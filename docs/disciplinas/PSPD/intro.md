# Introdução Sistemas Distribuídos

---

## 1. Introdução

Até meados dos anos 80, o cenário da computação era dominado pelos Mainframes: máquinas gigantescas (do tamanho de salas inteiras) que exigiam infraestruturas complexas de refrigeração e orçamentos milionários. Por serem tão caros e raros, esses computadores operavam de forma isolada; as organizações possuíam apenas algumas unidades que não "conversavam" entre si.

Essa lógica foi quebrada por dois avanços fundamentais: a dos microprocessados e das redes de alta velocidade

Até então limitados a tarefas simples (como calculadoras), os microprocessadores deram um salto de potência graças à Lei de Moore. A miniaturização dos componentes permitiu colocar milhões de transistores em um único chip, reduzindo o tamanho físico e o consumo de energia, enquanto a velocidade de processamento disparava.

Assim, tornou-se muito mais eficiente e barato comprar 1.000 microcomputadores de mil dólares cada do que investir em um único Mainframe de milhões de dólares. Embora o Mainframe fosse potente, um conjunto de mil máquinas menores oferecia um poder de processamento somado muito maior por uma fração do preço.

Diante disso, o desafio deixou de ser o hardware e passou a ser o software: como fazer mil máquinas independentes trabalharem juntas? Foi dessa necessidade que nasceram as redes e, principalmente, os Sistemas Distribuídos.

Embora ja existissem protótipos de redes desde os anos 60, foi nessa época que as LANs e WANs atingiram maturidade técnica e comercial para suprir a necessidade da conexão entre microcomputadores.

O resultados dessas tecnologias foi a viabilidade ao decorrer dos anos de montar uma rede sistemas de sistemas de computação, ou sistemas distribuídos, com vários computadores conectados por uma rede de alta velocidade, que substituiu os sistemas centralizados/monoprocessadores anteriores, que eram centralizados em um único computador e seus periféricos.

**Nota:** Apesar disso tudo, os Mainframes não morreram. Eles evoluíram, encolheram para o tamanho de uma geladeira e hoje são máquinas altamente especializadas para processamento de transações críticas (como as de grandes bancos), onde a centralização ainda é uma vantagem de segurança.


## 1. Definição

**Tanenbaum:** Um conjunto de computadores independentes conectados em rede em que os processos e recursos estão espalhados em diferente computadores e que se apresenta a seus usuários como um sistema único e coerente.

- Consiste em componentes autônomos.
- Usuários acham que estão tratando de um único sistema.

**Colouris:** Sistema no qual componentes localizados em
computadores interligados em rede se comunicam e coordenam suas ações apenas passando mensagens

- Não há visão do usuário nessa definição.

---

## 2. Características Importantes:

**Simplificação para o usuário:** O sistema oculta que seus recursos estão distribuídos em várias máquinas. Assim, o usuário não percebe sua organização interna, nem que se trata de vários sistemas. Exemplo: Quando você acessa o Google, não sabe (e não precisa saber) em qual servidor ou país sua busca está sendo processada.

**Escalabilidade:** Facilidade de aumentar a capacidade do sistema conforme a demanda cresce. Pode-se aumentar a RAM/CPu ou adicionar novas máquinas.

**Concorrência:** Como existem vários computadores, vários processos acontecem ao mesmo tempo.

**Falta de um relógio global:** Em um sistema centralizado, há um único relógio. Em sistemas distribuídos, cada máquina tem seu próprio tempo interno, resultando em limitações na sincronização exata do tempo.

**Falhas independentes:** Um nó falha sem interromper o sistema todo.

---

## 3. Sistemas Descentralizados VS Sistemas Distribuídos

Sistemas Descentralizados: Dividido em vários computadores por necessidade, enfatizando autonomia e independência como objetivo. Se tentar centralizar o sistema quebra. Exemplos:

- IA: Modelos de IA são grandes demais para uma placa de vídeo só, portanto o treinamento precisa ser dividido .
- Blockchain: Garante autonomia, ninguém precisa confiar em ninguém.
- Geografia e Latência (Edge Computing): Em vez de enviar um arquivo para um servidor gigante e distante (processo demorado), utilizar de um mini-computador, como uma RaspberryPI. Exemplo: câmeras de segurança.
- Leis: Muitas vezes, dados de usuários europeus precisar fica na Europa.

Sistemas Distribuído: Dividido em vários computadores suficientemente para que o sistema seja rápido e confiável, enfatizando que o usuário não perceba a divisão. Exemplos: 

- Sistemas NAS: Servidor acessado por Wi-Fi que aparece como Unidade Z e esconde toda a bagunça do hardware.
- Sistemas CDNs: Como a Netflix e Youtube. Quando você da play, você não perceve que o vídeo vem de um servidor perto de você e não da sede nos EUA.

