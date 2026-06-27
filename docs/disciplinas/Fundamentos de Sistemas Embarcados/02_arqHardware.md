# Arquitetura de Hardware

## 1. Arquitetura de Hardware

Todo sistema embarcado, independente do tamanho ou complexidade, é formado pelos mesmos blocos fundamentais. Eles são:

- **1. Processador**
- **2. Memória**
- **3. Barramentos Internos**
- **4. Interfaces de Comunicação**
- **5. Periféricos Externos**

## 2 Processador(CPU)

É o núcleo e cérebro do sistema. O processador busca instruções armazenadas na memória, decodifica o que cada instrução significa e as executa, seja  operações matemáticas, lógicas e de controle de fluxo. 

O processador determina a capacidade de processamento disponível: 

- Frequência de clock: quantas operações por segundo.
- Arquitetura: quantos bits processa de uma vez (8, 16, 32 ou 64 bits).
- Unidades especiais: pode possuir ou não. Exemplo: FPU (Floating Point Unit, para cálculos com decimais) e MMU (Memory Management Unit, necessária para rodar Linux).

## 3. Memória:

Pode ser: 

**1. Memória Não-Volátil (Flash/ROM):** armazena o código do programa (firmware) de forma permanente. Mesmo sem energia, o conteúdo persiste. Quando o sistema liga, o processador busca as instruções a partir daqui. É lenta para escrita.

**2. Memória Volátil (RAM — Random Access Memory):** armazena as variáveis, pilhas de função e dados em uso durante a execução. É muito mais rápida que a flash para leitura e escrita. Todo seu conteúdo é perdido ao desligar o sistema. Geralmente é escassa e deve ser gerenciada com cuidado.

Alguns sistemas embarcados possuem ainda memória EEPROM ou áreas de NVS (Non-Volatile Storage) dentro da flash para armazenar pequenas configurações persistentes (senhas, calibrações, estados) que precisam sobreviver a reinicializações mas também precisam ser atualizadas durante a vida do produto.


## 4. Comunicação

Em um sistemas embarcado a comunição ocorre em três níveis:

**1. Intra-chip:** 

- Ocorre por meio dos barramentos internos. 
- Conecta módulos internos do chip.
- Exemplos de destino: CPU, memória, controladores e periféricos internos.
- CPU --barramento interno--> Memória.

**2. Inter-chip:**

- Ocorre por meio de conexões dedicadas.
- Conecta módulo externos do chips, porém ainda na mesma placa.
- É mediado por controladores internos (ainda no chip).
- Exemplos de destinos: memória RAM, PCIe.
- CPU --barramento interno--> controlador específico  --conexões dedicadas--> RAM.

**3. Extra-chip:** 

- Ocorre por meio de interfaces de comunicação.
- Conecta módulos externos ao chip e a placa.
- É mediado por controladores internos (ainda no chip).
- Exemplo de destinos: sensores, atuadores. 
- CPU --barramento interno--> cocontrolador específico  --interfaces de comunicação--> Sensor.


## 5. Barramentos Internos

Os barramentos internos são as "estradas" que interligam o processador, a memória, controladores e periféricos dentro do chip ou da placa. Sem eles, cada componente seria uma ilha isolada.  Eles, além de conectarem os dispostivos, também definem as regras da comunicação, como velocidade, largura de bits, protocolo e etc.

### 5.1 Grupos de Sinais

Um barramento é formado por três grupos distintos de fios. 

**1. Barramento de Endereço:** Indica a posição de memória ou o periférico que está sendo acessado. O número de fios desse grupo depende da arquitetura do processador (16, 32, 64).

**2. Barramento de Dados:** Transporta o dado em si. O número de fios também depende da arquitetura do processador.

**3. Barramento de Controle:** Sinais que coordenam a operação. Não depende da arquitetura do processador, e sim de quais funções ele possui: há um fio para cada função. Exemplo: Clock (sincroniza todos), Read/Write (define a direção), ACK (confirmação de recebimento), IRQ (sinaliza interrupção de um dispositivo).

Quando um dispositivo quer solicitar algo, ele envia pelos fios de barramento um sinal com bits que representam o que ele quer. O dispositivo de destino recebe o sinal e lê os bits que chegaram e, de acordo com eles, executa a operação solicitada. 

- Em uma operação de leitura, o dispositivo de destino coloca o dado solicitado no barramento de dados. - Em uma operação de escrita, ele recebe o dado presente no barramento de dados.

### 5.2 Elementos de Suporte
São elementos que auxiliam o barramento.

