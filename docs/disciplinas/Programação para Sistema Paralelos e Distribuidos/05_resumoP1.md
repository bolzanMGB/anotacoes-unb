# Resumo P1

## 1. Introdução Sistemas Distribuídos

- Mainframes.
- Lei de Moore: microprocessadoes e redes de alta velocidade.

### 1.1 Conceito

- Conceito Tanembaum: tem a visão do usuário

> Um conjunto de computadores independente conectados entre si compartilhando processos e recursos e que se apresentam como um sistema único para os usuários.

- Conceito Colouris:

> Sistema no qual componentes localizados em computadores interligados em rede se comunicam e coordenam suas ações apenas passando mensagens.

### 1.2 Características

- Simplificação para o usuário: veem como uma coisa só.
- Escabilidade: aumentar mais CPUs facilmente.
- Concorrência: varios processos au mesmo tempo.
- Falta de um relógio global: cada pc tem seu relógio.
- Falhas independentes:

### 1.3 Descentralizados vs Distribuídos

**Descentralizados:** em vários pcs por necessidade, se centralziar quebra. Ex: IA, blockchain.

**Descentralizados:** em varios pcs somente por estrategia, ser mais rapido e mais escalavel. 

### 1.4 Dificuldades

**Heterogeneidade:** realidade física contem diversos hardwares (heterogeneidade), os SDs tem que disfarçar isso.

**Abertura do sistema:** deve conter suas interfacas publicadas.

**Interoperabilidade:** diferentes hardware conseguirem trabalhar entre si.

**Portabilidade:** programas rodarem em diferentes pcs.

**Extensibilidade:** o sistema deve permitir adicionar novos pcs sempre.

**Segurança:** recursos intrínsecos devem ser confidenciais para pessoas de fora, continuar integros apos alteração e disponíveis quando necessários.

**Escabilidade:** continuar funcionando eficientemente com o aumento de usuários e recursos.

**Falhas:** devem ser parciasi.

**Transparencia:** parecer para o usuário como um todo em relação a acesso, localização, concorrencia e etc.

### 1.5 Tipos

#### 1.5.1 Sistemas de Computação Distribuídos e de Alta Perfomance
Focam em força bruta computacional. são divididos em:

**1. Sistemas de Computação de Cluster:** vários pcs homogeneos simples são conectados entre si numa rede local de alta velocidade formando um supercomputador.

- Cada nó com o mesmo SO.
- Há um nó mestre que distribui as tarefas.

**2. Sistemas de Computação em Grade:** formando por máquinas heterogêneas ao redor do mundo criando um supercomputador virtual.

- Permite a colaboração entre instituições.
- Organizado em camadas: base, conectividade, recursos, coletiva e aplicação.

#### 1.5.2 Sistema de Informação Distribuídos

Sistemas de banco de dados gigantes. neles pare do processamento lógico ocorre tmb no pc do usuário.

**1. Sistemas de Processamento de Transações (SPT):** foco em integridade em sistemas bancários, nao dar erro

- Transações ACID: 
    - Atômicas: como se fossem uma só (tudo ou nada).
    - Consistentes:invariantes devem ser válidas antes e após.
    - Isoladas: transações concorrentes são independentes.
    - Duráveis: irreversíveis.

**2. Integração de Aplicações Empresariais (EAI)**: foco na comunicação entre diferentes bancos de dados de uma empresa (na mesma lingua).

- Usa RPC.
- Usa IPC.
- Desvantagem de possui forte acoplamento: chamador e chamado precisam estar ligados ao mesmo tempo. por isso foram substituidos pelo MOM.

**3. Sistemas Distribuídos Ubíquos e Pervasivos:** focam em invisibilidade.

- Processamento espalhado por diversos pequenos nós.
- Celulares, sensores e smartwatches.
- Pervasivos: discretos e ficam invisíveis organicamente ao ambiente.
- Ubíquos: evolução dos pervasivos, além de serem invisíveis estão em disponiveis em qualuqer lugar e momento
- Pilares:
    - Distribuição: precisa estar na rede para acessar recursos.
    - Sensibilidade ao contexto: sabe onde voce esta, o que esta fazendo, quem esta com vc.
    - Autonomia/composicao adhoc: se autogerencia sozinho: exemplo wifi.
    - Inteligencia: usa IA para mudanças brucas