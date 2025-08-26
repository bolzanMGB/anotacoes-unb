# Processos

---

## 1. Modelo de Processo

Um **processo** pode ser visto em duas dimensões:

* **Ambiente:** espaço de endereçamento + contexto de software.
* **Execução:** contexto de hardware.

**Tipos de modelos de processos:**

* **Heavyweight:** processo tradicional.
* **Lightweight:** threads (processos leves).

---

## 2. O que é um Processo

Em sistemas multiprogramáveis, existe um **pseudoparalelismo**: ilusão de que vários programas rodam ao mesmo tempo.

Cada processo possui sua própria "CPU virtual", mas, na prática, a CPU alterna entre processos rapidamente.

Ao longo do tempo, todos progridem, mas em um instante dado apenas um executa.

**Analogia do bolo:**

* Confeiteiro → CPU.
* Receita do bolo → Programa (passivo).
* Fazer o bolo → Processo (ativo).
* Ingredientes → Dados de entrada.
* Bolo pronto → Dados de saída.
* Se surgir outra tarefa prioritária (ex: socorrer criança), o confeiteiro interrompe o bolo, memoriza o ponto, faz a nova tarefa, e depois retorna.

**Conceito:** processo é um **programa em execução** junto com seu contexto:

* Pilha de execução.
* Apontador para a pilha.
* Contador de programa (próxima instrução).
* Valores dos registradores.

---

## 3. Criação de um Processo

Um processo pode ser criado em situações como:

* Inicialização do sistema:

  * **Foreground:** processos que interagem com o usuário.
  * **Background:** processos sem interação direta (daemons, serviços).
* Chamada de sistema feita por outro processo.
* Solicitação do usuário.
* Execução de tarefas em lote.

---

## 4. Término de Processos

* **Normal (voluntário):** terminou sua tarefa ou o usuário encerrou.
* **Erro (voluntário):** término por falha detectada.
* **Erro fatal (involuntário):** término forçado por falha grave.
* **Eliminado por outro processo (involuntário).**

---

## 5. Hierarquia de Processos

* Processos criados por outros mantêm relação de **pai-filho**.
* Em sistemas Unix/Linux, todos descendem do processo `init`.
* Windows não possui a mesma hierarquia explícita.

---

## 6. Estados de Processos

Processos interagem, comunicam-se e sincronizam-se. Seus estados podem ser:

* **Executando:** em uso da CPU.
* **Pronto:** apto a executar, aguardando a vez.
* **Bloqueado:** aguardando evento externo.

  * Exemplo: leitura em disco, entrada de usuário, dependência de outro processo.

**Transições típicas:**

1. Executando → Bloqueado (aguarda evento).
2. Executando → Pronto (usou tempo máximo).
3. Pronto → Executando (escalonado).
4. Bloqueado → Pronto (evento chegou).

**Classificação Bound:**

* **CPU-bound:** usam mais tempo de CPU.
* **I/O-bound:** ficam mais tempo bloqueados esperando E/S.

---

## 7. Implementação de Processos

### 7.1 Tabela de Processos

* Contém informações essenciais sobre cada processo.
* Cada processo tem um identificador (**PID**).
* Campos incluem gerenciamento de memória, arquivos abertos, registradores.
* **Troca de contexto:**

  * Salva os registradores e o estado do processo.
  * Carrega o estado de outro processo.
  * Permite retomar a execução como se não tivesse sido interrompido.

### 7.2 Tabela de Descritores de Interrupção (IDT)

* Tabela usada pelo processador para tratar interrupções.
* O **vetor de interrupção** é o índice da entrada na IDT.
* Cada dispositivo tem uma entrada associada.

**Passo a passo de uma interrupção de disco:**

1. Processo de usuário está em execução.
2. Disco gera interrupção (operação concluída).
3. CPU salva automaticamente o estado do processo (contadores, registradores).
4. Processador consulta a **IDT** com o vetor de interrupção.
5. Carrega a rotina de tratamento correspondente (assembly).
6. Rotina de tratamento processa a interrupção (ex: lê dados do disco, desbloqueia processos).
7. Escalonador decide se o processo interrompido retoma ou outro será executado.
8. Registradores e contador de programa são restaurados → execução continua.

---

## 8. Considerações Finais

* Processos são a **unidade fundamental de execução** em sistemas operacionais.
* O gerenciamento de processos envolve criação, execução, término, troca de contexto e escalonamento.
* A abstração de processos é essencial para permitir **concorrência, isolamento e multitarefa**.
