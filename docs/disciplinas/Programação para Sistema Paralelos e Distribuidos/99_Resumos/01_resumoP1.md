# Arquitetura

## 1. Introdução Sistemas Distribuídos

Mainframes -> Lies de Moore -> Microprocessadoes e Redes de alta velocidade.

### 1.1 Conceito

- Conceito Tanembaum: tem a visão do usuário
- Conceito Colouris: mais sobre comunicaçãp

### 1.2 Características

- Homogeneidade
- Middleware.
- Transparência.
- Interfaces publicadas.
- Interoperabilidade
- Portabilidade
- Extensibilidade.
- Segurança
- Escalabilidade
- Mascaramento de Falhas
- Concorrência;

### 1.3 Finalidades

1. Sistemas de Computação Distribuídos e de Alta Perfomance
- 1.1 Sistemas de Computação de Cluster: 
        - Homogeneo.
        - Local
- 1.2 Sistemas de Computação em Grade: 
        - Diferente.
        - Virtual

2. Sistema de Informação Distribuídos
- 2.1 Sistemas de Processamento de Transações (SPT): 
    - Integridade,.
    - Sistemas bancários.
    - Monitor TP controla as subtransações
- 2.2 Integração de Aplicações Empresariais (EAI): 
    - Comunicação.
    - Para empresas
- 2.3 Sistemas Distribuídos Ubíquos e Pervasivos: 
    - Focam em invisibilidade.
    - Wifi

## 2. Estilos Arquitetônicos 
Organização do Software

1. Arquitetura em Camadas.
- 1.1 Arquitetura Cliente-Servidor
- 1.2 Arquitetura em Múltiplas Camadas

2. Arquitetura Baseada em Serviços
- 2.1 Arquitetura Baseada em Objetos.
- 2.2 Arquitetura Baseada em Microsserviços.
- 2.3 Arquitetura Baseada em Recursos.

3. Arquitetura Baseadas Publicar-Subscrever
- 3.1 Baseada em Eventos
- 3.2 Espaço de Dados Compartilhados

### 2.1 Arquitetura em Camadas:
Fluxo: requisições de cima para baixo, respostas de baixo para cima.

#### 1. Cliente e Servidor
- Cliente: é ativo, envia um requisição ao servidor.
- Servidor: é passivo, esperando continuamente uma requisição para responder.

**Cliente Gordo e Magro**
- Cliente magro:
    - Possui pouco código (só interface).
    - Maioria do processamento e dados ficam no servidor.
    - Fácil de gerenciar.
    - Tendencia atual.
- Cliente gordo: 
    - possui  muito código.
    - cuida da interface e parte do processamento.
    - Díficl de gerenciar.

#### 2. Arquitetura de Múltiplas Camadas (IDP)
- Nível de Interface/Aplicação: janelas gráficas q o usuario lida.
- Nível de Processamento: lógica da aplicação
- Nivel de Dados: banco de dados

### 2.2 Arquitetura Baseada em Serviços
Os sistemas viram entidades

- Baseada em Objetos: funções remotas
- Baseada em Microserviços
- Baseada em Recursos: identificar recurso e utilizar metodos get, post

### 2.3 Arquiteturas Publicar-Subscrever
Há um middleware que faz a comunicação entre os sistemas.

- Desacoplamento no Espaço: remetende não quem é o destinatario e vice-versa.
- Descaoplamento no Tempo: remetendo e destinário nao precisam esta rodando ao mesmo tempo.

#### 1. Baseada em Eventos

- Um processa publicador anuncia um evento.
- Outros processos manifestam interesse.
- Desacomplado no espaço.
- Acoplado no tempo.

#### 2. Baseada em Dados Compartilhados

- Há um repositorio persistente.
- O processo publicador insere dados no repositorio.
- Os processos fazem buscas no repositorio para achar dados que eles querem.
- Desacoplado no espaço.
- Desacoplado no tempo.

## 3. Arquiteturas de Sistema

### 3.1 Distribuida Centralizada
- Assimetria: processos cliente e um servidor.
- Distribuição vertical: distribuição do processamento em níveis (Interface/Lǵica/Dados).

### 3.1 Distribuida Descentralizadas

#### 1. Peer-To-Peer

- Simetria: todos agem como cliente e servidor ao mesmo tempo.
- Distribuição horizontal: cada nó tem uma parte do sistema inteiro.
- Overlay-network: topologia virtual onde cada nó conhece somente alguns (precisa ir pulando).

**P2P Estruturada**
- Regras matemáticas rígicas.
- Topologia rigida.
- Tabela hash (DHT).

**P2P Não-Estruturadas**
- Não há regras rígidas.
- Se conectam de forma aleatória
- Muitas mensagens.
- Flooding.
- Ramdom Walk.

#### 2. BitTorrent

- P2P Não-Estruturado melhorado.
- Superpares: pcs mais potentes, sabem exatamente em qual nó um recursoe stá guardado.

