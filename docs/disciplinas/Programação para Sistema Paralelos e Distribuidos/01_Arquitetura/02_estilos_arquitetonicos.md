# Tipos e Arquiteturas

## 1. Introdução

Tanembaum faz a distinção clara entre dois conceitos sobre a organização do software com a organização da rede.

### 1.1 Estilos Arquitetônicos:

Refere-se à organização lógica do software. É o "desenho" de como os componentes interagem entre si, independentemente de onde eles serão instalados. O foco aqui são os Componentes (unidades de software) e os Conectores (mecanismos de comunicação). É organizado em:

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
    
### 1.2 Arquiteturas de Sistemas:

Refere-se à organização física. É a maneira como colocamos os componentes de software em máquinas reais e como essas máquinas se relacionam. É aqui que decidimos se o sistema será centralizado ou se todos os nós terão o mesmo peso. É organizada em:

1. Arquiteturas Centralizadas

2. Arquiteteuras Distribuídas
- 2.1 Arquiteturas Distribuídas Centralizadas
- 2.2 Arquiteturas Distribuídas Descentralizadas
    - 2.2.1 Arquiteturas Peer-To-Peer
        - 2.2.1.1 P2P Estruturado
        - 2.2.1.1 P2P Não-Estruturado
    - 2.2.2 Arquituras BitTorrent
- 2.3 Arquiteturas Híbridas
    - 2.3.1 Computação em Nuvem
    - 2.3.2 Computação em Borda
    - 2.3.3 Computação em Névoa

## 2. Estilos Arquitetônicos

Os sistemas distribuídos muitas vezes são complexas peças de software cujos componentes estão, por definição, espalhados por várias máquinas. Logo, o **estilo arquitetônico** define como os componentes de software se conectam e é de extrema importância em sistemas distribuídos. 

> **Componente de Software:** É uma unidade de software modular com interfaces requeridas e fornecidas bem definidas e que pode falhar e é substituível dentro de seu ambiente.

> **Estilo Arquitetônico:** É o modo como os componentes são organizados e conectados uns aos outros e como os dados são trocados entre eles.

> **Conector:** Um mecanismo que serve de mediator da comunicação da cooperação entre componentes. Ex: conexão de rede, passagem de mensagens.


<div style="text-align: center;">
  <img src="../../../assets/pngs/101.png" alt="Inserção" />
</div>

## 3. Arquitetura em Camada

Nela os componentes são organizados em camadas onde cada camada estabelece uma interface e provê um serviço. Por padrão, as camadas superiores (clientes) fazem requisições e chamam as inferiores, que por sua vez respondem para cima. Porém, dependendo da necessidade do sistema, esse fluxo pode ser invertido.

### 3.1 Arquitetura Cliente-Servidor

É a implementação mais simples do estilo em camadas. Ela se baseia em Servidor e Cliente.

#### 3.1.1 Papéis e Comportamentos

**Servidor (Processo Ativo):** Ele é como um "garçom" que nunca vai embora. Ele roda continuamente (como um daemon no Linux) esperando alguém pedir algo. Pode ser um servidor web, um banco de dados ou um servidor de arquivos.

**Cliente (Processo Ativo):** É quem toma a iniciativa. Ele envia uma requisição e fica parado esperando a resposta.

Um processo não está preso a um único rótulo. Quase sempre ocorre um troca-troca de papéis.

**Exemplo:** Quando você acessa um site, o Servidor Web da empresa é o "Servidor" para você. Mas, se esse servidor precisar descobrir o IP de um banco de dados, ele envia um pedido para um servidor DNS. Nesse momento, o Servidor Web virou um Cliente.

#### 3.1.2 Divisão Lógica X Divisão Física

**Divisão Lógica:** Divisão por o que o sistema faz.

- Nível de Interface: O que o usuário vê. 
- Nível de Processamento: Onde está a inteligencia e as regras de negócio.
- Nível de Dados: Onde as informações são guardadas permanentemente.

**Divisão Física:** É a divisão de em quais máquinas cada uma das camadas lógicas vai morar. É aqui onde entra os clientes magros e os clientes gordos.

#### 3.1.3 Espectro de Clientes

**Clientes Magros:** Nela a máquina do usuário é preguiçosa, só cuida interface e todo o processamento e dados ficam no servidor.

