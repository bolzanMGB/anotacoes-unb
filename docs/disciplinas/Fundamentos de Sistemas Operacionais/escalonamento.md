# Escalonamento

---

## 1. Quando Ocorre

O **escalonamento** ocorre quando há necessidade de decidir qual processo em estado **pronto** deve assumir a CPU. Situações típicas:

* Quando um processo termina;
* Quando um processo é bloqueado;
* Quando um novo processo é criado (reavaliar prioridades);
* Quando ocorrem interrupções.

O processo em execução pode se tornar não apto e outro precisa ser escolhido. Essa decisão é feita pelo **escalonador**, que usa um **algoritmo de escalonamento**.

---

## 2. Classificação dos Algoritmos

**Não-preemptivo:**

  * O processo selecionado executa até ser bloqueado ou liberar voluntariamente a CPU.

**Preemptivo:**

  * O processo é executado por um tempo máximo (quantum). Se não terminar, é suspenso e outro assume.
  * Mais equilibrado e usado na maioria dos SO modernos.
  * Dificulta a programação de processos concorrentes.

---

## 3. Critérios de Escalonamento

* **Justiça:** garantir que todos os processos tenham acesso justo à CPU.
* **Eficiência:** manter a CPU ocupada sempre que houver trabalho.
* **Tempo de resposta:** minimizar o tempo de resposta para usuários interativos.
* **Turnaround:** minimizar o tempo total entre o lançamento e o término do processo.
* **Tempo de espera (waiting line):** reduzir o tempo médio na fila de prontos.
* **Throughput:** maximizar o número de processos concluídos por unidade de tempo.

---

## 4. Algoritmos Clássicos

### 4.1 First Come First Served (FCFS)

**Características:**

- Processo executado na ordem de chegada.
- **Não-preemptivo.**

- Baseado em fila FIFO.

**Vantagens:** implementação simples, CPU sempre utilizada.

**Desvantagens:** processos longos podem atrasar os demais.

**Critérios:**

- Justiça: não (um processo pode monopolizar).
- Eficiência: sim.
- Tempo de resposta: ruim em caso de tarefas longas.
- Turnaround: não necessariamente minimizado.
- Waiting time: alto para processos curtos.
- Throughput: baixo se tarefas iniciais forem longas.

### 4.2 Round-Robin (RR)

**Características:**

* Cada processo recebe a CPU por um **quantum** fixo.
* Alternância circular entre processos.

**Vantagens:** justo, adequado para sistemas interativos.

**Problema:** definir quantum ideal.

  * Quantum longo → similar a FCFS.
  * Quantum curto → muitas trocas de contexto, perda de eficiência.
  * Tempo de troca de contexto deve ser menor que o tempo médio de execução.

### 4.3 Escalonamento com Prioridades

**Características:**

* Cada processo recebe uma prioridade.

**Atribuição de prioridades:**

  * **Estática:** classes fixas de prioridade.
  * **Dinâmica:** ajustada pelo sistema conforme comportamento.

    * Processos de E/S → alta prioridade.
    * Fórmula exemplo: prioridade = 1/f, onde *f* é o quantum usado na última rodada.

### 4.4 Shortest Job First (SJF)

**Características:**

* Executa primeiro o processo com menor tempo de execução estimado.
* Ideal para sistemas em lote.

**Vantagem:** minimiza turnaround.

**Desvantagem:** difícil prever tempo de execução real.

---

## 5. Deadlock

**Deadlock** ocorre quando dois ou mais processos ficam bloqueados permanentemente, esperando por recursos que nunca serão liberados.

**Exemplo:**

* Processo A tem o recurso 1 e pede o recurso 2.
* Processo B tem o recurso 2 e pede o recurso 1.

**Condições necessárias para deadlock:**

1. **Exclusão mútua:** recursos não podem ser compartilhados.
2. **Posse e espera (hold and wait):** processos mantêm recursos já adquiridos enquanto esperam por novos.
3. **Não-preempção:** recursos não podem ser retirados à força.
4. **Espera circular:** cadeia de processos em que cada um espera por recurso do próximo.

---

## 6. Considerações Finais

* O escalonador é fundamental para garantir **uso eficiente da CPU** e **atendimento justo aos processos**.
* A escolha do algoritmo depende do ambiente (lote, interativo, tempo real).
* Deadlocks representam riscos que exigem **prevenção, detecção e recuperação**.
