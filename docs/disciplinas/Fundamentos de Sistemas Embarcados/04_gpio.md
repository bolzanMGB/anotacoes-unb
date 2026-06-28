# GPIO (General Purpose Input/Output)

## 1. Definição

Como microcontroladores, como a ESP32, recebem e transmitem bits de dispositivos externos, como leds e motores, utilizando interfaces de comunicação, como, por exemplo, o I2C?

A interface elétrica física para isso é fornecida pela GPIO. Ela consiste em  pinos físicos e genéricos do microcontrolador que podem ser configurados como quisermos e utilizados como entrada ou saída digital de níveis lógicos (bits).


## 2. Camada Física

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

## 3. Camada de Sinal

O momento em que o pino da GPIO recebe uma tensão, ao apertar um botão por exemplo, pode ser detectado de duas formas:

- Níveis.
- Bordas.

### 3.1 Níveis

Representam períodos em que o sinal permanece estável em um mesmo estado lógico.

```bash
  0 1 2 3 4 5 6 7 8 9 10 
1          
  ______|‾‾‾‾‾‾‾‾‾‾‾|___
0 
```

- Entre os instantes [3-9], o sinal está em **nível alto**.
    - Durante esse intervalo, o GPIO lê o valor lógico 1.
- Entre os instantes [0-3] e [9-10] o sinal está em **nível baixo**.
    - Durante esse intervalo, o GPIO lê o valor lógico 0.

### 3.2 Bordas

Representam instantes específicos em que um evento de transição de sinal ocorre.

```bash
  0 1 2 3 4 5 6 7 8 9 10 
1          
  ______|‾‾‾‾‾‾‾‾‾‾‾|___
0 
```

- **Rising Edge (Borda de Subida):** Evento no instante 3.
- **Falling Edge (Borda de Descida):** Evento no instante 9.
- **Any Edge (Qualquer Borda):** Evento no instante 3 e 9.

### 3.3 Bounce e Debouncing

No mundo real, a borda gerada muitas vezes não é única e limpa. Quando apertamos um botão, por exemplo, parece que ele afunda e toca de forma instantânea o fundo, porém na realidade ele quica mecanicamente no fundo por milissegundo antes de se firmar. Para GPIO, esse quique (bouncing) é interpretado como dezenas de oscilações entre "0" e "1".

Para evitar que o software conte um único clique como múltiplos apertos, aplica-se o Debouncing, que pode ser feito de 3 formas:

**1. Hardware:** 

- Adiciona-se um capacitor em paralelo com o botão. 
- O capacitor absorve os mini-quiques elétricos.
- Suaviza a transição para uma rampa única e limpa.

**2. Software 1:** 

- Ao detectar a primeira transição, desabilita a interrupção ou ignora leituras por um período fixo (20–50 ms).
- Depois reabilita. 
- Simples mas pode perder eventos se o intervalo for mal calibrado.

**3. Software 2:**

- Incrementa um contador enquanto o estado lido é o esperado. 
- Zera o contador se o estado mudar. 
- Só registra o evento quando o contador atinge um limiar X consecutivo.

## 4. Camada de Software

Uma vez que a tensão elétrica foi detectada no pino de entrada, o software precisa monitorar essas mudanças. Há três estratégias fundamentais para fazer isso:

**1. Pooling:**

- Laço que fica verificando o nível do pino continuamente.
- Simples de implementar.
- Ocupa CPU em 100% do tempo.

**2. Eventos:**

- Programa fica blocked (dormindo) e é acordado a cada Raising-Edge e Falling-Edge.
- Essas Mudanças de estados são colocadas em filas e consultadas quando conveniente.
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


## 5. Valores Intermediários

No caso de um LED que pode receber valores intermediários de brilho (não somente 0 (desligado) e 1 (ligado)) e no caso de um Sensor de Temperatura que envia valores também intermediários, como fazer para os pinos receberem/enviarem esses valores se eles só mexem com 0V ou 3.3V/5V ? 


**1. ADC (Analog-to-Digital Converter)**

- Possibilita os pinos da GPIO receberem valores intermediárias.
- Maioria dos chips tem resolução máxima de 12 bits (4096 combinações).
- Pino recebe a tensão intermediária.
- ADC mede a tensão intermediária
- ADC transforma a tensão em número binário fazendo uma regra de três.
- 3.3V equivale ao valor máximo 4095.
- Esse número 12 bits é guardando na memória
- Quando você solicita o dado,a CPU puxa esse número inteiro direto da memória.

**2. PWM (Pulse-Width Modulation):**

- Possibilita os pinos da GPIO fornecerem saídas intermediárias. 
- Ocorre por meio de uma técnica de hardware.
- Simula uma tensão analógica intermediária que altera o pino entre o Nível Alto e o Nível Baixo em uma velocidade extremamente alta.
- Em comparação com o DAC:
    - Possui melhor eficiência energética.
    - Tensão gerada possui oscilações.
    - É mais usado por na maioria dos casos essa onda não fazer diferença.
- Usado em:
    - Controle de brilho em LEDs.
    - Velocidade de motores.
    - Controle de posição de servomotores.
    - Sinalização de buzzers.

**3. DAC (Digital-to-Analog Converter):**

- Possibilita os pinos da GPIO fornecerem saídas analógicas intermediárias reais (sem simulação).
- Maioria dos chips que possuem DAC integrado tem resolução máxima de 8 bits (256 combinações).
- Quando o software solicita uma escrita analógica, a CPU grava um número inteiro (de 0 a 255) direto na memória especial do DAC.
- O hardware do DAC lê esse número da memória e transforma em tensão física contínua fazendo uma regra de três:
        - O valor mínimo 0 equivale a 0.0 V.
        - O valor máximo 255 equivale a 3.3 V (teto elétrico do chip).
- O pino recebe essa tensão exata e a mantém perfeitamente estável, sem pulsar.
- Em comparação com o PWM:
    - Possui menor eficiência energética (esquenta).
    - Tensão gerada é precisa.
    - Utilizado apenas em contextos onde oscilações não são bem vindas:
        - Áudio de alta fidelidade.
        - Sensores de precisão.
        - Equipamentos científicos.