| Modelo | Localização do Processamento | Objetivo Principal |
| :--- | :--- | :--- |
| **Centralizado** | Uma única máquina (Mainframe). | Controle total e simplicidade lógica. |
| **Descentralizado** | Espalhado por **necessidade** (técnica, legal ou de confiança). | Autonomia, privacidade e falta de um "dono" central. |
| **Distribuído** | Espalhado por **estratégia** (escala e performance). | **Transparência**: o usuário enxerga o sistema como uma máquina única. |
---

## 4. Metas/Desafios/Design Goals

### 4.1 Heterogeneidade
 A realidade física é heterogênea, ou seja, compostas por uma variedade de hardwares, sistemas operacionais, redes e linguagens de programação. Os SDs tem como objetivo "disfarçar" essa bagunça e faz isso através de um Middleware.

**Middleware:** Uma camada de software, situada entre uma camada de nível mais alto (usuários e aplicações) e uma subjacente (sistemas operacionais), que oferece um modelo computacional de sistema único. 

![Inserção](../../assets/pngs/93.png){align=center }

### 4.2 Abertura do Sistema

**Interfaces publicadas:**
Um sistema aberto é um sistema que possui sua especificação e documentação (as "regras do jogo", o que o sistema faz, como ele faz) de suas interfaces publicadas e disponíveis para os desenvolvedores através de portais ou repositórios. Isso garante a ele a capacidade de ser estendido e reimplementado de diferentes maneiras.

Um sistema distribuído deve ser aberto, deve oferecer fácil acesso a seus recursos e pode ser expandido.

**Interoperabilidade:** Diferentes sistemas (de marcas diferentes) conseguem trabalhar juntos. 

**Interoperabilidade:** Você pode pegar o seu código e rodá-lo em outro sistema operacional ou hardware que siga as mesmas regras, sem precisar reescrever tudo.

**Separação entre Mecanismo e Política:** A clara separação gera flexibilidade. Mecanismo é "como" algo é feito (ex: técnica de criptografia usada). Política é "o que" deve ser feito (ex: qual nível de segurança o usuário precisa ter).

**Uniformidade e Extensibilidade:** Um sistema aberto nunca esta "pronto", ele sempre permite que você adicione novos serviços sem precisar desligar o sistema inteiro ou mexer no que já esta funcionando.

### 4.3 Segurança:

Muitos dados e recursos em sistemas distribuídos tem alto valor intrínseco e devem ser protegidos Essa segurança abrange três componentes: **confidencialidade** (proteção da exposição do conteúdo para pessoas não autorizadas), **integridade** (proteção contra alteração ou dano) e **disponibilidade** (proteção contra interferência com os meios dea cesso aos recursos).

### 4.4 Escalabilidade
Escalabilidade é a capacidade de um sistema continuar operando de formar eficiente mesmo com um aumento significativo no número de usuários e recursos. Principais desafios: controlar o custo dos recursos físicos, controlar a perda e gargalos de desempenho e impedir que os recursos de software se esgotem.

Á medida que a demanda por um recurso aumenta, deve ser possível, a um custo razoável, ampliar o sistema para atendê-la. Para isso deve-se evitar a centralização: sistemas com um único servidor, dados centralizados ou algoritmos que dependem de informações globais tornam-se gargalos de desempenho à medida que crescem.

Para que um sistema seja escalável, o custo dos recursos físicos deve ser, no máximo, proporcional ao número de usuários ou recursos presentes no sistema e a perda de desempenho deve ser manter em uma complexidade logarítmica em relação ao volume de dados.

### 4.5 Tratamento de Falhas
Em sistema distribuído as falhas são parciais, ou seja, alguns componentes falham enquanto outros continuam funcionando. Portanto, o tratamento de falhas é particularmente difícil.

**Detecção de Falhas:** Algumas falhas podem ser detectadas, por exemplo, com somas de verificação, outras são mais difíceis, ou mesmo impossíveis.

**Mascaramento de falhas:** É o processo de ocultar ou tornar falhas menos sérias.Dois exemplos são:retransmitir mensagens que não chegam e gravar dados de arquivos em dois discos.


### 4.6 Concorrência:
Em um sistema distribuído, tanto os serviços quanto os aplicativos fornecem recursos que podem ser compartilhados pelos clientes. Para uma organização, por exemplo, é muito mais eficiente compartilhar uma única impressora de alta performance ou um banco de dados central do que equipar cada estação individualmente.

Contudo, o compartilhamento introduz o desafio da **concorrência**: a possibilidade de que múltiplos clientes tentem acessar ou modificar o mesmo recurso simultaneamente. Sem o devido controle, as operações podem se "entrelaçar", gerando **riscos de inconsistência** e **condições de corrida** (onde o resultado final depende da ordem imprevisível de chegada das requisições). 

