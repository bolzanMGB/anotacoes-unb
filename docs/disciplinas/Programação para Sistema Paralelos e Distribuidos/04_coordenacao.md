# Coordenação

## 1. Introdução

Depois de entender estrutura e comunicação, o próximo problema é a coordenação. Em sistemas distribuídos, não basta os processos conseguirem  comunica-se entre si, também é necessário organizar:

- Quem pode acessar um recurso.
- Adesso simultâneos a recursos.
- Em que ordem os eventos ocorrem.
- Como manter os dados consistentes entre vários nós.

Em um sistema local essa coordenação é mais simples, já que os processos compartilham apenas uma única memória, um único sistema operacional e um único reógio. Já nos SD, como cada parte está em uma máquina diferente e existe diferentes tempo, SOs e etc, a coordenação de processos é muito mais complexa e importante. Se dois processos tentam atualizar o mesmo recurso ao mesmo tempo, ou se diferentes nós precisam concordar sobre uma sequência de eventos, o sistema pode quebrar a consistência.

## 2. Sincronização de relógios

A primeira grande questão é o tempo. Em um sistema local, o tempo é simpls de usar já que todos os processos compartilham o mesmo tempo. Já em SDs, cada máquina tem seu próprio relógio, o que torna dificil saber a ordem real dos eventos apenas olhando o horário registrado por cada nó.

### 2.1 Cristal de Quartzo

Todo computador possui um mecanismo físico para medir o tempo que é baseado em cristal de quartzo. Quando esse crital recebe uma tensão elétrica ele vibra numa frequência estável, conhecida e previsível

**Relógio de Cristal de Quartzo:** O mecanismo para medir o tempo em um computador é baseado na vibração que o seu cristal de quartzo, acoplado no sue interior, produz ao receber uma tensão elétrica.

**Clock Tick:** O hardware do computador possui um contador que é decrementado a cada oscilação do cristal de quartz. Quando o contador atinge zero, o hardware gera uma interrupção chamada clock tick, indicando que uma unidade de tempo passou. O sistema operacional utiliza esses ticks para atualizar o relógio do sistema e executar tarefas periódicas,.

**Clock Skew/Drift:** Com o tempo, condições físicas e ambientais afetam a frequência de oscilação do cristal de quartzo, causando pequenas variações na taxa dos clock ticks. Essas diferenças se acumulam ao longo do tempo, resultando em uma disparidade no tempo dos relógios. 

Mesmo relógios digitais sendo precisos, o clock skew faz com que diferentes máquinas tenham percepções de tempo ligeiramente distintas, exigindo mecanismos de sincronização em sistemas distribuídos.

### 2.2 Algorítmo de Cristian

Aparece como uma solução prática para sincronizar um cliente com um servidor de tempo.

- Teve haver um servidor de tempo que é preciso e o cliente pode usar como referência.
- Cliente consulta um servidor confiável.
- Cliente registra o momento em que envia a requisição e o momento em que recebe a resposta.
- Cliente recebe a hora e estima o atraso da comunicação da rede para ajustar o próprio relógio.

### 2.3 Network Time Protocol (NTP)

Organiza a sincronização através de estratos de forma que cada máquina sabe de quem pode confiar.

**Estratos:** É uma hierarquia onde o servidor de baixo se sincroniza com o de cima, indo assim até o topo, onde está'uma fonte muito precisa.


## 3. Relógios Lógicos

Toda sincronia anterior era baseada em um relógio real medindo o tempo. Porém,ter relógios perfeitamente sincronizados é impossivel, sempre haverá algum clocl skew mínimo. Assim, usar "horário" para decidir ordem de eventos é arriscado. Imagine:

> - Máquina A registra: evento aconteceu às 10:00:01
> - Máquina B registra: evento aconteceu às 10:00:00

Nesse exemplo parece que B aconteceu antes de A, mas pode ser só porque o relógio de B está atrasado. 


### 3.1 Relógio de Lamport

#### 3.1.1 Ordem Casual

Lamport criou a relação do "acontece-antes", em vez de se importar com que horas aconteceu, o importante é saber a **ordem causal** lógica dos eventos. Assim:

> Se A → B, então A ocorreu antes de B.

Isso pode representar duas coisas:

**1. Primeiro Caso:** A e B fazem parte do mesmo processo e, na execução linha por linha do programa, o Evento A aconteceu antes do Evento B.

**2. Segundo Caso:** Evento A representa um processa que envia uma mensagem, e o Evento B representa o processo que recebeu essa mensagen

#### 3.1.2 Transitividade

Outro ponto é em relação a **transitividade**, temos que:

> - A → B
> - B → C
> - Logo: A → C

#### 3.1.3 Concorrência

