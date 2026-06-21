# Message Passing Interface (MPI)

## 1. Introdução

No OpenMP, a programação paralela se dá na mesma região de memória (compartilhada, na mesma máquina) e a comunicação se dá por variáveis compartilhadas.

No MPI, a programação paralela se dá em diferentes espações de memória (distribuída, diferentes máquinas) e a comunicação entre esses processos independentes ocorre através da troca explícita de mensagens.

## 2. Estrutura Básica de um Programa MPI

**1. MPI_Init(&argc, &argv)**

Inicializa o ambiente e deve ser chamada antes de qualquer outra função MPI.

**2. MPI_Comm_rank(MPI_COMM_WORLD, &num_procs)**

Descobre o identificado único (rank) do processo atual dentro do comunicador global;.

**3. MPI_Finalize()**

Encerra o ambiente.
