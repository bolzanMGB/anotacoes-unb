# Fundamentos de Sistemas Operacionais (FSO)

---

## 1. Conceitos Básicos

Um **computador** é formado por duas partes principais:

* **Hardware** (parte física)
* **Software** (programas e instruções)

### 1.1 Definição

**Tanenbaum**: Sistema Operacional (SO) é a parte fundamental do software que executa em **modo protegido**, com acesso total ao hardware e capacidade de executar qualquer instrução da máquina.

  * Exemplo: apenas o SO tem acesso direto ao disco, memória e dispositivos. Aplicativos precisam solicitar esse acesso ao SO.

**Machado e Maia**: O SO é uma aplicação capaz de executar de forma **assíncrona**, em vez de linear.

  * Exemplo: podemos ouvir música, baixar arquivos e usar antivírus ao mesmo tempo; se fosse síncrono, só rodaria uma tarefa por vez.

### 1.2 Funções

**Abstração do hardware (máquina estendida / máquina abstrata):**

- O SO atua como interface entre usuário e computador.
- Inicialmente, programadores precisavam conhecer linguagem de máquina e hardware em detalhes.
- Atualmente, o SO esconde a complexidade, simplificando e tornando o uso mais seguro.

**Compartilhamento de recursos:**

O SO gerencia recursos físicos (CPU, memória, disco, dispositivos) e lógicos de forma organizada e protegida.
- **Exemplo multiusuário:** o SO organiza impressões de vários usuários em uma mesma impressora.
- **Exemplo monousuário:** em um laptop, o SO organiza múltiplas tarefas simultaneamente.

**Responsabilidades do SO:**

  * Gerenciar dispositivos (HD, memória, CPU, periféricos);
  * Controlar operações de leitura/escrita;
  * Transferir dados entre hardware e memória;
  * Informar programas sobre conclusões de operações;
  * Definir quem pode acessar quais recursos.

---

## 3. Classificação dos Sistemas Operacionais

### 3.1 Monoprogramáveis / Monotarefa

* Primeiros a surgir.
* Executam apenas uma aplicação por vez.
* Todos os recursos são dedicados a uma única tarefa.

### 3.2 Multiprogramáveis

* Permitem que múltiplos programas compartilhem recursos.
* Enquanto um programa espera por E/S, outro pode usar o processador.
* Implementação mais complexa.

### 3.2.1 Classificação por número de usuários:
* **Monousuário**
* **Multiusuário**

### 3.2.2 Classificação pela forma de gerenciamento:

**Batch (em lote):**

* Programas armazenados e processados em lotes, sem interação do usuário.
* Exemplo: geração de boletos de clientes.

**Tempo compartilhado:**

* Divisão do tempo do processador em fatias (time-slice).
* Usuários interagem diretamente com o SO.
* Alternância rápida → aparência de simultaneidade.
* Exemplo: celular executando vários aplicativos.

**Tempo real:**

* Cumprimento rígido de prazos temporais.
* Pontualidade > desempenho.
* Exemplo: controle de tráfego aéreo, airbags, indústria automobilística.

### 3.3 Sistemas com Múltiplos Processadores

* Dois ou mais processadores trabalhando em conjunto.
* Vários programas executados em paralelo.
* Maior desempenho, escalabilidade e disponibilidade.

**Tipos:**

* **Fortemente acoplados:** memória compartilhada.
* **Fracamente acoplados:** memórias independentes.

---

## 4. Sistemas Operacionais Usuais

### 4.1 Computadores Pessoais

* Desktop, notebooks.
* Exemplo: Windows 10, Ubuntu, Fedora.

### 4.2 Servidores

* Objetivo: atender vários usuários simultaneamente.
* Serviços: web, e-mail, autenticação.
* Exemplo: Windows Server 2008, CentOS, Red Hat.

### 4.3 Embarcados

* Equipamentos que não aparentam ser computadores.
* Exemplo: Android, iOS, sistemas embarcados de TVs, micro-ondas, carros.

---

## 5. Estrutura dos Sistemas Operacionais

### 5.1 Básico

* O núcleo (kernel) é responsável por oferecer serviços essenciais.
* Comunicação com o núcleo:

  * **Chamadas de sistema (system calls):** exemplo, criar/escrever arquivos.
  * **Utilitários:** interfaces gráficas (gerenciador de arquivos, tarefas).
  * **Linguagem de comando:** terminal (prompt de comando, shell).

### 5.2 Funções do Núcleo

* Tratamento de interrupções e exceções.
* Criação e eliminação de processos e threads.
* Comunicação e sincronização entre processos.
* Escalonamento de tarefas.
* Gerência de memória e arquivos.
* Controle de dispositivos de E/S.
* Suporte a redes locais e distribuídas.
* Contabilização e auditoria de recursos.

### 5.3 Modo de Acesso

* **Modo Usuário:** execução de instruções não privilegiadas.
* **Modo Kernel:** acesso total às instruções e recursos.

### 5.4 System Calls

* Permitem que aplicações solicitem serviços privilegiados do SO.
* Executadas em **modo kernel**.
* O processador alterna entre modo usuário ↔ modo kernel durante chamadas.

### 5.5 Arquiteturas do Núcleo

#### 5.5.1 Monolíticos

* Núcleo único formado por módulos compilados em um único programa.
* Apenas o SO roda em modo protegido.
* **Vantagem:** melhor tempo de resposta.
* **Desvantagem:** difícil manutenção.
* **Exemplo:** Linux.

#### 5.5.2 Em Camadas

* Dividido em camadas sobrepostas.
* Cada camada acessa apenas a imediatamente inferior.
* **Vantagens:** isolamento, proteção.
* **Desvantagens:** menor desempenho, mais trocas de modo.
* **Exemplos:** THE, MULTICS.

#### 5.5.3 Máquinas Virtuais

* Camada intermediária que cria máquinas virtuais independentes.
* Cada VM possui cópia virtual configurável do hardware.
* **Vantagens:** isolamento, consolidação de servidores, testes.
* **Exemplo:** VMware ESX, VirtualBox.

#### 5.5.4 Microkernel

* Modelo cliente-servidor.
* Núcleo mínimo: gerencia processos, memória básica, IPC e interrupções.
* Serviços do SO implementados em nível usuário.
* **Vantagens:** estabilidade, segurança.
* **Desvantagens:** implementação complexa, menor desempenho.

#### 5.5.5 Exokernel

* Núcleo mínimo que apenas gerencia recursos básicos (CPU, memória, disco).
* Aplicações acessam diretamente o hardware.
* **Vantagens:** alta performance, customização.
* **Desvantagens:** complexidade de uso.

#### 5.5.6 Contêineres

* Alternativa às máquinas virtuais.
* Não emulam hardware nem rodam um SO completo.
* Compartilham o mesmo kernel, mas têm bibliotecas isoladas.
* **Exemplo:** Docker.

---

## 6. Considerações Finais

* O Sistema Operacional é essencial para abstrair, organizar e proteger recursos.
* Diferentes arquiteturas e classificações atendem a necessidades distintas (tempo real, multiprogramação, servidores, embarcados).
* Evoluções recentes como **máquinas virtuais** e **contêineres** expandem seu papel para ambientes de nuvem e escalabilidade.
