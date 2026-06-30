# Introdução ao CUDA

## 1. Introdução

### 1.1 CPU x GPU

- CPU: Central Processing Unit.
    - É a unidade geral de processamento.
    - Executa instruções gerais.
        - Excelente para tarefas de lógica.
    - Abrir programas, rodar o SO, compilar código, controlar memória, dispositivos, arquivos, etc.
    - Até 32 núcleos.
- GPU: Graphics Processing Unit.
    - É a unidade de processamento especializado em cálculos pesados.
    - Renderizar imagens, gráficos, vídeos, jogos, animações, VR, IA, etc.
    - Milhares de núcleos trabalhando ao mesmo tempo.

### 1.2 SIMD 

- GPU possui padrão SIMD (Single Instruction, Multiple Data).
- Executa muito bem a mesma instrução sobre múltiplos elementos simultaneamente.
    - Tarefas repetitivas e simultâneas.
- Possui alto throughput aritmético.
    - Alta quantidade de operações matemáticas por segundo.

### 1.3 Surgimento da CUDA

- Até 2001, as GPUs eram feitas apenas para renderizar gráficos e os programadores não tinham nenhum controle.
- Em 2001 surgiu o NVIDIA GeForce 3.
    - Desenvolvedores passaram a poder programar a GPU para executar Vertex Shader (modelagem de vídeo).
    - Eles começaram a enganar a GPU passando para ela cálculos gerais como imagens.
    - Surgimento da GPGPU (General-Purpose computing on Graphics Processing Units).
- Em 2006 surgiu o CUDA:
    - Possibilitou programar direto na GPU. 
    - Sem precisa fingir que está desenhando uma imagem.
    - CUDA não é só a linguagem para programar GPU, é um ecossistemas completo:
        - Hardware das GPU.
        - Compiladores.
        - Drivers
        - Bibliotecas otimizadas.

## 2. Ambiente de Programação

- Requer:
    - Placa de vídeo da NVIDIA.
    - Kit de desenvolvimento (CUDA Toolkit)
    - Driver proprietário.
- Cuidados:
    - Atualizações de kernel podem impedir o driver.
    - CUDA Toolkit deve ser compatível com a GPU.
- Alternativa: Google Colab.


## 3. Programação Heterogênea

Significa usar mais de um tipo de processador no mesmo programa.

- CPU começa rodando uma única thread na main.
- Chegando na parte paralelizável, ela chama a GPU.
- CPU continua de fundo preparando dados, alocando memória, chamando kernel, etc.

### 3.1 Tipos de funções:**

- funções host: 
    - Executadas em CPU.
    - Comportamento padrão.
    - Geralmente a tag de host é omitida.
- funções device: 
    - Executadas paralelamente em GPU.
    - Só podem ser chamadas por que já está executando na GPU.
    - Ou seja, outras funções device ou funções global.
- funções kernel/global: 
    - Executadas paralelamente em GPU.
    - Podem ser chamadas por funções host.
    - Podem chamar funções device. 
    - São chamadas usando <<<x, y>>>


screenshot 3


```c
__global__ void helloFromGPU(){
    printf ("Hello froom GPU");
}

int main (){
    helloFromGPU<<<2, 2>>>;
    cudaDeviceSynchronize();
    return 0;
}

"Hello froom GPU"
"Hello froom GPU"
"Hello froom GPU"
"Hello froom GPU"
```

### 3.2 Blocos e Grid:**

- Threads são organizas em blocos.
- Blocos são organizados em grid.
- Ao chamar uma função que executa em GPU utilizamos `<<<x, y>>>`, onde:
    - x: números de blocos no grid.
    - y: números de threads por bloco.
- Para identificação usamos:
    - `threadIdx.x`: Retorna o identificador da thread dentro de uma bloco.
    - `blockIdx.x`: Retorna o identificador do bloco dentro de uma grid.
    - `blockDim.x`: Retorna o número de threads dentro do bloco.

screenshot 3

### 3.3 Dimensões

- Blocos e grid podem ser organizados nas 3 dimensões.
    - `dim3 grid(x, y, z)`
    - `dim3 block(x, y, z)`
- Ao omitir uma das letras mudamos a dimensão.
- A identificação também pode ser feita com mais de uma dimensão utilizando:
    - Para y: `threadIdx.y` e `blockIdx.y`
    - Para z: `threadIdx.z` e `blockIdx.z`


**1. Uma Dimensão:**

Exemplo: dim3 grid (2), dim3 block (3)

```text
Bloco 1:       Bloco 2: 
(0) (1) (2)    (0), (1), (2)
```

**2. Duas Dimensões:**

Exemplo: dim3 grid (2, 2), dim3 block (2, 2)

```text
Bloco 1:     Bloco 2
(0,0)(1,0)  (0,0)(1,0)
(0,1)(1,1)  (0,1)(1,1)

Bloco 3:     Bloco 4
(0,0)(1,0)  (0,0)(1,0)
(0,1)(1,1)  (0,1)(1,1)
```

**3. Três Dimensões:**

Imagine que os blocos e grids são organizados em camadas

Exemplo: dim3 grid (2, 2, 2), dim3 block (2, 2, 2)

screenshot 4

## 4. Arquitetura física

- As GPUs possuem milhares de cores.
- Os cores são organizados em Streaming Processors (SM).
- Os SM são organizados em Graphics Processing Clusters (GPCs).
- Ao fazer uma chamada de GPU em CUDA:
    - Cada bloco vai para um SM.
    - Threads desse bloco são distribuídos pelos cores desse SM.
    - Uma thread não corresponde necessariamente a um core.
    - Um core pode executar mais de uma thread.
    
screenshot 5


## 5. Memória

- CPU trabalha com RAM.
- GPU trabalha com VRAM.
- A GPU não consegue acessar diretamente as variáveis da RAM.
- Então:

**1. Antes da GPU acessar uma variável da RAM:** 

- Criar espaço na VRAM: `cudaMalloc (void **device_ponteiro, tamanho)`
- Copiar os dados da RAM para a VRAM: `cudaMemcpy(destino, origem, tamanho, cudaMemcpyHostToDevice)

**2. Após executar:** 

- Executar o kernel.
- Copiar o resultado da VRAM de volta para a RAM: `cudaMemcpy(destino, origem, tamanho, cudaMemcpyDeviceToHost)`
- Limpar memória
: `cudaFree(variável)`


Exemplo: Soma de vetores

```c
#define N 2

__global__ void somaVet (*a, *b, *c){
    int i = threadIdx.x
    c[i]=a[i]+b[i];
    printf ("Soma do vetor %d é igual a %d"i, c[i])
}

int main (){
    int *a; int *b; int*c;
    int *d_a; int *d_b; int*d_c; 

    int size = N * sizeOf (int);

    cudaMalloc(void **d_a, size);
    cudaMalloc(void **d_b, size);
    cudaMalloc(void **d_c, size);

    a = (int *) malloc (size);
    b = (int *) malloc (size);
    c = (int *) malloc (size);

    for (int i = 0; i < N; i++){
        a[i]=i;
        b[i]=i;
        c[i]=i;
    }
    
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, size, cudaMemcpyHostToDevice);

    dim3 n(N)
    somarvet <<<1, n>>> (d_a,d_b,d_c);

    cudaMemcpy(a, d_a, size, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_x);

    Free(a);
    Free(b);
    Free(c);
}
```