- Exemplo: O seu Navegador Web (Chrome/Firefox). Ele não sabe calcular o seu saldo bancário; ele apenas desenha na tela o que o servidor do banco mandou.

- Vantagem: Muito fácil de gerenciar. Se você atualizar o código no servidor, todos os usuários recebem a atualização na hora.

**Clientes Gordos:** A máquina do usuário faz o trabalho pesado. Ele cuida da interface e de boa parte do Processamento.

- Exemplo: Um jogo instalado no PC ou um software pesado de ERP. O processamento gráfico e as regras acontecem no seu computador, e ele só fala com o servidor para buscar ou salvar dados.

- Desvantagem: É um pesadelo de gestão. Se você tiver 1.000 clientes, terá que garantir que os 1.000 instalaram a versão correta, têm o hardware compatível e estão protegidos contra vírus que podem afetar o processamento local.

**Tendência Atual:** Existe um abandono dos Fat Clients. Hoje, quase tudo está migrando para o modelo Thin Client (SaaS/Web) porque é muito mais barato, seguro e confiável manter tudo centralizado no servidor do que espalhado nas máquinas dos usuários.


### 3.2 Arquitetura de Múltiplas Camadas

A arquitetura Multi-Tier surge como a solução para o esgotamento do modelo cliente-servidor tradicional (2-Tier). Quando a demanda cresce, um servidor único que tenta fazer tudo acaba "brigando" por recursos: a lógica de negócio consome a CPU, enquanto as consultas ao banco de dados saturam o Disco (I/O).


**Modelo 3-Camadas (3-Tier)**

Nesta evolução, a divisão física é levada ao limite das responsabilidades, separando o sistema em três máquinas (ou grupos de máquinas) independentes:

- **Nível de Interface de Aplicação:** Responsável
pela interação direta, como janelas gráficas ou
terminais de texto ou lidando com uma aplicação
externa.

- **Nível de Dados:** Gerencia as informações persistentes, geralmente em um banco de dados ou sistema de arquivos.

- **Nível de Processamento:** Camada posicionada entre as outras duas, reside a lógica da aplicação. 

**Exemplo:** Sistema de busca na Web.

- **Nível de Interface:** A página onde o usuário digita a pesquisa ou um website encontrado.
- **Nível de Dados**: O banco de dados que contém todas as páginas.
- **Nível de Processamento:** Lógica de negócio e gerador de consultas, como por exemplo a transformação das palavras da busca do usuário em consultar formais ao BD.

## 4. Arquiteturas Baseadas em Serviços

Inicialmente as arquiteturas eram muito acopladas e existia uma forte dependência/acoplamento entre os componentes, Assim, para reduzir essa dependência os sistemas se organizaram genericamente em entidades independentes e reutilizáveis, que encapsulam um determinado serviço, que pode ser um objeto, recurso ou microsserviço. 

A adaptação web da arquitetura baseada em serviço se chama Representational State Transfer (REST). Quando uma aplicação segue os padrões REST, ela é chamada de RESTful

### 4.1 Arquitetura Baseada em Objetos

Cada objeto, que correspondem a um componente, encapsula seus dados e as operações são feitas vias métodos. O que torna essa arquitetura distribuída é que, para um cliente, parece que ele está chamando uma função local, porém na verdade ele está invocando um função de um objeto que pode estar fisicamente em outra máquina, através das Chamadas de Procedimento Remoto (RPC). Para usar esse objeto, há dois mecanismos envolvidos:

**1. Vinculação**
Para utilizar do objeto, é necessário primeiro encontrá-lo.

- **Bind (Vinculação):** É o processo de localizar o objeto remoto na rede e conectar-se a ele. É como procurar um contato na agenda e clicar em ligar.

- **Proxy:** No lado do cliente, surge um representante. Quando você chama um método no objeto você não está falando com o objeto real, mas com esse Proxy, que tem a mesma interface do original.

imagem 102

**2. Tradução**
Mecanismo de como os dados viajam:

- **Client Stub:** É um código local que serve de "dublê". Quando o seu programa chama objeto.calcular(), o Stub pega esse comando, transforma os parâmetros em um formato que pode viajar pela rede (processo chamado de Marshaling) e envia para o servidor.

- **Server-side Stub/Skeleton:** No servidor, o "Esqueleto" recebe esse pacote de rede, transforma de volta em um comando que o objeto real entende (Unmarshaling) e executa a função. O resultado faz o caminho inverso.

