# Comunicação por envio de mensagens

## 1. Introdução

A comunicação por envio de mensagens é uma forma direta de interação em sistemas distribuídos, na qual os processos trocam dados explicitamente por meio de mensagens. Diferente da RPC, que abstrai a comunicação e esconde a complexidade da rede, nesse modelo a aplicação é responsável por construir, enviar, receber e interpretar as mensagens.

Esse modelo pode ser classificado como transiente e persistente e, por oferecer controle explícito sobre o envio, formato e processamento das mensagens, proporciona maior controle e, menor overhead (uso de recurso extra) em comparação com o RPC.

## 2. Sockets

Um socket é um canal bidirecional de comunicação entre dois processos, que permite enviar e receber dados pela rede. Podem ser via:

**TCP:** Com conexão, mais confiável e organizado. Usado em HTTP.

**UDP:** Sem conexão, sem garantia de entrega e mais rápido. Usado em jogos e streaming.

Além disso, eles ocorrem por meio das operações:

● socket: criar um ponto de comunicação
● connect: estabelece uma conexão
● send: envia dados de uma conexão
● receive: recebe dados de uma conexão
● close: fecha a conexão
● bind: estabelecer um endereço local
● listen: dizer que o socket aceita conexões nele e
qual o tamanho máximo de conexões pendentes
● accept: bloqueia até receber uma requisição

## 3. Message-Parsing Interface (MPI)
O MPI é um padrão de comunicação desenvolvido para computação paralela de alto desempenho. Enquanto os Sockets foram feitos para a internet em geral, o MPI foi feito para rodar em redes fechadas de altíssima velocidade e ao mesmo tempo garantir portabilidade de códigos, ou seja, permitir que sejam rodados em diferentes sistemas sem modificações.

**Ideia Principal:**

Ele assume que a rede é compostas por diversos grupos fechados e seguros que possuem seus próprios processos. A comunicação entre grupos é feita utilizando um par de identificação (ID do Grupo, ID do Processo) para definifir a origem e o destino.


## 4. Message-Oriented Middleware (MOM)

É um software focado em mensagens persistentes e assíncronas, ou seja, um sistema onde (diferente do MPI e RPC):

- As mensagens são momentaneamente armazenadas pelo middleware.
- As mensagens não sao bloqueantes.
- Emissor e receptor não precisam estar ativos simultaneamente para se comunicarem.
- Comunicações podem demorar minutos, ao invés de segundos.

### 4.1 Filas de mensagens

Nele, ao invez de um contato direto entre cliente e servidor, as mensagens sao guardadas por um middleware, que as organiza em uma fila. Essa fila é útil pois:

- O produtor não precisa esperar o consumidor.
- O consumidor pode processar no seu próprio ritmo.
- Resolve problemas de falhas de rede e indisponibilidade.
- Resolve problema de lentidão em momentos de pico.

Operações típicas de fila são:

PUT: adicionar uma mensagem na fila (nãoblocante)
GET: remove um elemento da fila, bloqueia se
estiver vazio
POLL: remove um elemento da fila mas não
bloqueia se estiver vazio
NOTIFY: insere uma função de callback que deve
ser executada quando existir elemento na fila

### 4.2 Brokers

Em um ambiente com vários sistemas interagindo, surgem múltiplas filas e a comunicação ponto a ponto se torna complexa, pois cada sistema precisa saber para qual fila enviar mensagens e quem irá consumi-las. 

Nesse cenário, surge o broker, que atua como um mediador central responsável por gerenciar as filas, definir regras de roteamento, realizar possíveis conversões de dados e encaminhar mensagens. 

Com isso, os sistemas passam a se comunicar apenas com o broker, que decide para qual fila cada mensagem deve ser enviada e quais consumidores irão recebê-la. Essa centralização reduz a complexidade de integração de O(N²) para O(N), tornando o sistema mais escalável e organizado.

Assim como os brookers podem:

- Transformar campos.
- Converter formatos.
- Adaptar protocolos.
- Fazer integração entre aplicações heterogêneas.

Eles toranam os middlewares muitos valioso em ambientes corporativos e de integração de sistemas legados.

### 4.3 Advanced Message Queuing Protocol  (AMQP)

Como no passado cada empresa criava seu próprio Broker proprietário, em 2006 foi criado o AMQP, um padrão aberto criado para permitir que diferentes sistemas de enfileiramento de mensagens operem juntos.

- Usa conexões TCP.
- Comunicação vidirecional.
- Dado viaja por meio de links.
- Uma mensagem nasce com status unsettled e muda para settled quando o destino confirma que a processo com sucesso.

### 4.4 Aplicações Práticas

**RabbitMQ:** É um dos Message Brokers mais famosos e implementa o AMQP. O grande diferencial arquitetural dele é o conceito de Exchanges.

- Quem envia a mensagem não manda direto para a fila. Manda para um Exchange.
- O Exchange, ao contrário do Broker, não armazena mensagens, apenas lê as regras e decide em quais filas aquela mensagem deve ser jogada. 
- Isso dá uma flexibilidade enorme para criar sistemas complexos.

**Celery:** É um framework (middleware) muito usado em Python para gerenciar filas de tarefas. Ele facilita a vida do programador porque padroniza o código, permitindo que você conecte seu software a um RabbitMQ (Message Broker) ou a um Redis (Banco em Memória), sem precisar reescrever as integrações se decidir trocar a tecnologia de fila no futuro.


