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

## 2. Organização

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

## 3. Erros

**1. Números máximo de threads por bloco**

- Na maioria das GPUs atuais o limite de threads por block é 1024.
- Então precisamos usar mais de um bloco
- Nesse caso, se utilizássemos apenas `int id = threadIdx.x` teríamos problemas pois o id da thread é único apenas dentro um bloco específico. 
- Para isso, a identificação das threads pode ser feita com:
    - `int id = blockIdx.x * blockDim.x + threadIdx.x`