Se dois processos A e B não trocam mensagens e não têm relação causal, logo eles são concorrentes e não existe ordem definida entre eles:

> - não dá pra dizer que A → B
> - nem que B → A


#### 3.1.4 Solução

A solução de Lamport para o problema da sincronização foi a utilização de **contadores** dentro dos processos, funcionando como um relógio lógico que marca a ordem dos eventos, e não o tempo real. Assim, toda vez que um evento acontece no processo, seja algo interno, o envio de uma mensagem ou recebimento, o contador é aumentado em um.

O envio de uma mensagem cria uma ligação causal entre os processos. Temos, por exemplo, o seguinte estado inicial de dois processos:

> - P1: 5
> - P2: 2

Isso significa que o **timestamp** de P1 é 5 e P2 é 2. Ao receber a mensagem, o timestamp de P2 é calculado da seguinte maneira:

> P2 = max(2, 6) + 1 = 7

Caso os timestamps forem idênticos, utiliza-se o id do processo como desempate. Assim, ao pegar o maior timestamp e acrescentar, é possível ter uma noção de o que veio depois e o que veio antes.

**Limitação:**

Os contadores são locais e podem crescer independentemente. Assim, se

> C(A) < C(B)

Isso não garante que A → B.


## 4 Relógios Vetoriais

Surgem para resolver essa limitação dos relógios de lamport. Em vez de um único contador, cada processo mantém um vetor com N posições, onde N é o número de processos do sistema. Assim, cada posição registra as interações de um processo com os outros processos, marcando tanto os seus eventos, quanto o que ele conhece dos eventos dos outros. 

Assim, quando uma mensagem chega, o receptor não só atualiza seu próprio contador, como também incorpora informação sobre o estado causal do emissor. Exemplo:

> - P1: [0, 0, 0]
> - P2: [0, 0, 0]
> - P3: [0, 0, 0]

Após P1 ter um evento interno:

> - P1: [1, 0, 0]
> - P2: [0, 0, 0]
> - P3: [0, 0, 0]

Após P1 enviar uma mensagem para P2:

> - P1: [1, 0, 0]
> - P2: [2, 1, 0]
> - P3: [0, 0, 0]

## 5. Exclusão Mútua

Após entender tempo e ordem, como impedir que vários processos usem o mesmo recurso crítico ao mesmo tempo?

Em sistemas locais, ess impedimento ocorre através de locks, semáforos e memória compartilhada. Em sistemas distribuídos, já que não existe uma memoria compartilhada central, a solução para atingir a exclusão mútua é feita apenas por troca de mensagens. Para isso, existem dois tipos de algorítmos:

**Baseados em Permissão:** A troca de mensagens é realiza com requisições de recursos, que podem ser aceitas ou negadas.
- Desvantagem: Precisam dtrocar muitas mensagem para realizar uma ação.

**Baseados em Token (ficha):** Os processos se organizam em uma estrutura e uma ficha é transferida de um processo ao outro, apenas que tem a ficha pode acessar o recurso.
- Desvantagem: Processo de recuperação complicado caso o algritmo com a ficha cair.

### 5.1 Algoritmo Centralizado

Nele um coordenador controla quem pode entrar na seção. Funciona da seguinte forma:

- **Requisição:** Processo pergunta se pode acessar.
- **Negação/Concessão:** Coordenador concede ou nega, durante esse tempo o processo fica bloqueado. Caso negar, forma-se uma fila.
- **Liberação:** Processo acessa (ou não) os recursos e é liberado

**Vantagens:** 

- Usa poucas mensagens.
- Fácil de implementar.
- É justo e evita starvation.

**Desvantagem:** 

- Coordenador pode se tornar um gargalo: O cliente fica travado até receber a resposa, caso o coordenador cair ele fica sem resposta e todo o sistema sofre.
- Coordenador pode ficar sobrecarregado.
- Não é escalável.
- Frágil em grandes sistemas distribuídos.

### 5.2 Algorito Distribuído de Ricart e Agrawala

É baseado em mensagens e em relógio lógico e todos os processos participam da decisão. Funciona da seguinte forma:

1. Quando um processo quer entrar na seção crítica, ele envia pedido para os outros e espera resposta positiva.

2. Ao receber um pedido de acesso a um recurso, vindo de outro processo, o processo que recebeu tem **três opções**:

- **A) Ele não está acessando o recurso e nem quer acessar:** Então ele apenas informa que, por ele, ele pode acessar.

- **B) Ele está acessando o recurso:** Então ele nega a mensagem e a coloca em uma fila.

- **C) Ele não está acessando o recurso, porém quer acessar:** Então desempate é feito pelo timstamp; quem tiver a menor marca de tempo vence.


