# Comunicação

## 1. Introdução

Em processos multihread tradicionais, no mesmo computador, a comunicação ocorre pelo paradigma de memória compartilhada (elas podem acessam a mesma memória). Já em um sistema distriuida, onde os componentes estão separado por redes e máquinas diferente, a comunicação entre processos diferente ocorre pelo paradigma de troca de mensagens.

## 2. Fundamentos de comunicação

## 2.1 Modelo OSI

Para um sistema A se comunicar com um sistema B, deve haver um acordo de o que vai ser enviado, como vai ser enviado, onde  a mensagem começa, onde ela termina, como saber se  foi danificada e diversos outros pontos. Para isso foi desenvolvido o modelo OSI que, embora não se tornou amplamente popular e está praticamente morto hoje em dia, se mostrou bastante útil para entender  as redes de computadores.

### 2.1 Protocolos 
O modelo OSI é um modelo conceitual que organiza a comunicação em rede em 7 camadas. Cada camada possui suas próprias regras/protocolos que os computadores devem concordar para se comunicarem entre si. Esses protoclos regem o formato, o conteúdo e o significado das mensagens. Há dois tipos de protocolos:

**Protocolos Orientados a Conexão:** Antes de trocarem dados, o remetente e o receptor primeiro estabelecem uma conexão negocionam qual procotolo usarão. Exemplo: sistema de telefone.

**Protocolos Não Orientados a Conexão:** Não é necessario estabelecer nada antecipadamente, o remetendo apenas transmite a priemira mensagem. Exemplo: colocar uma carta em uma caixa de correio.


### 2.2 Camadas

Cada camada passa e prepara os dados para a próxima camada. Assim, quando você envia uma mensagem, a informação desce pelas camadas:

> Aplicação → Apresentação → Sessão → Transporte → Rede → Enlace → Física

e chega no receptor, onde o processo é invertido:

> Física → Enlace → Rede → Transporte → Sessão → Apresentação → AplicaçãoEssas camadas são (FERTSAA):

Essas camadas são:

**1. Camada Física:** 

- Transmite bits no meio físico. 
- Hardware, sinal elétrico, bits.
- Exemplo: cabos (UTP, fibra), conectores.

**2. Camada de Enlace de Dados:** 

- Agrupa os bits em unidades denominadas quadros e providencia que cada quadro seja corretamente recebido (sem erros) dentro de uma rede local. 
- Coloca uma padrão especiaol de bits para delimitar o início e fim de um quadro.
- Dispositivos: pontes, switches.
- Exemplo: Ethernet, Wi-Fi, VLAN.

**3. Camada de Rede:** 

- Faz o encaminhamento entre redes.
- Dispositivos: roteadores;
- Exemplo: IPv4, IPv6.

**4. Camada de Transporte:** 

- Conexões fim-a-fim e portas. 
- Exemplo: ping, TCP, UDP

**5. Camada de Sessão:** 

- Gerencia conexões entre aplicações. 
- Exemplo: RPC.

**6. Camada de Apresentação:** 

- Faz criptografia/compressão. 
- Exemplo: TLS/SSL.

**7. Camada de Aplicação:** 

- Protocolos que o usuário recebe e interage.
- Exemplo: HTTP/HTTPS


### 2.3 Protocolos Middleware

Nos sistemas distribuídos, na prática, o middleware simplifica a comunicação, abstrai detalhes de protocolo e pode assumir parte do papel que, no modelo OSI, seria distribuído entre sessão e apresentação. Tanenbaum destaca essa camada como essencial para construir transparência e facilitar o desenvolvimento.

### 2.4 Comunicação Persistente vs Transiente

**Persistente:** A mensagem fica armazenada pelo middleware de comunicação até o que o destinatário receba, assim o emissor e receptor não precisam estar online ao mesmo tempo. Exemplo: email.

**Transiente:** A mensagem só existe e é armazenada enquanto emissor e receptor estão ativos e a infraestrutura consegue transmiti-la. Se houver falha, a mensagem pode ser descacrtada. Exemplo: sockets.

### 2.5 Comunicação Assíncrona vs Síncrona

**Síncrona:** O emissor bloqueia até algum evento de confirmação ocorrer: o middleware aceitar a mensagem, o receptor receber ou a resposta volta.

**Assíncrona:** O emissor continua eexecutano e realizando mais chamadas após transmitir a mensagem. O middleware cuida do armazenamento temporário e da entre posterior.

Essas categorias combinam-se entre si. Por exemplo:
- RPC costuma ser transiente + síncrona.
- E-mail e filas de mensagens costumam ser persistentes + assíncronas.
- Alguns middlewares permitem combinações intermediárias.

## 3. Remote Procedure Call (RPC)

Em sistemas distribuídos, o uso de chamadas explícitas de comunicação tendem a ser muito complexas (é necessáŕio programar rede + lógica ao mesmo tempo)dificultando o desenvolvimento. Para isso surgiram as RPC, funções que tenta esconder essa complexidade.

### 3.1 Ideia básica

Tornar as trocas de mensagens entre diferente máquinas invisíveis para o programador, de modo que os procedimentos que envolveriram máquinas remotas podem ser chamadas como se fossem procedimento do espaço de endereçamento local.

**Exemplo:**

Sem RPC:

```bash
enviarMensagem("somar", {2,3})
```

Com RPC

```bash
resultado = somar(2,3)
```

### 3.2 Funcionamento
Exemplo: chamada remota de read de dados que estão em outra máquina;

**Apêndice/stub de cliente:** É uma função que finge ser o read local. Quando chamada, ela não executa a leitura diretamente, mas:

- Empacota os parâmetros (marshalling).
- Monta uma mensagem.
- Chama o SO local.
- SO local, invez de ler os dados direto, envia a mensagem para o S0 remoto.

**Apêndice/stub de servidor:** É o equiavalente do stub de cliente no servidor. É uma função que transforma requisições de fora em chamadas de procedimentos locais e retorna o resultado ao SO cliente. Ao receber a mensagem:

- O SO remoto, agora o local, da a mensagem para o stub de servidor.
- O stub de servidor desempacota a mensagem e chama o seu SO local.
- O SO local chama o read local e le os dados.
- O SO local envia a mensagem ao SO do cliente.
- O SO do cliente da a mengemgem ao stub do cliente.
- O stub do cliente desempacota o resultado e retorna ao cliente.

Após receber a mensagem de volta, o cliente desempacota o resultado de forma usual e só sabe que os dados estão disponíveis: não tem ideia de que o trabalho foi realizado remotamente, e não locamente.


110 png

### 3.3 Mashalling e unmarshalling

Esse processo de transformar estruturas de dados em uma representação transmissível e depois reconstruí-las no destino é algo muito complicado.

**Marshalling:** Processo de empacotar os parâmetros/dados para o envio.S
**Unmarshalling:** Processo de desempacotar e recosntruir os parâmetros/dados ao chegar.

Isso é necessário porque máquinas podem ter arquiteturas diferentes, como little endian e big endian, além de formatos distintos para números, alinhamento e representação interna.