### 4. Arquiteturas Híbridas
Aplicação real em empresas

**Computação em Nuvem:**
- A empresa não lida com o servidor, ele fica em um data center gerenciado por terceiros
- Serviço sob demanda e elasticidade rapida.
- Serviço diponivel pela inernet em qualquer lugar.
- Serviço mensurável.
- Pooling de recursos.

**Tipos de Serviço em nuvem:**
- IaaS: provedor te da o hardware virutal (máquina virtual).
- PaaS: provedor te da o ambiente de desenvolvimento pronto (voce so precisa codar).
- SaaS: provedor te da tudo, vc so usa (netflix).

**Computação de Borda:**
- Para resolver a latenca.
- Nao envia para nuvem, o dado é processado no lugar onde nasce.

**Computação em Névoa:**
- Para resolver a latencia.
- Nao envia para a nuvem, envia para um mini servidor loca.

### 5.Middleware

**Sistemas abertos:**
- Um bom sistema distribuido é tambem um sistema aberto.
- Um sistema com interfaces publicadas.
- Possui um repositorio publico com suas regras e funcionamentos documentadas.

**IDL**
- Linguagem neutra que faz uma ponte comum entre as outras linguagens
- Interoperabilidade: comunicação entre diferentes maquinas.
- Extensibilidade.

**wrapper/broker**
- casca/mediadores que traduz um código antigo para IDL.

# 4. Comunicação


1. RPC

2. Por envio de mensagens
    - 1.1 Sockets
    - 1.2 MPI (Message-Parrsing Interface)
    - 1.3 MOM (Message-Oriented Middleware)
        - 1.3.1 Filas
        - 1.3.1 Broker
        - 1.3.1 Protocolos (AMQP)

3. Multicasting
    - 3.1 Overlay-Network
    - 3.2 Flooding 
        - 3.2.1 Flooding TTL
        - 3.2.2 Flooding Probabilístico
    - 3.3 Disseminação Epidêmica (Gossip)
        - 3.1 Push 
        - 3.1 Pull 
        - 3.4 Push-Pull 


## 1. Introdução

**Modelo OSI**
- Modelo conceitual de comunicação em 7 camadas.
- Possui protocolos: regem o formato das mensagens.
    - Orientados a conexão: faz a conecão e depois envia
    - Não orientados a conexão: somente envia.
- FERTSAA.
- Quando manda uma mensagem ela desce nas camadas.
- Quando você recebe, ela sobe.

---

## 2. Protocolos Middleware
Faz o papel da camada de sessão e apresentação.

**Transiente X Persistente:**
- Transiente: middle so armazena a mensagem enquantoemissor e receptor estiverem online, depois é descartada.
- Persistente: middleware armazena a mensagem até o destinatario receber. Receptor e emissor não precissam estar onlines ao mesmo tempo.

**Síncrona X Assíncrona**
- Sincrona/Bloqueante: emissor é bloqueado durante a comunicação.
- Assincrona/Não-Bloqueante: emissor não é bloqueado e pode realizar outros processos.

---

## 3. RPC (Remote Procedure Call)
Fazer parecer que mensagens entre diferentes máquians estão acontecendo no mesmo PC. Bstrair.
São transiente e assincronas.

**Funcionamento:**

1. Apendice/stub do cliente:
- Uma função local do PC1 chama ela.
- Ela faz o empacotamento/mashalling do dos parametros, montando a mensagem.
- Chama o SO local.
- So loca, invez de ler os dadso, envia a mensagem pro SO do PC2.

2. Apendice/stub do servidor:
- SO do PC2 passa a mensagem pro stub do servidor.
- Stub do servidor faz o unmashalling/desempacotamente da mensagem.
- Chama o SO local.
- SO local le os dados (ou o que a função for).
- SO local manda a mensagem para função local.
- SEssa função faz o mashalling dnv.
- Chama o SO local e manda de volta para o PC1.

### 1 Passagem de parametros por valor
- Transforma os dados em uma cópia transmissível. 
- o mashalling e unmarhsalling

### 2 Por referencia
dificil e proibidas no geral;

---

## 4. Envio de mensagens direto
Não há abstração, os processo trocar mensagem de forma direta. 

### 1. Sockets
- Internet no geral.
- Canal bidirecional de comunicação
- Uso de comandos.
- É transiente

### 2. MPI (Message Parsing)
- Para computação de alto desempenho.
- Redes fechadas e seguras.
- Redes possui varios grupos e cada grupo possui processos (ID duplo).
- Redes utilizam esse par de ID livremente.
- É transiente

### 3. MOM (Messa Oriented Middlewaer)
- Persistente e assincronas.
- Middleware armazena as mensagens.
- Nao bloqueante.
- Nao precisa estar online ao mesmo tempo.
- Duram minutos, nao segundos.
- Suas implementações são:

