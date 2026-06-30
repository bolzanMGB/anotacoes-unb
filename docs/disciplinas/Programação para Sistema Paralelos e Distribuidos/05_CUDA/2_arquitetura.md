# 1. Arquitetura

## 1. Conceitos

**1. Famílias:** 

- Diz a linha comercial da GPU. Exemplos:
- GeForce RTX 3050, GeForce RTX 4050: Placas para consumidor final.
- V100, A100: Placas para data centers.

**2. Arquiteturas:** 

- Diz a arquitetura interna da GPU
- Costuma ter nome de cientistas: Fermi, Kepler, Pascal
- Novos CUDA Cores.
- Novas instruções.
- Ray Tracing.

**3. Compute Capability:** 

- É a versão CUDA daquela arquitetura.
- Indica recursos e capacidades de hardware.
- Exemplo: Blackwell

## 2. Organização Física

- CUDA Core: 
    - Unidade de execução para operações matemáticas comuns.
- TENSOR Core: 
    - Unidade de execução especializada para operações matriciais
- SM (Streaming Multiprocessor): 
    - Agrupa Cores.
    - Escalona as threads nesses Cores.
- TPC (Texture Processing Cluster):
    - Agrupamento intermediário.
    - Agrupa SMs.
- GPC (Graphics Processing Cluster):
    - Agrupamento maior.
    - Agrupa TPCs.

## 3. Execução

Ao fazer uma chamada de GPU em CUDA:

- Informamos o número de blocos e o número de threads por bloco.
    - Cada bloco pode possuir até 1024 threads.
- O hardware distribui os blocos entre os SMs.
    - O limite de threads por SM é 2048.
    - OS blocos são distribuídos por inteiro:
        - Preenche até chegar perto do limite de 2048.
        - Também é levado em conta outros recursos do SM, como registradores e memória compartilhada.
        - Se um bloco não caber por inteiro é passado para o próximo SM.
- Depois de serem distribuídos pelos SMs, os blocos são internamente divididos em warps:
    - Warps: Blocos de 32 threads.
    - Por isso o número de threads por bloco geralmente é um múltiplo de 32.
- Dai então as threads são executadas:
    - A cada ciclo de clock um ou mais warps são escolhidos pelo Warp Scheduler.
    - As threads desses warps são executadas pelos CUDA Cores.
    - Não existe correspondência de 1 thread para 1 core.
    - Cada CUDA Core executa muitas threads ao longo do tempo.
        
screenshot 5

## 3. Erros

### 3.1 Tratamento de Erros

- A função `ret = cudaMemcpy(...)` possuir retornos, por exemplo:
    - ret = cudaSucces.
    - ret = cudaErrorInvalidValue.
    - ret = invalid configuration argument.
        - Esse aqui pega se for número inválido de threads.
- Então, a função `cudaGetErrorString(ret)` transforma ess retorno em texto, por exemplo:
    - out of memory.
    - invalid argument.
- A execução do kernel não retorna erros, deve-se perguntar logo após ele:
    - `cudaGetLastError()`

Logo é possível tratar o erro:

```c
void check_error (cudaError_t ret){
    if (ret != cudaSuccesss){
        printf ("Erro: %s", cudaGetErrorString(code));
        exit(1);
    }
}

int main (){
    ...
    check_error(cudaMemcpy(void ** d_a, a, size, cudaMemcpyHostToDevice));
    somarVet<<<grid_size, block_size>>> (d_a);
    check_erorr(cudaGetLastError);
}
```

### 3.2 Como lidar com N threads maior que o limite por Block?

- Na maioria das GPUs atuais o limite de threads por block é 1024.
- No caso de N = 2024, somaVet <<<1, 2024>>>
    - Cada bloco teria 2024 threads.
    - Daria erro (máximo 1024).
- Solução: usar mais de um bloco, cada um um número menor de threads.
- block_sizes: número de threads por bloco.
- grid_size: número de blocos por grid.

**1. Escolher o block_size**

- Tamanho limite maioria das vezes é 1024.
- Escolha do block_size depende do programador.
- Cuda executa threads em grupos de 32 threads.
- Então, o block_size geralmente é múltiplos de 32.

**2. Calcular o tamanho do grid_size:**

- N é o número de threads.
- Dividimos N por block_size.
- É necessário o arredondamento a divisão não for inteira.
- `grid_size = ceil (N/(float) block_size)`
- No caso de 2024:
    - block_size = 32
    - grid_size = 62

**3. Como identificar as threads dentro um bloco?**

- Se utilizássemos apenas `int id = threadIdx.x`, teríamos problemas pois o id da thread é único apenas dentro um bloco específico. 
- Para isso, a identificação das threads pode ser feita com:
    - `int id = blockIdx.x * blockDim.x + threadIdx.x`.
- Problema:
    -o número de threads criadas pode passar o número de N.
    - Então, limitados o id apenas para o tamanho do vetor N com um `if`:

```c
__global__ void add(int *a, int *b, int *c){
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < N){
        c[id] = a[id] + b[id];
    }
}
```

