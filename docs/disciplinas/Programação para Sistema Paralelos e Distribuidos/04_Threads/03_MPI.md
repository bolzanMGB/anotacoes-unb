# Message Passing Interface (MPI)

## 1. Introdução

No OpenMP, a programação paralela se dá na mesma região de memória (compartilhada, na mesma máquina) e a comunicação se dá por variáveis compartilhadas.

No MPI, a programação paralela se dá em diferentes espações de memória (distribuída, diferentes máquinas) e a comunicação entre esses processos independentes ocorre através da troca explícita de mensagens.

Nele as trocas de mensagens ocorrem dentro de um Comunicador, que seria basicamente uma "sala de chat" entre processos. O `MPI_COMM_WORLD` é o comunicador global. Ele engloba todos os processos da execução atual, que são identificados por ranks. Também é possível criar subgrupos dentro do comunicador global.

Ao executar um programa MPI `nome.c` com `mpirun`, você indica o número de processos que vão ser criados e todos eles vão executar em paralelo o mesmo código a partir da função main dentro do comunicador `MPI_COMM_WORLD`.

## 2. Como rodar

**1. Pacotes necessários**

```bash
sudo apt update
sudo apt install build-essential openmpi-bin openmpi-common libopenmpi-dev
```

**2. Compilar**

```bash
mpicc nome_programa.c -o programa_mpi
```

**3. Executar**

```bash
mpirun -np 4 ./programa_mpi
```

## 3. Estrutura Básica de um Programa MPI

**1. ret = MPI_Init(&argc, &argv)**

Ele inicializa o ambiente criando o comunicador global `MPI_COMM_WORLD`. Ele retorna se a inicialização foi bem-sucedida ou não:

- MPI_SUCCESS: Valor 0, tudo ocorreu certo.
- Valor diferente de 0: Deu errado.

**2. MPI_Comm_rank(MPI_COMM_WORLD, &rank)**

Descobre o identificador do processo atual e coloca dentro de uma variável, no caso rank.

**3. MPI_Comm_size(MPI_COMM_WORLD, &num_procs)**

Descobre o número de processos dentro de um comunicado e coloca dentro de uma variável, no caso num_procs.

**3. MPI_Finalize()**

Encerra o ambiente.

**4. MPI_Abort(MPI_COMM_WORLD, ret)**

Força a interrupção de todos os procesos associados com um determinado comunicardor, geralmente o global MPI_COMM_WORLD.


### 3.1. Exemplo 1: Hello World Básico

```c
#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[]){
    int rank;
    int num_procs;
    int ret;

    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS){
        MPI_Abort (MPI_COMM_WORLD, ret);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    printf ("Hello World do processo %d/%d\n", rank, num_procs);

    MPI_Finalize();
    return 0;
}

$ mpirun -np 4 ./programa
Hello World do Processo 1/4
Hello World do Processo 2/4
Hello World do Processo 3/4
```

## 4. Comunicação Ponto a Ponto

**1. MPI_Send(msg, ret+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD)**

Envia uma mensagem com certos parâmetros (M,S,T,D,T,C):

- 1. msg: Indica o ponteiro para onde os dados que serão enviados estão.
- 2. ret+1: Indica o tamanho da mensagem mais 1 (o \0 que indica o fim da string).
- 3. tipo: Indica o tipo de dado da mensagem, pode ser MPI_CHAR, MPI_INT e MPI_FLOAT.
- 4. dst: Indica o rank do destino.
- 5. tag: Indica a tag, serve para identificar o assunto ou categoria da mensagem.
- 6. comunicador: Indica o comunicador pra onde a mensagem vai.


**2. MPI_Recv(msg, 200, MPI_CHAR, org, tag, MPI_COMM_WORLD, &status)**

Recebe uma mensagem com certos parâmetros:

- 1. msg: Ponteiro para onde MPI vai gravar a mensagem que recebeu.
- 2. 200: Tamnho máximo da mensage.
- 3. tipo: Tipo da mensagem que vai ser recebida.
- 4. org: Rank de origem/remetente.
- 5. tag: Tag que pode ser recebida.
- 6. comunicado: Comunicador de onde a mensagem veio.
- 7. &status: Onde o MPI vai anotar os metadados da mensagem após ela ser entregue.

