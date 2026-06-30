# Memória

## 1. Hierarquia de Memórias.


**1. Memória da CPU**

- Localizada na RAM da CPU.
- Acessível pelas threads da CPU.
- Declarada com variáveis normais.
- Alocada com `malloc()`.

**2. Memória da GPU**

- **2.1 Memória Global**
    - Localizada na VRAM.
    - Acessível para todas as threads.
    - Alocada com `cudaMalloc()`.
    - Transferência usando `cudaMemcpy()`.
- **2.2 Memória Compartilhada**
    - Localizada na Shared Memory SM.
    - Acessível somente para threads do mesmo bloco.
    - Declarada com `__shared__`.
- **2.3 Memória Local**
    - Localizada nos registradores no SM ou na memória global.
    - Acessível só pela thread que esta executando.

```text
                GPU
┌──────────────────────────────────────────┐
│   GPU                                    │
│   ├─── GPC                               │
│   │    ├─── TPC                          │
│   │    │    ├── SM                       │
│   │    │    │    ├── CUDA Cores          │
│   │    │    │    ├── Registradores       │
│   │    │    │    ├── Shared Memory       │
│   │    │    │    └── Warp Scheduler      │
│   │    │    └── SM                       │
│   │    └─── TPC                          │ 
│   │         ├── SM                       │
│   │         ├── SM                       │
│   └─── GPC                               │
│                                          │
└───────────────────┬──────────────────────┘
                    │
                    │ 
                    │
        ┌────────────────────────────┐
        │           VRAM             │
        │                            │
        │       Global Memory        │
        └────────────────────────────┘
```

## 2. Memória Global

- É visível par todas as threads.
- Fica na VRAM da placa de vídeo
- Alocado com **cudaMalloc(void **d_a, size)**
- É necessário copiar os dados:
    - da CPU para GPU: cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    - da GPU para CPU: cudaMemcpy(a, d_a, size, cudaMemcpyDeviceToHost);

Exemplo: Soma de Vetores

```C
#define N
#define th 32
int *a, *b, *c;
int *d_a, *d_b, *d_c;

int size = N * sizeof (int);

check_error(cudaMalloc ((void **) &d_a, size));
check_error(cudaMalloc ((void **) &d_b, size));
check_error(cudaMalloc ((void **) &d_c, size));

a = (int*) malloc (size);
b = (int*) malloc (size);
c = (int*) malloc (size);

for (int i = 0; i < N; i++){
    a[i] = i;
    b[i] = i;
    c[i] = i;
}

cudaMemcpy (d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy (d_b, b, size, cudaMemcpyHostToDevice);

dim3 grid_size (ceil(N / (float th)));
dim3 block_size (th);

somaVet <<<grid_size,block_size>>> (d_a, d_b, d_c);
check_error(cudaGetLastError);

cudaMemcpy (c, d_c, size, cudaMemcpyDeviceToHost);

free(a);
free(b);
free(c);
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);

return 0;
```
## 3. Memória Unificada

- Mesma coisa global: fica na CPU mas é copiado para GPU quando precisa.
- Porém é o driver que faz toda a parte de escrever na GPU.
- Mais fácil de usar.
- Pode ter menor velocidade.
- É necessário usar `cudaDeviceSynchronize()` antes do `cudaFree()`.

Exemplo: Soma de vetores

```C
int main (){
    int *a, *b, *c;
    int size = N * sizeof(int);
    
    check_error(cudaMallocManaged ((void **) &a, size));
    check_error(cudaMallocManaged ((void **) &b, size));
    check_error(cudaMallocManaged ((void **) &c, size));
    
    for (int i = 0; i < N; i++){
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    dim3 grid_size (ceil(N / (float th)));
    dim3 block_size (th);

    somaVet <<<grid_size,block_size>>> (d_a, d_b, d_c);
    check_error(cudaGetLastError);

    cudaDeviceSynchronize();

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
```

## 4. Memória Compartilhada

- Memória compartilhada APENAS entre threads dentro do mesmo bloco.
- Localizada no SM.
- É rápido.
- Usa-se `__shared__`.

## 5. Algoritmo Stencil

**1. Entrada:**

- Vetor X de N posições: X[N]
- Raio r

**2. Saída:**

- Vetor Y de n posições Y[N], onde cada Y[i] é a soma dos valores das posições de X[i - r] até X[i + r].

**3. Exemplo:**

```text
IN:
X[8] = X[0,2,5,2,5,4,3,1]
r=2

OUT:
Y[8]= X[7,9,14,18,19,15,13,8]
```

**4. Implementação Serial:**

```c
#include <stdio.h>
#include <stdlib.h>

#define N 20
#define RADIUS 3

int main()
{
    int vet[N];
    int out[N];

    srand(123);

    for (int i = 0; i < N; i++)
    {
        vet[i] = rand() % 100;
    }

    for (int i = 0; i < N; i++)
    {
        out[i] = 0;

        for (int j = i - RADIUS; j <= i + RADIUS; j++)
        {
            if (j >= 0 && j < N)
                out[i] += vet[j];
        }
    }
}
```

**6. Implementação CUDA:**