**1. Árbitro (Arbiter):** Quando múltiplos dispositivos querem usar o barramento ao mesmo tempo, o árbitro decide quem vai. Sem árbitro, dois dispositivos colocariam valores diferentes nas linhas simultaneamente, corrompendo os dados.

**2. Decodificador de Endereço:** Ao ver o endereço colocado no barramento, identifica qual dispositivo deve responder. 

**3. Bridge (Ponte):** Conecta dois barramentos diferentes que não são compatíveis diretamente.Por exemplo, um barramento de alta velocidade (para CPU e memória) a um barramento de baixa velocidade (para periféricos mais lentos).

**4. DMA (Direct Memory Access):** Assume o trabalho de realizar as operações de leitura e escrita de endereços para a DMA, de modo a economizar CPU.

### 5.3 AMBA (Advanced Microcontroller Bus Architecture)**

Há várias implementações de barramentos intra-chip, uma dessas implementações é a AMBA. 

A AMBA é uma família de protocolos de barramento intra-chip para diferentes necessidades que foi desenvolvida pela ARM e é utilizada em SoCs e ASICs baseados em processadores ARM. É um padrão aberto (qualquer fabricante pode implementar) e é o barramento usado na Raspberry Pi e na ESP32. Os principais barramentos da AMBA são

**1. APB (Advanced Peripheral Bus)**

- Baixa performance.
- Conecta periféricos que não precisam de alta velocidade.
- Mnor consumo, menor área.

**2. AHB (Advanced High-performance Bus)**

- Alta performance.
- Conecta os componentes mais críticos: CPU, memória e controladores DMA.
- É um barramento pipelined (enquanto um dado está sendo transferido, o próximo endereço já está sendo enviado).

**3. AXI (Advanced eXtensible Interface)**

- Altíssima Performance
- Usa canais separados e independentes para cada tipo de informação.
- Realmente simultâneas.

## 6. Interfaces / Protocolos de Comunicação

São os modos transmitir os bits para o mundo externo ao chip e a placa, como para sensores, displays, ou sistemas remotos pela rede. 

- UART.
- I2C.
- SPI.
- CAN.
- USB.

### 6.1 Classificações

**1. Em relação a Sincronia:**

- Protocolos Síncronos: Existe um clock comaprtilhado. Bits são enviados e lidos de acordo com o sinal de clock. 
- Protocolos Assíncronos: Não existe um clock compartilhado. Bits não são enviados e lidos simultaneamente.

**2. Em relação a Duplex:**

- Simplex: Comunicação em apenas uma direção.
- Half-duplex: Comunicação em dois sentidos, mas não simultaneamente (um fala por vez).
- Full-duplex: comunicação em dois sentidos simultaneamente (como uma ligação telefônica).

**3. Em relação a Topologia:**

- Ponto a ponto: Apenas dois dispositivos.
- Multi-drop: Múltiplos dispositivos compartilham o mesmo barramento.

**4. Em relação a Cabeamento:**

- Wired: Uso de cabos. Exemplo: I2C, UART.
- Unwired: Sem uso de cabos. Exemplo: WiFi,

### 6.2 Trade Offs

**1. Velocidade x Distância.**
**2. Número de dispositivos x Complexidade.**
**3. Custo x Confiabilidade.**
**4. × Custo x Escabilidade.**
**5. Desempenho × Consumo de energia.**

### 6.3 Protocolos

**1. UART (Universal Asynchronous Receiver-Transmitter):**

- Usa dois fios (TX e RX). 
- É assíncrona: transmissor e receptor precisam concordar previamente sobre a velocidade.
- Ideal para comunicação ponto a ponto entre dois dispositivos, como a ESP32 e um módulo GPS. 
- Alta velocidade.

**2. I2C (Inter-Integrated Circuit):**

- Usa dois fios (SDA para dados e SCL para o clock). 
- É sincrona: transmissor e receptor precisam concordar nada.
- Permite conectar até 128 dispositivos no mesmo par de fios.
- Dispositivos identificados por um endereço único de 7 bits. 
- Ideal para sensores, displays OLED e potenciômetros digitais.
- Menor Velocidade.

**3. SPI (Serial Peripheral Interface):**

- Usa 3 ou 4 fios (MOSI, MISO, SCLK e um CS por dispositivo). 
- É síncrono. 
- Ideal para displays LCD/TFT, cartões SD, memórias flash externas e conversores de alta resolução.

**3. CAN (Controller Area Network):**

    - usa 2 fios diferenciais.
    - Ideal para ambientes com muita interferência eletromagnética (veículos, fábricas). 
    - Padrão na indústria automotiva e em robótica industrial.