#### 3.1 Filas de Mensagens
- Os sistemas conversam diretamente.
- O middleware orgazina as mensagems em filas.
- consumidor processa no seu proprio ritmo.

#### 3.2 Brokers

- O sistema mandama a mensagem pro Broker e ela vai formadno e organizando as filas.
- É um gerenciador de filas em ambientes com varios sistemas.

#### 3.3 AMQP (Advanced Message Queuing Protocol)
Padrão para o envio de mensagens

---

## 4. multicasting
Mensagem de um sistema para varios outros, nao um a um.

### 4.1 Overlay Network
- Nós se organizam em uma árvore.
- Um nó quer mandar uma mensager e vira a raiz.
- Os ros que querem receber se juntam nele formando uma árvore.
- Nó raiz envia mensagem para poucos (dois) e esses dois repassam para cada ramo da arvore.

**Problema (Link Stress)**

- Rede Overlay não é formada seguindos os enlaces (cabos) físcos.
- Uma mensagem pode acabar passando pelo mesmo caminho várias vezes (Link Stress).


### 4.2 Flooding
- Quando nao da para fazer uma arvore.
- Um nó recebe a mensagem e envia para todos seus vizinhos.
- Se ele ja recebeu ele ignora
- Mais simples.
- Pode gerar desperdicio de mensagens

1. Time to Live (TTL)
- Otimização
- Define número maximo que nos que a menxagem pode percorrer.
- Diminui o trafego

2. FLooding Probabilísitico
- Em vez de transmitir sempre, cada nó tem uma chance de transmiit.
- Diminui a garantia de alcance total

### 4.2 Gossip
- Nao envia para todos os vizinho
- Envia para alguns nós aleatorios.
- Esses nos infectados fazem a mesma coisa.
- Ate todos estiverem informados

1. Push
- Nós infectados mandam para outros nós.
- Bom no inicio

2. Pull
- Nós nao infectados tomam a uniciativa.
- Conversa com outro nó e pergunta se ele esta infectado
- Bom no final

3. Push/Pull
- Push no inicio
- Pull no final.


# 5. Coordenação

## 1. Sincronização de Relogios

**Cristal de Quartzo**
- Todo computador possui um.
- Esse cristal gera uma vibração estável ao recber um tensão eletrica.
- A cada X vibraões temo uma unidade de tempo (clock tick).
- Clock Skew/Drift: com o tempo o cristal de quartzo sofre variações que resulta em pequenas variações no clock tick que se acumulam gerando disparidade.
- Mesmo relogios preciso, o clock skew é invevitabel. entao depender dele n é uma boa opção

**Algoritmo de Cristian**
- Há uma variação de tempo enetre a requisão e a respostas.
- O pc teria como referencia um servidor de tempo muito preciso.
- A hora atual seria o tempo desse servidor menos o tempo que levou para receber a resposta apos a requisição.

**Netowork Time Protocol**
- Organização em camadas *estratos*, cada maquina sabe em quem confiar

## 2. Relógios Lógicos

**Relogio de Lamport**
- Processos possuem contadores que aumentam a cada evento interno que concluem.
- Timestamp é o valor atual desse contador
- No caso de eventos como enviar mensagens, o receptor vai pegar o maior timestamp (o próprio ou da pessoa que enviou) e somar mais um.
- Eles são locais, ter um timestamp menor não significa que o processo ocorreu antes;

## 3. Relógios Vetoriais
- Consegue marcar o quanto o processo conhece dos eventos dos outros processos.
- Cada processo possui uma lista de N posições, uma para cada processo do sistema, que representa contadores.
- Caso houver um evento interno, o processo aumenta o seu próprio contador.
- Caso houver uma interação

## 5. Exclusao Mutua
- Impedir que vários processos usem o mesmo recurso critico ao mesmo tempo.
- Algoritmos de permissão:
    - O acesso é feito por requissões, que pode ser negadas ou aceitas
    - Desvantagem: muitasa mensagem
- Algoritmot de ficha:
    - Procesos formam uma estrutura, quem esta com a ficha pode acessar.
    - Desvantagem: temq  ter um algoritmo de recuperação caso o nó com a ficha cair 

### 1. Algoritmo Centralizado
- Há um processo coordenador, os outros processos perguntam se podem acessar.
- Se não tiver ngm acessando, ele aceita.
- Se alguem tiver acessando, ele nega e o processa vai pro final da fila.
- Poucas mensagens, fácil implementacao, justo, sem starvation

### 2. Algoritmo Distribuido de Ricart Agrawala
- Não tem coordenador, é necessario ter OK de todos.
- Ele pergunta pra todo mundo se querem usar.
- Se nao esta usando da OK.
- Se esta usando da OK após liberar o acesso.
- Se quer usar, só da OK se tiver time stamp maior que o dele.
- Evita deadlock
- Muitas mensagens, s eum cair ja era

### 3. Algortimo Token-Ring

### 3. Algortitmo Descentralizado