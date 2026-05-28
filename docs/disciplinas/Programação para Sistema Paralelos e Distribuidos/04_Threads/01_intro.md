# Threads

## 1. Arquiteturas Paralelas e Taxonomia de Flynn

O processador funciona em um ritmo determinado pelo seu clock. Em cada clock, a unidade de processamento (CPU) executa uma operação (soma, leitura de memória, comparação, etc).

A taxonomia de Flynn divide os processados com base no número de fluxos de instruções e dados simultâneos.


**1. SISD (Instruction Single Data Stream)**

- Presence em processadores convencionais.
- CPU busca apenas uma instrução do programa por Clock.
- Essa instrução é aplicada a apenas um único item de uma vez.
- Exemplo:
    - CPU busca uma instrução de somar.
    - Há uma lista com 100 números.
    - Processador vai somar os números 1 por vez.
    - Repetir a instrução 50 vezes.

**2. SIMD (Single Instruction Multiple Data Streams)**

- CPU busca apenas uma instrução do programa por Clock.
- Essa instrução é aplicada a vários item de uma vez.

**4. MISD (Multiple Instruction Single Data Streams)**

- Bem restritivo e sem implementações comerciais.
- CPU busca várias instruções do programa por Clock.
- Essa instrução é aplicada a um item por vez.

**3. MIMD (Multiple Instruction Multiple Data Stream)**

- É a arquitetura dominante hoje em dia.
- CPU busca várias instruções do programa por Clock.
- Essa instrução é aplicada a vários item de uma vez.


## 2. Organização da memória

Nos MIMD existe diferentes formas de organizar a memória.

### 2.1 Aspecto Lógico da Memória

É como o programador vê a memória.

**1. Memória Compartilhada:** Processadores enxergam um espaço de endereçamento único. Isso facilita a programação e torna a comunicação muito eficiente.

**2. Memória Privativa:** Processadores enxergam diferentes espaços de memória. Cada um tem o seu. Comunicação ocorre por troca de mensagens.

### 2.2 Aspecto Físico da Memória
É como os dados percorrem os fios e barramentos em sistemas de memória compartilhada.

**1. Memória Distribuída - Non-Uniform Memory Access (NUMA):** Memória é dividida em módulos, cada módulo está proximo a um processador.

**2. Memória Centralizada - Uniform Memory Access (UMA):** Memória se encontra na mesma distância de todos os processadores. Nela a comunicação é muito mais eficiente, porém necessita sincronização.


## 3. Modelos de Programação Paralela

Programação Paralela é a execução coordenada de tarefas para a solução de um único problema, é necessário comunicação entre elas. Criar várias threads não garante que um programa seja, de fato, paralelo.

**1. Programação por Memória Compartilhada:**

- Quando os processos e threads podem acessar a mesma região de memória.
- A comunicação é feita por variáveis armazenadas em um espaço de memória comum.
- Ferramentas comuns: Pthreads, threads em C++ e threads em Java.
- Maior risco são as condições de corrida, que devem ser tratadas com primitivas de sincronização

**2. Programação por Troca de Mensagens:**

- Não existe espaço de memória em comum.
- Cada processo possui sua própria memória privada.
- Comunicação entre processos é feito pelo envio de sinais e dados (mensagens).
- Comunicação pode ser entre apenas dois processos ou coletiva (mais de dois).
- Resolve o risco de condições de corrida.
- Porém muito suscetível a deadlocks.
- Deve-se utilizar algum suporte de comunicação:
    - MPI (Message Passing Interface).
    - PVM (Parallel Virtual Machine).


## 4. Threads

### 4.1 Funcionamento das threads

**Processos vs Threads:**

Um processo carrega o ambiente, ou seja, o espaço de endereçamentos, arquivos. etc. Já uma thread corresponde ao estado de execução de um processo. Um processos pode ter uma ou várias threads.

**Visão Unificada do Kernel Linux**

Independente da forma como processos e threads são criados, a diferenciação de threads e processos somente existe para o programador. Para o kernel do Linux, toda linha de execução é representada internadamente pela mesma estrutura de dados: a `task_struct`. Por baixo dos panos todas as formas de criar processos/threads usam a mesma chamada `clone()`, o que diferencia um do outro são os parâmetros passados.

### 4.2 Criações de Threads

**1. Suporte Nativo:**

Há um modelo de baixo nível para criar processos. Todo SO possui comando nativos para conversar diretamente com o Kernel do SO. Ele vai ser o responsável por administrar esses processos.

Alguns comandos são: `fork()`, `getpid()` e `kill()`

**2. Bibliotecas de Alto Nível (OpenMP)**

Para poupar o programador de ter que lidar com a complexidade de chamadas de sistemas manualmente, há diversos frameworks que fornecem abstração para criação de threads. Somente é necessário dizer o que dever ser rodado em paralelo.

O principal framework é o `OpenMP`. As threads geradas por ele compartilham o mesmo espaço de memória.

## 5. Avaliação de Desempenho

Threads ocasionam concorrência e aumento da complexidade. Desde modo nem todo código possuem necessidade serem paralelizados. A medida que o problema aumenta pode ser que o overhead de comunicação diminua e eficiência Há diversas formas de mensurar o ganho de tempo real com o uso de threads:

**1. Speedup:** É a razão entre o tempo do programa serial original e o tempo paralelo.

$$\mathbf{Speedup = \frac{T_{serial}}{T_{paralelo}}}$$

**2. Eficiência:** É a razão entre o Speedup e o número de processadores. Indica o o rendimento do núcleo. O gráfico de eficiência pode ser:

- Superlinear: E > 1.
- Linear: E = 1.
- Sublinear: 0 < E < 1.
- Retorno negativo: E < 0.

**7. Lei de Amdahl:**

- S é uma parte que precisa ser executada serialmente

## 6. Medindo Desempenho

- É necessário rodar mais de uma vez.
- `3 a 10 vezes` é uma quantidade aceita pela maioria da comunidade científica.

**Ferramentas/Programas para medir desepenho**

1. `/usr/bin/time`.

2. `perf stat -r 3`