**3. MPI_Status status**

Assim como integer, string etc, ele também é uma estrutura de dados. Ele armazena os metadados de uma mensagem recebida após uma receção, é o recebido de entrega. Ele possui:

- `status.MPI_SOURCE`: Rank do processo que enviou a mensagem.
- `status.MPI_TAG`: Tag que veio com a mensagem.
- `status.MPI_ERROR`: Código de erro se algo deu errado.


### 4.1 Exemplo 1: Send e Recv

```c
#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main (int argc, char *argv[]){

    int ret;
    ret = MPI_Init (&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    char msg [200];
    int tag = 0;
    MPI_Status status;

    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    if (rank != 0){
        int dst = 0;
        int size = sprintf (msg, "Mensagem do Processo %d/%d\n", rank, num_procs) + 1;
        MPI_Send(msg, size, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
        printf ("Sou o processo %d/%d, Acabei de Enviar para o 0/%d\n", rank, num_procs, num_procs);
    } 

    MPI_Barrier(MPI_COMM_WORLD);
    
    if (rank == 0){
        printf ("Sou o processo %d/%d, Recebi essas mensagens:\n", rank, num_procs);
        for (int dst = 1; dst < num_procs; dst++){
            MPI_Recv (msg, 200, MPI_CHAR, dst, tag, MPI_COMM_WORLD, &status);
            printf ("%s", msg);
        }
    }

    MPI_Finalize();
    return 0;
}

$ mpirun -np 4 ./programa
Sou o processo 2/4, Acabei de Enviar para o 0/4
Sou o processo 1/4, Acabei de Enviar para o 0/4
Sou o processo 3/4, Acabei de Enviar para o 0/4
Sou o processo 0/4, Recebi essas mensagens:
Mensagem do Processo 1/4
Mensagem do Processo 2/4
Mensagem do Processo 3/4
```

## 5. Informações

**1. char nome [MPI_MAX_PROCESSOR_NAME]**

Macro que representa o tamanho máximo em caracteres que o nome de uma máquina pode ter.

**2. MPI_Get_processor_name(name, &ret)**

Pega o hostname da máquina onde o processo, que está em ret, está rodando e colocando dentro de uma variável.


**3. MPI_Get_version(&ver, &subver);**

Pega a versão e subversão do MPI que está rodando em coloca em variáveis.

**4. t_init = MPI_Wtime();**

Retorna um double do tempo do relógio local da máquina. Usado para medir quanto tempo demorou algo.

## 6. Ordem de Envio e Recepção

Se um processo X enviar uma mensagen n1 e depois uma mensagen m2 para o processo Y, a mensagem n1 sempre vai chegar primeiro que a n2.

## 6.1 Exemplo: Mostra a Ordem de Envio

```c
#include <stdio.h>
#include "mpi.h"
#include <string.h>

#define n_msgs 3
// MSTDTC
int main (int argc, char * argv[]){
    
    double t_fim;
    int ret = MPI_Init (&argc, &argv);
    double t_inicio = MPI_Wtime();

    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    MPI_Status status;
    int tag = 0;
    char msg [200];

    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    if (rank != 0){
        int dst = 0;

        for (int i = 0; i < n_msgs; i++){
            sprintf (msg, "Mensagem %d do processo %d/%d\n", i, rank, num_procs);
            int size = strlen(msg) + 1;
            MPI_Send (msg,size,MPI_CHAR,dst,tag,MPI_COMM_WORLD);
        } 
    }
    else{
        char name [MPI_MAX_PROCESSOR_NAME];
        MPI_Get_processor_name(name, &ret);

        int ver; 
        int subver;
        MPI_Get_version(&ver, &subver);

        printf("Sou o Processo 0, estou rodando em %s na versão %d.%d e recebi:\n", name, ver, subver);
        for (int org = 1; org < num_procs; org++){
            for (int j = 0; j < n_msgs; j++){
                MPI_Recv (msg,200,MPI_CHAR,org,tag,MPI_COMM_WORLD,&status);
                printf ("%s",msg);
            }
        }
        t_fim = MPI_Wtime();
        printf ("Tempo gasto = %3.6lf ms\n", (t_fim - t_inicio) * 1000.0);
    }

    MPI_Finalize();
    return 0;
}

// bash
$ mpirun -np 4 ./programa 
Sou o Processo 0, estou rodando em DESKTOP-KRL991S na versão 3.1 e recebi:
Mensagem 0 do processo 1/4
Mensagem 1 do processo 1/4
Mensagem 2 do processo 1/4
Mensagem 0 do processo 2/4
Mensagem 1 do processo 2/4
Mensagem 2 do processo 2/4
Mensagem 0 do processo 3/4
Mensagem 1 do processo 3/4
Mensagem 2 do processo 3/4
Tempo gasto = 0.355700 ms
```