Para evitar que o estado do recurso seja corrompido, a integridade deve ser garantida no nível do **objeto**:
- **Responsabilidade do Objeto:** Não basta o servidor estar online; cada recurso compartilhado deve ser projetado para gerenciar seus próprios acessos concorrentes.
- **Mecanismos de Sincronização:** O uso de técnicas padrão, como **semáforos** ou travas (locks), é essencial para garantir que apenas um processo manipule dados sensíveis por vez, mantendo a coerência de todo o sistema distribuído.
Por

### 4.7 Transparência:

É definida como a ocultação, para um usuário final ou para um programador de aplicativo, da separação dos componentes em um sistema distribuído, de modo que o sistema seja percebido como um todo, em vez de como uma coleção de componentes independentes. Há oito formas de transparência:

**Transparência de Acesso:** Oculta diferenças na representação de dados e no modo de acesso a um
recurso

**Transparência de Localização:** Oculta o lugar onde um recurso está localizado fisicamente.

**Transparência de Migração:** Oculta que um recurso pode ser movido para outra localização física.

**Transparência de Realocação:** Oculta que um recurso pode ser movido para outra localização enquanto está em uso.

**Transparência de Replicação:** Oculta a existência de múltiplas cópias de um recurso para aumentar a disponibilidade.

**Transparência de Concorrência:** Oculta que
um recurso pode ser compartilhado por vários
usuários concorrentes sem interferência mútua.

**Transparência de Falha:** Oculta a falha e a
posterior recuperação de um recurso, permitindo
que a tarefa seja concluída.

**Transparência de Desempenho:** Permite que o sistema seja reconfigurado para melhorar o desempenho conforme a carga varia.

**Transparência de Escalabilidade:** O sistema pode expandir em escala sem alterar sua estrutura ou algoritmos.

**Transparência de Rede:** Engloba a transparência de acesso e localização.

### 4.8 Qualidade de Serviço:
Uma vez que a funcionalidade do sistema é atendida, devemos observar as **propriedades não funcionais** que determinam a experiência do usuário.

* **Confiabilidade e segurança:** fundamentos básicos para a integridade do sistema e dos dados.
* **Desempenho (Performance):** definido pela velocidade de resposta, rendimento computacional e, principalmente, pela capacidade de cumprir prazos finais (**pontualidade**).
* **Adaptabilidade:** capacidade do sistema de se ajustar a variações de configuração e disponibilidade de recursos.
* **Garantia de recursos:** para serviços críticos (como streaming de vídeo), o sistema deve ser capaz de reservar recursos de computação e rede para garantir que as tarefas sejam terminadas no tempo correto.

## 5. Sistema de Computação Distribuídos de Alta Performance
- Sistena de cimputação de cluster.
- Conjunto de estações de trabaçho ou PCs semelhantes, compostos por componentes comuns de mercado, conectados por uma rede local de alta velocidade.
- O grande atrativo foi que em um certo ponto ficou melhor construir supercomputadores usadno sistemas simples que são conectados.
- O nó de gerenciamento é responsável por receber tarefas e distribuir as tarefas entre os nós de processamento.
- Nós de processamento possuem um software simplificado quando comparados ao de gerenciamento.
- 95% é baseado em Linux.
- Algumas abordagens com uso de kernel simplificado e um kernel complexo são encontradas na literatura.
- Atualmente, a minimização da complexidade do software base da estação pode ser alcançada através do uso de contêiners.
- Sistema de computação em grade (grid).
- Sistemas com alto grau de heterogeneidade, não podendo assumir nada sobre sistemas, hardware.
- Sistema distribuído que conecta computadores distantes geograficamente, para criar um supercomputador virual.
- Modelos de simulação na engenharia, serviços, financeiros e aplicações.
- O grid tmb pode ser visto como uma federação de computadores de diferente dominios administrartivos, permitindo a colaboração de grupos de pessoas.
- Exempĺo CERN
- F@h
- Foster: arquitetura em camads: base, conectividade, recurso, coletiva e aplicação
- Bases: camada-base, provê interfaces para recursos locasi e um lugar específico, funções que obtêm estados e recursos.
- A soma das camadas são o middle ware do grid.
-Padrao Open GRid Service Archictecture



## 5. Sistema de Informação Distribuido

Os componentes foram separados e notadamente foram distinguidos as atividades de computação



## 5. Sistema de Processamento de Transações
ACID
- Atomicas: indivisivel, ou toda transacao é executada ou nada é
- Consistente: a transação não viola invariantes de sistema.
- Isolada: transações concorrentes não interferem.
- Durpaveis: permanente quando finalizadas. 

## 5. Sistema distribuidos Ubiquos
- Sistemas Doméstico;
- Sistemas de Saúde Eletrônicos
- Rede de Sensores

##