# Biblioteca OpenMP


O O OpenMP é um dos frameworks é um dos modelos de programação paralelas mais utilizadas hoje em dia. Ele é utilizado importando a biblioteca `#include <omp.h>`


## 1. Como compilar

1. `#include <omp.h>` 
    - Necessário ter importado a biblioteca no código


2. `gcc -fopenmp paralelo.c`
    - Comando para compilar um arquivo paralelo.c  
    

3. `export OMP_NUM_THREADS=X`

    - Comando para controlar o número de threads em paralelo

4. `./a.out`
    
    - Comando para gerar o programa compilado

## 2. Como as threads funcionam

- O programa começar com apenas uma thread (a Master Thread).
- Ao encontrar um região paralela (um # pragma omp), a Master Thread cria a quantidade threads selecionada (fork).
- As threads executam o bloco de código simultaneamente.
- A ordem de acesso depende do escalonador (é aleatório).
- Threads se comunicam através de variáveis compartilhadas.
- No final do bloco paralelo, as threads morrem e apenas a Master Thread continua.

## 3. Anatomia de uma instrução OpenMP

```C
#pragma omp diretiva cláusula1 cláusula2
```

1. **Diretiva:** É o que fazer.

2. **Cláusula:** São a regras adicionais (ex: quais variáveis são privadas, quantas threads usar)

## 4. Funções principais

1. Bloco paralelo
Aqui todas as threads vao executar ao mesmo tempo uma tarefa. Se você tiver 4 threads e nesse bloco colocar um printf ("Hello"), vai ser printados 4 hellos.
```C
#pragma omp parallel
{
    // Todas as threads executam isso ao mesmo tempo
    funcao(); 
}
```

2. Loop paralelo
Aqui as interações do laço for são divididas entre as threads, proporcionando uma execução mais rápida.

```C
#pragma omp parallel
{
   int vetor[1000];

    #pragma omp for
    for (int i = 0; i < 1000; i++) {
        vetor[i] = vetor[i] * 2; // Cada thread lida com um i diferente
    }
}

// algumas cláusulas podem ser combinadas, o trecho pode ser reescrito assim:

int vetor[1000];

#pragma omp parallel for
for (int i = 0; i < 1000; i++) {
    vetor[i] = vetor[i] * 2; // Cada thread lida com um i diferente
}
```


## 5. Identificando threads

1. `omp_set_num_threads();` 
    - Indica quantas threads vao ser ser executadas.

2. `omp_get_thread_num();` 
    - Indica o número identificado da thread que rodou a função.

3. `omp_get_num_threads();` 
    - Indica o número de threads que estão rodando ativamente nesse bloco.

4. `omp_get_max_threads()` 
    - Indica o limite de threads que podem ser criadas.


**Exemplo:**

```C
#include <stdio.h>
#include <omp.h>

int main (){
    int nthreads;
    int id;

    #pragma omp parallel private (id, nthreads)
    {
        id = omp_get_thread_num();

        nthreads = omp_get_num_threads();

        printf("%d of %d - hello world!\n", id, nthreads);
    }

    return 0;
}

/// bash
$ gcc -fopenmp teste.c
$ ./a.out
1 of 4 - hello world!
2 of 4 - hello world!
0 of 4 - hello world!
3 of 4 - hello world!
```
## 7. Número de threads

Podemos usar `omp_set_num_threads(n)` para setar um número fixo de threads.

Se não usarmos ele, podemos definir o número de threads após compilar o código e antes de executá-lo com `export OMP_NUM_THREADS=n`

```C
#include <stdio.h>
#include <omp.h>

int main (){

    omp_set_num_threads(2);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int total =  omp_get_num_threads();
        printf("thread %d/%d\n", id, total);
    }
    return 0;
}

/// bash
$ gcc -fopenmp teste.c
$ ./a.out
thread 0/2
thread 1/2

# sem o set
$ gcc -fopenmp teste.c
$ export OMP_NUM_THREADS=5 
$ ./a.out
thread 2/5
thread 1/5
thread 3/5
thread 4/5
thread 0/5
```

**2. export OMP_NUM_THREADS=n**
Seta um número padrão que pode ser alterado

```C

````

## 6. Dados compartilhados vs Dados privados

**1. private:** É criado uma cópia sem valor para cada thread.

**2. firstprivate:** Cada thread possui a sua variável, porém é iniciada com o valor que ela tinha antes da região paralela

**3. shared:** Todas threads acessam a mesma variável.

```C
int compartilhado = 100;
int privado       = 200;
int primeiro_priv = 300;

#pragma omp parallel num_threads(2) shared(compartilhado) private(privado) firstprivate(primeiro_priv)
{
    int id = omp_get_thread_num();

    if (id == 0) {
        compartilhado = 999; 
    }

    privado = id + 1;

    primeiro_priv = primeiro_priv + id;

    printf("Thread %d -> shared: %d | private: %d | firstprivate: %d\n", 
            id, compartilhado, privado, primeiro_priv);
}

// bash
Thread 0 -> shared: 999 | private: 1 | firstprivate: 300
Thread 1 -> shared: 999 | private: 2 | firstprivate: 301
```
.

## 7. Sincronização

Aqui temos um grande problema. Quandos threads acessam variáveis globais (declaradas fora do escopo do pragma) pode ocorrer delas alterarem essa variável ao mesmo tempo, resultando em uma diferença ao rodar o código várias vezes. Talvez iso seja perceptível com baixos números, porém com altos isso muda bastante.

```C
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main()
{
    srand(123);
    int *vet = malloc(400000000 * sizeof(int));
    for (int i = 0; i < 400000000; i++)
        vet[i] = rand() % 50;

    int n = 1;
    int q_n = 0;

    #pragma omp parallel 
    {
        #pragma omp for
        for (int i = 0; i < 400000000; i++)
            {
                if (vet[i] == n)
                    q_n++;
            }
    }
   
    printf("q_n = %d\n", q_n);
    return 0;
}

/// bash
$ ./t.exe
q_n = 6352056
$ ./t.exe
q_n = 6458356
```

**1. critical**

- Threads formam uma fila na frente do trecho.
- Trecho é delimitado por {}, caso sem ele é somente a próxima instrução.
- Cada thread acessa uma por vez (serializado).
- Garante exclusão mútua.
- Pode ser mais lento

int contador_erros = 0;

```C
#pragma omp parallel 
{
    // O OpenMP tranca a porta para todas as outras threads
    #pragma omp critical
    {
        contador += 1;
        if (contador % 100 == 0) {
            printf("Chegamos a mais uma centena: %d\n", contador);
        }
    } // Tranca aberta para a próxima thread da fila
}
```

**2. reduction (operação:variavel)**

- Threads acessam simultâneamente o trecho.
- Age em uma só variável.
- Porém, cada uma possui uma cópia privada da variável.
- No final o OpemMP junta os resultados.
- A operação para juntar pode ser, soma, subtração etc.
- Mais rápido que critical

```C
int soma = 0;

// O (+:soma) diz: crie cópias e, no fim, junte tudo somando
#pragma omp parallel for reduction(+:soma)
for (int i = 0; i < 1000; i++) {
    soma += i; 
}
// Aqui, 'soma' tem o resultado perfeito e seguro
```

**3. atomic:**
- Semelhante a critical, porém focada em uma única linha de código simples.
- Não cria travas.
- Usa o hardware, mais precisa.

**4.single**

- Serve para somente uma única thread (geralmente a Master Thread) acesse a região.
- Há uma barreira implícita.
- Ao chegar no single, todas as threads esperam thread escolhida acessar a área.
- Depois todas seguem juntas.

```C
#pragma omp parallel
{        
    // Todas as threads fazem isso em paralelo
    fazer_calculo_pesado();

    #pragma omp single
    {
        // Apenas UMA thread vai executar esse print
        printf("Fase 1 concluída. Preparando próxima etapa...\n");
    } // <-- Todas as outras threads esperam aqui até este bloco terminar

    // Todas as threads continuam a partir daqui
    fazer_proximo_calculo();
}
```

**5. master**
- Mesma coisa da single.
- Porém sempre será a thread 0 que vai acessar a região.

**6. barrier:**

- Serve como um ponto de encontro ou linha de largada.
- Força todas as thread esperarem até que todas tenham chegado nesse ponto do código.

```C
#pragma omp parallel
{
    int id = omp_get_thread_num();
    vetor_compartilhado[id] = calcular_etapa_1(id);

    // STOP! Ninguém pode avançar para a etapa 2 antes que TODO o vetor_compartilhado esteja preenchido.
    #pragma omp barrier 

    // Agora é seguro ler dados calculados por outras threads na etapa 1
    int vizinho = (id == 0) ? vetor_compartilhado[1] : vetor_compartilhado[id-1];
    calcular_etapa_2(vizinho);
}
```

## 8. Escalonamento de Loops
Como o OpenMP divide as interações do loop entre as threads? 

### 8.1 static
As interações são divididas em blocos de tamanho fixo e distribuídas em um padrão round-robin antes da execução do loop. Há rodadas, caso alguem terminar primerio é necessário esperar todos terminarem para inicia sua próxima rodada.

**Exemplo:**

Há um loop com 12 interações, 3 threads e blocos de chunks de 3, então:

```bash
1. Rodada
- O bloco com as iterações [0, 1] vai para a Thread 0.
- O bloco com as iterações [2, 3] vai para a Thread 1.
- O bloco com as iterações [4, 5] vai para a Thread 2.

2ª Rodada (O ponteiro volta para o começo da fila):
- O bloco com as iterações [6, 7] vai para a Thread 0.
- O bloco com as iterações [8, 9] vai para a Thread 1.
- O bloco com as iterações [10, 11] vai para a Thread 2.
```

*Exemplo Prático:

```C
#include <stdio.h>
#include <omp.h>
#include <unistd.h> 

int main()
{
#pragma omp parallel for num_threads(4) schedule(static,1) //schedule(static,4)
    for (int i = 0; i < 8; i++)
    {
        sleep(1);
        printf("Thread %d calculando %d\n", omp_get_thread_num(), i);
    }
    return 0;
}

/// bash static 2
$ ./t.exe
Thread 1 calculando 2
Thread 1 calculando 3
Thread 3 calculando 6
Thread 3 calculando 7
Thread 0 calculando 0
Thread 0 calculando 1
Thread 2 calculando 4
Thread 2 calculando 5

/// bash static 4
$ ./t.exe
Thread 1 calculando 4
Thread 1 calculando 5
Thread 1 calculando 6
Thread 1 calculando 7
Thread 0 calculando 0
Thread 0 calculando 1
Thread 0 calculando 2
Thread 0 calculando 3
```

### 8.2 dynamic

OpenMP não define quem faz o que antes de executar. As tarefas ficam numa fila e as threads vão pegando pacotes de x tarefas conforme vão terminando até acabar a fila. Em vez de esperar todo mundo terminar (como seria no estático),  vira uma corrida de quem é mais rápido.

**Exemplo:

Há um loop com 16 interações, 3 threads e blocos de chunks de 3, então:

```bash
1. Largada:
- Thread 0 pega o Pacote A [0, 1, 2]
- Thread 1 pega o Pacote B [3, 4, 5]
- Thread 2 pega o Pacote C [6, 7, 8]

2. Meio do Caminho
Thread 1 tinha uma conta fácil e terminou primeiro que todo mundo:
- Thread 1 pega o Pacote D [9, 10, 11]

Logo depois, a Thread 2 termina o dela. Ela corre na fila e pega o Pacote E:
- Thread 2 pega o Pacote E [12, 13, 14]

E a Thread 0, que pegou um trabalho demorado, finalmente termina agora. Ela vai até a fila e pega o último pacote que sobrou:
- Thread 0 pega o Pacote F [15]
```

**Exemplo prático**

```C
#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel for num_threads(4) schedule(dynamic,2)
    for (int i = 0; i < 8; i++)
    {
        printf("Thread %d calculando %d\n", omp_get_thread_num(), i);
    }
    return 0;
}

/// bash

$ ./t.exe
Thread 1 calculando 2
Thread 1 calculando 3
Thread 1 calculando 6
Thread 1 calculando 7
Thread 3 calculando 4
Thread 3 calculando 5
Thread 2 calculando 0
Thread 2 calculando 1
```

## 8.3 guided

Também funciona com filas conforme vão terminando, porém o tamanho dos blocos começa grande e vai diminuindo ao longo do tempo.

- O tamanho do próximo bloco é o número de iterações que sobraram na fila dividido pelo número de threads.
- Economiza tempo de processador das threads ficarem indo e voltando a fila perguntando o que fazer.

### 8.4 Onde usar cada um?

A função `#pragma omp parallel for num_threads(x) schedule(runtime)` permite escolher o tipo da hora de executar com `export OMP_SCHEDULE=static`.

- **static:** Tarefas previsíveis e uniformes de qualquer tamanho
- **dynamic:** tarefas imprevisíveis e desequilibradas porém com volume menor.
- **guided:** tarefas imprevisíveis e desiquilibradas porém com volume gigante.