## 7. Recv MPI_ANY_SOURCE e MPI_ANY_TAG

**1. MPI_ANY_SOURCE**

Em vez de especificar a origem de onde vai receber mensagens, podemos deixar aberto. Assim, recebemos a mensagem que chegar primerio.

**2. MPI_ANY_TAG**

A mensagem a ser recebido pode ter qualquer tag.

## 8. MPI_Bcast (&MSG, SIZE, TYPE, ORIGIN, COMMUNICATOR)

Envia uma mensagem a partir de um único processo para todos os outros. Somente o processo origin envia, os outros recebem. 


```c
// Início
Processo 0 -> msg = "Hello do Processo 0"
Processo 0 -> msg = ""
Processo 1 -> msg = ""

// Fim
Processo 0 -> msg = "Hello do Processo 0"
Processo 0 -> msg = "Hello do Processo 0"
Processo 1 -> msg = "Hello do Processo 0"
```

- MSG: Ponteiro para onde o dado que vai ser enviado está e onde vai ser guardado nos processos que vão receber.
- SIZE: tamanho em int da mensage.
- TYPE: Tipo: MPI_CHAR, MPI_INT etc.
- ORIGIN: Rank do processo emissor.
- COMMUNICATOR: canal onde os processos estão.


## 9. MPI_Gather (V,AS,T,D,AR,T,D,C) VSTDRTRC

Coleta X elementos de um vetor de cada proceso e os junta em um outro vetor no processo raiz.

```c
// Inicio
Processo 0 -> vet[A,B] vet2[]
Processo 2 -> vet[C,D]
Processo 2 -> vet[E,F]

// Fim
Processo 0 -> vet[A,B] vet2[]
Processo 2 -> vet[C,D]
Processo 2 -> vet[E,F]
```

- V: Ponteiro para o endereço do dado a ser coletado.
- AS: Quantidade de elementos nesse endereço que vão ser enviados;
- T: Tipo do dado coletado.
- D: Array de destino onde os dados vão ser juntados na raiz.
- AR: Quantidade de elementos que vão ser recebidos por processo.
- T: Tipo dos dados recebidos.
- R: Rank do processo raiz.
- C: Comunicator onde vai ocorrer

## 10. MPI_Scatter(V, AS, T, D, AR, T, R, C) VSTDRTRC

Oposto do gather: pega um array com X elementos de um processo raiz e o distribui para os outro procesos

```c
// Início
Processo 0 -> vet['A''B','C']
Processo 1 -> letra = '' 
Processo 2 -> letra = '' 
Processo 3 -> letra = '' 

// Fim
Processo 0 -> vet['A''B','C']
Processo 1 -> letra = 'A' 
Processo 2 -> letra = 'B' 
Processo 3 -> letra = 'C' 
```

- V: Vetor que será dividido.
- AS: Amount sent, quantos elementos enviados por processos.
- T: Tipo dos elementos.
- D: Variavel de destino nos processos.
- AR: Amount Recv, quantos elementos são recebidos.
- T: Tipo dos elementos.
- R: Raiz que possui o array.
- C: Comunicador.