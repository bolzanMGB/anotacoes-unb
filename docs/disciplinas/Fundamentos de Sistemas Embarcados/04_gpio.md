# GPIO (General Purpose Input/Output)

## 1. Definição

Como microcontroladores, como a ESP32, recebem e transmitem bits de dispositivos externos, como leds e motores, utilizando interfaces de comunicação, como, por exemplo, o I2C?

A interface elétrica física para isso é fornecida pela GPIO. Ela consiste em  pinos físicos e genéricos do microcontrolador que podem ser configurados como quisermos e utilizados como entrada ou saída digital de níveis lógicos (bits).


## 2. Camada física

### 2.1 Entrada e saída

- Os pinos da GPIO são ligados através de cabos (jumpers) em dispositivos externos.
- Através desses jumpers os dispositivos podem enviar e receber dados do microcontrolador.
- Esses dados são na verdade tensão elétrica que é interpretada como valores lógicos (bits 0 ou 1).
- Entrada: Botão envia uma tensão elétrica pelo jumper que chega ao pino da GPIO e é interpretada pela CPU do Chip.
- Saída: CPU envia uma tensão elétrica ao pino GPIO que passa pelo jumper e chega no led, onde pe interpretado.

### 2.2 Thresholds:

- Tanto o microcontrolador quanto os dispositivos externos, não leem valores exatos de tensão mas sim valores dentro de uma faixa de tolerância.
- Essa faixa de tolerância depende do dispositivo, porém tende a ser:
    - Bit 1 =~ 3.3V.
    - Bit 0 =~ 0.0V.
- Os valores que determinam essa faixa se chamam thresholds.
    - Threshold Inferior: valores menores que ele são interpretadas como 0.
    - Threshold Superior: valores maiores que ele são interpretadas como 1.
- Os valores entre os dois limites pertencem a uma região indefinida e podem causar leituras incorretas.
- Se a tensão for maior que o limite superior o chip pode ser permanentemente danificado.

**Exemplos:**

Raspberry Pi (3,3 V)

- Bit 0: 0,0 V a 0,8 V.
- Bit 1: 2,0 V a 3,3 V.
- Região indefinida: 0,8 V a 2,0 V.

 Arduino Uno (5 V)

- Bit 0: 0,0 V a 1,5 V.
- Bit 1: 3,0 V a 5,0 V.
- Região indefinida: 1,5 V a 3,0 V.

### 2.2 Floating-Input

- Quando um pino está configurado como entrada e nada está conectado a ele, a tensão lida flutua aleatoriamente entre 0 e 3.3V.
- Isso ocorre devido a ruídos eletromagnéticos do ambiente.
- Floating-Input é esse estado de ruído.
- Isso pode ocasionar leituras errôneas de 0 ou 1. 

### 2.3 Resistores Pull-Up e Pull-Down

Para resolver o floating-input, os pinos da GPIO possuem dois potenciais elétricos:

    - VCC: tensão positiva (1), 3.3V ou 5V.
    - GND: tensão negativa (0), 0v.

Esses potenciais são acionados por meio de transistores:

    - Pull-Up: Conecta a tensão ao VCC.
    - Pull-Down: Conecta a tensão  o GND.


Assim, fechando e abrindo esses transistores, podemos ter três circuitos diferentes. Geralmente, microcontroladores já vem com uma configuração de fábrica (com um ou nenhum dos transistores fechados), porém com Software podemos abrir e fechar esses registradores, resultando em uma nova configuração. Os três circuitos são:

**1. Input Pull-Up:**

- Transistor Pull-Up: Fechado.
- Transistor Pull-Down: Aberto.
- Tensão padrão é alta (1).
- Pino ao receber uma tensão baixa (0):
    - Corrente alta sai do VCC e vai embora do pino pelo jumper em direção ao 0.
    - Tensão no pino cai e buffer lê 0.
- Pino ao receber uma tensão alta (1):
    - Tensão continua alta e buffer lê 1.       
- Lógica inversa:
    - Sem ação externa: Buffer lê 1.
    - Com ação externa: Buffer lê 0.

**2. Input Pull-Down:**

- Transistor Pull-Up: Aberto.
- Transistor Pull-Down: Fechado.
- Tensão padrão é baixa (0).
- Pino ao receber uma tensão baixa (0):
    - Tensão continua baixa e buffer lê 0.  
- Pino ao receber uma tensão alta (1):
    - Corrente alta vem do jumper para o pino e desce pro GND preenchendo o pino.
    - Tensão fica alta e buffer lê 1.   
- Lógica inversa:
    - Sem ação externa: Buffer lê 0.
    - Com ação externa: Buffer lê 1.

**3. Floating-Input:**

- Transistor Pull-Up: Aberto.
- Transistor Pull-Down: Aberto.
- Tensão recebida vai direto para o buffer.
- Sofre de floating-input.


### 2.2 Mecanismo de Software

Uma vez que a tensão elétrica chega ao pino de entrada, o software precisa monitorar essas mudanças. Há três estratégias fundamentais para fazer isso:

**1. Pooling:**

- Laço que fica verificando o estado do pino continuamente.
- Simples de implementar.
- Ocupa CPU em 100% do tempo.

**2. Eventos:**

- Programa fica blocked (dormindo) e é acordado com mudanças de estado.
- Mudanças de estados são colocadas em filas e consultadas quando conveniente.
- CPU fica livre para outras tarefas.
- Possui pequena latência entre o clique físico e a leitura pelo software da fila.

**3. Interrupções:**

- Programa fica blocked (dormindo) e é acordado com mudanças de estado.
- Mudanças não entram em filas:
    - CPU larga o que está fazendo.
    - Executa a função de tratamento na hora. 
    - Depois volta a fazer o que estava fazendo.
- Eficiência máxima e latência mínima.
- No Linux a troca de contexto gera overhead.
- No bare metal funciona perfeitamente. 


### 3.2 Bouncing: Debounce



<div style="text-align: center;">
  <img src="../../assets/pngs/96.png" alt="Inserção" />
</div>