**4. USB (Universal Serial Bus):**

- Interface externa de alta velocidade.
- Presente quando o sistema embarcado precisa se conectar a um computador ou a periféricos USB (câmeras, armazenamento, interfaces de áudio).


**5. Wi-Fi:**

- Permite integrar o sistema embarcado a redes TCP/IP.
- Possibilita comunicação com a internet, servidores em nuvem e outros dispositivos na mesma rede. 

**6. Bluetooth / BLE:** 

- Comunicação de curto alcance (~10 m). 
- O BLE é especialmente relevante em IoT porque consome muito menos energia que o Bluetooth clássico

### Protocolos de aplicação
### 1.5 Periféricos Externos (I/O)

**1. Entrada (Sensores):** Capturam grandezas físicas e as convertem em sinais elétricos que o chip pode processar. Podem ser:

- Digitais: Botões, chaves, encoders, sensores de presença por infravermelho. Geram sinais de dois estados (0 ou 1).
- Analógicas: Sensores de temperatura (NTC/PTC), potenciômetros, sensores de luz (LDR), microfones. Geram tensões contínuas que precisam ser convertidas para digital pelo ADC (Analog-to-Digital Converter) interno do chip.

**2. Saída (Atuadores):** Recebem comandos do processador e produzem efeitos no mundo físico.

- Digitais: Acionados com um simples sinal alto ou baixo no GPIO. Exemplo: LEDs, relés, buzzer. 
- Analógicas: Converte um valor numérico em tensão contínua através do DAC (Digital-to-Analog Converter).


## 2. Tipos de Dispositivos de Processamento

Os chips de processamento existem em diferentes categorias, cada uma otimizada para um conjunto específico de requisitos. 

### 2.1 Microcontroladores (MCU)

**1. Definição:**

É um sistema computacional completo em um único chip. Ele integra CPU, RAM, memória flash , periféricos e interfaces de comunicação sem fio. Não precisa de componentes externos para funcionar, basta alimentação e clock.

**2. Quando usar:** 

Aplicações com baixo consumo de energia, tamanho reduzido, custo baixo, e que não precisam de sistema operacional complexo. 

**3. Exemplos:** 

ESP32, PIC, AVR, MSP430.

### 2.2 Processadores de Propósito Geral (GPP)

**1. Definição:**

São os mesmos processadores dos computadores pessoais. Possuem múltiplos núcleos, caches, MMU completa, e são otimizados para throughput máximo (executar o maior número de instruções por segundo).

**2. Quando usar:** 

Em sistemas embarcados, GPPs aparecem quando a aplicação precisa de um SO completo (Linux, Android), processamento intenso, interface gráfica ou múltiplas aplicações rodando simultaneamente.

**3. Exemplos:**

Processadores Intel Core, AMD Ryzen, ARM Cortex-A. 

A Raspberry Pi usa um processador GPP.

### 2.3 Processadores de Sinal Digital (DSP)

**1. Definição:**

Foram criados para o problema específico de processar fluxos de dados numéricos em altíssima velocidade. 

**2. Quando usar:** 

Processamento de áudio, vídeo, radar, sonar, comunicações sem fio, controle de motores que exigem algoritmos de controle vetorial.

### 2.5 Field Programmable Gate Arrays (FPGA)

**1. Definição:**

São circuitos integrados cujo comportamento pode ser reprogramado após a fabricação. Pode implementar centenas de operações acontecendo paralelamente.

**2. Quando usar:** 

Protocolos de comunicação personalizados, aceleração de algoritmos paralelos, interfaces com timing muito rígido, processamento de sinal de alta velocidade.

### 2.5 Field Programmable Gate Arrays (FPGA)

**SoC (System-on-Chip):** Integra em um único circuito integrado componentes que antes precisavam de chips separados: CPU, GPU, controladores de memória, interfaces de comunicação (USB, HDMI, Ethernet), DSPs para comunicação sem fio. O processador de smartphones é um SoC.

**MPSoC (Multiple Processor SoC):** Inclui múltiplos processadores programáveis de arquiteturas possivelmente diferente em um único chip.

### 2.6 Application Specific Integrated Circuits (ASIC)

**1. Definição:**

Um ASIC é um circuito projetado e fabricado especificamente para uma única função. Uma vez fabricado, não pode ser reprogramado. 


**2. Quando usar:** 

ASICs têm custo de desenvolvimento absurdamente alto mas custo unitário muito baixo em produção em massa. São a escolha para produtos de alto volume onde eficiência e custo por unidade são crítico

**3. Exemplos:**

Chips de calculadoras e mouses e processador de modems 4G.