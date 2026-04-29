
## 3. Relógios Lógicos

Toda sincronia anterior era baseada em um relógio real medindo o tempo. Porém,ter relógios perfeitamente sincronizados é impossivel, sempre haverá algum clock skew mínimo. Assim, usar "horário" para decidir ordem de eventos é arriscado. Imagine:

> - Máquina A registra: evento aconteceu às 10:00:01
> - Máquina B registra: evento aconteceu às 10:00:00

Nesse exemplo parece que B aconteceu antes de A, mas pode ser só porque o relógio de B está atrasado. Assim, relógios lógicos são categoria de soluções para substituir tempo real em sistemas distribuídos.


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


### 3.2 Relógios Vetoriais

Surgem para resolver essa limitação dos relógios de lamport. Em vez de um único contador, cada processo mantém um vetor com N posições, onde N é o número de processos do sistema. Assim, cada posição registra as interações de um processo com os outros processos, marcando tanto os seus eventos, quanto o que ele conhece dos eventos dos outros. 

Assim, quando uma mensagem chega, o receptor não só atualiza seu próprio contador, como também incorpora informação sobre o estado causal do emissor. 

> - P1: [0, 0, 0]
> - P2: [0, 0, 0]
> - P3: [0, 0, 0]

Após P1 ter um evento interno:

> - P1: [1, 0, 0]
> - P2: [0, 0, 0]
> - P3: [0, 0, 0]

Após P1 enviar uma mensagem para P2:

> - P1: [1, 0, 0]
> - P2: [1, 1, 0]
> - P3: [0, 0, 0]


A regra  para o receptor é pegar os contadores máximos, seja dele ou do mensageiro.  Continuando o exemplo anterior mas com P2 mandando mensagem para P3 temos:

> - P1: [1, 0, 0]
> - P2: [2, 1, 0]
> - P3: [2, 1, 1]