**Vantagens:**
- Evita deadlock e starvation

**Desvantagem:**
- Número de mensagens muito alto.
- Pouca tolerância a falhas.
- Parecido com o centralizado, um processo pode ficar sem resposta caso a mensagem for perdida.

imagem 111

### 5.3 Token-Ring

Nesse modelo, os processos estão organizados em anel e uma ficha de acesso circula entre eles. Somente quem possui o token pode acessar o recurso. 

- Se um processo não quer acessar nada, ele simplesmente repassa a ficha.
- Se um processo quer acessar o recurso, ele espera a fixa chegar até ele.
- Depois de usars e liberar o recurso, a ficha é passada para o próximo.

**Vantagens:**

- Evita deadlock.
- Evita starvation

**Desvantagem:**

- O token pode ser perder.
- O processo que posusi o token pode falhar.
- Dai precisa de um mecanismo para detectar a perda e reconstruir o anel.

imagem 112

### 5.4 Algortimo Descentralizado

Nesse modelo, invés de um único coordenador, o recurso é replicado e cada réplica tem seu próprio controlador. Para obter acesso, o processo precisa convencer uma maioria desses coordenadores.

O sistema cria N réplicas lógicas desse recurso, e cada réplica ganha um coordenador diferente.

Quando um processo quer acessar um recurso, ele joga o nome do recurso em uma **função hash**, que cospe quem são os N coordenadores.

O processo então vai  enviar um pedido permissão para esses N coordenadores, o pedido não chega ao mesmo tempo em todos e ele não precisa da permissão de todos, apenas da maoria simples "M":

> M > N / 2

Os coordenadores vão dar voto de "SIM" apenas para a primeira mensagem de acesso que chegar a eles, para os outros eles darão "NÃO". Nesse caso, os rejeitados não formam uma fila; eles aguardam um tempo (que pode ser aleatório)e dai tentam acessar denovo.

No caso do processo conseguir a maioria de votos "SIM", ele acessa o recurso. Enquanto estiver acessando, os coordenadores vão guardar seu voto. Após ele terminar, eles podem dar o voto para outra pessoa.

Deste modo, esse algoritmo impede o problema do coordenador se tornar um gargolo caso ele cair. Quando isso acontece, ele reinicia e esquece para quem ele tinha dado o seu voto "Sim" antes de cair, porém os outros coordenadores ainda lembram pra quem tinham votado.

**Vantagens:** Coordenador não vira um gargalo facilmente, somente se a maioria deles cairem.

**Desvantagem:** 

- Alta complexidade de coordenação.
- Alto custo de consultas.

### 6. Algoritmos de Eleição

Em muitos sistemas, é necessário escolher dinamicamente um coordenador. Isso acontece quando o coordenador atual falha ou quando o sistema precisa reorganizar sua liderança. 

Os algoritmos de eleição são baseados em uma rede de overlay em nós e resolvem esse problema: eles determinam qual nó vai assumir o papel de coordenador e fazem com que todos os demais descubram esse resultado. Quando um processo é eleito a coordenador, ele não para com a atividade q estava executando, ele passa a trabalhar em turnos.

#### 6.1 Algortimo Bully

Nele, o nó com maior identificador vence. Note que não é maior timestamp, e sim ID. O ID é atribuido pelo administrador do sistema e geralmente indica potência. Funcionamento:


- Um nó percebe que o coordenador não responde e inicia uma eleição **(ELECTION)** enviando uma mensagem para os nós maiores que ele.
- Se alguém responder **OK**, significa que há um nó mais forte vivo, e esse nó se torna o candidato a coordenadoraté chegar a alguem maior.
- Quando ninguém mais responder, achou-se o maior e anuncia-se o vencedor **(COORDINATOR)**.

O nome “Bully” vem dessa lógica: o nó mais alto acaba “empurrando” os demais até assumir a coordenação. 

**Vantagens:**

- Simples.
- Termina com clareza.

**Desvantagens:**

- Depende de mensagens ELECTION, OK e COORDINATOR.
- Assume que os nós conseguem identificar corretamente quem está ativo.

imagem 113


#### 6.2 Algoritmo Anel

Aqui, o critério também é quem possui o maior identificador, porém, os nós estão organizados em uma estrutura cíclica e cada nó conhece seu sucessor. Funcionamento:

- Quando um processo percebe falha do coordenador, ele declara uma **ELECTION:** cria uma lista, assina seu ID e passa para o próximo nó.
- A lista é repassada e os nós vão acrescentando seus próprios identificadores.
- Se o sucesso não responder, ele é pulado.
- A mensagem percorre o ciclo até retornar ao iniciador.
- O iniciador olha o maior número e anuncia o vencedor **(COORDINATOR)** 