imagem 103 

### 4.2 Arquitetura de Microsserviços

Arquitetura dividida em pequenas tarefas independentes, não existe uma definição formal de quão pequeno precisa ser. Para que esses serviços funcionem de maneira independente, outros componentes podem ser necessários:

- **API Gateway:** Lida como um único ponto de entrada, distribuindo as requisições dos clientes.
- **Orquestração:** Um software de controle pode agir como coordenador, indicando direções e o fluxo de dados Arquiteturas de Microsserviços.
- **Gerência de Dados Não-Centralizada:** Cada serviço é
responsável pelos seus dados e manter a consistência e gerência dos dados pode ser um desafio.
- **Descoberta de serviços:** Um mecanismo para que os
serviços encontrem automaticamente, conectem-se
para permitir a escalabilidade.

### 4.3 Arquitetura Baseada em Recursos

Onde recursos são acessados de forma remota. Há quatro características obrigatórias:

- Identificação Única: Cada recurso é identificado por um
esquema de nomes único, geralmente URIs (como URLs).

- Interface Uniforme: Todos os serviços usam conjunto
restrito de operações padrão: GET, PUT, POST e DELETE.

- Mensagens Auto-Descritivas: As mensagens enviadas contêm todas as informações necessárias ao processamento.

- Stateless: O servidor não guarda informações sobre o
cliente entre as requisições, facilita a escalabilidade.


## 5. Arquiteturas Publicar-Subscrever (Pub-Sub)**
Este modelo representa uma mudança de paradigma: saímos da comunicação direta (onde o emissor conhece o receptor) para a comunicação indireta, mediada por um middleware. O objetivo central é o Desacoplamento, que Tanenbaum divide em duas dimensões fundamentais:

**Desacoplamento no Espaço:** Os processos são anônimos, remetente não sabe quem é o destinatário, e vice-versa. 

Ele apenas grita a mensagem, não sabe se existem 0 ou 100 pessoas ouvindo, nem quem são elas.

**Desacoplamento no Tempo:**  O remetente e o destinatário não precisam estar rodando ao mesmo tempo. Eu posso enviar uma mensagem agora, e você lê-la apenas quando ligar seu computador amanhã.

### 5.1. Arquitetura Baseada em Eventos 
Nesta arquitetura, o sistema é visto como uma coleção de processos autônomos que coordenam suas ações através de um Barramento de Eventos (Event Bus).

**Dinâmica:** Um processo Publicador emite uma notificação de evento. O barramento verifica quais processos Subscritores manifestaram interesse prévio naquele tipo de dado e realiza a entrega.

**Desacoplamento no Espaço:** Total. O publicador apenas "anuncia" o fato ao barramento.

**Acoplamento no Tempo:** Na definição clássica, é acoplado. A comunicação é efêmera: se o subscritor não estiver "ouvindo" no exato momento do disparo, ele perde o evento.

**Exemplo:** Um sistema de monitoramento de trânsito em tempo real. O sensor publica "Acidente na via X". Apenas os motoristas com o GPS ligado e sintonizados naquela área recebem o alerta instantâneo.

### 5.2 Espaço de Dados Compartilhados 

Este modelo, também conhecido como Sistemas de Tuplas ou Comunicação Generativa, eleva o desacoplamento ao seu nível máximo, removendo a dependência temporal.

**Dinâmica:** Existe um repositório persistente (o "Espaço de Dados").

- O Publicador insere um dado (uma Tupla, como ["projeto_X", "status", "concluido"]) e o dado permanece lá independentemente do estado do processo.
- O Subscritor realiza buscas no espaço usando modelos (templates) para encontrar os dados que lhe interessam.

**Desacoplamento no Espaço:** Total. Não há endereçamento direto.

**Desacoplamento no Tempo:** Total. O publicador pode postar o dado pela manhã e encerrar sua execução; o subscritor pode ligar seu sistema à noite, consultar o espaço e processar a informação que ficou "esperando".

**Exemplo:** Um sistema de submissão de tarefas (Job Queue). Um servidor mestre coloca as tarefas no espaço de dados. Diferentes máquinas trabalhadoras (que podem entrar e sair da rede a qualquer momento) buscam essas tarefas, executam e devolvem o resultado ao quadro.

