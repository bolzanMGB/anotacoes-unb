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

```C
#pragma omp parallel
{
    // Todas as threads executam isso ao mesmo tempo
    funcao(); 
}
```

2. Loop paralelo

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

**1. reduction:**

- Serve para acumular valores em loop.
- Sem que as threads atropelem o resultado uma das outras.
- É criado uma cópia privada da variável para cada thread.
- No final o OpemMP junta os resultados.

```C
int soma = 0;

// O (+:soma) diz: crie cópias e, no fim, junte tudo somando
#pragma omp parallel for reduction(+:soma)
for (int i = 0; i < 1000; i++) {
    soma += i; 
}
// Aqui, 'soma' tem o resultado perfeito e seguro
```

**3. critical**

- Serve para as threads acessarem o bloco uma por vez.
- Garante exclusão mútua.
- É formado uma fila para acessar.

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

**3. atomic:**
- Semelhante a critical, porém focada em uma única linha de código.
- Não cria travas.
- Usa o hardware, mais precisa.

**2.single**

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

**3. master**
- Mesma coisa da single.
- Porém sempre será a thread 0 que vai acessar a região.

**4. barrier:**

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
## 8.


