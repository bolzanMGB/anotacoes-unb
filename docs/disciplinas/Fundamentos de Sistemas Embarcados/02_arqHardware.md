# Arquitetura de Hardware

## 1. Arquitetura de Hardware

Todo sistema embarcado, independente do tamanho ou complexidade, é formado pelos mesmos blocos fundamentais. Eles são:


### 1.1 Processador(CPU)

É o núcleo e cérebro do sistema. O processador busca instruções armazenadas na memória, decodifica o que cada instrução significa e as executa, seja  operações matemáticas, lógicas e de controle de fluxo. 

O processador determina a capacidade de processamento disponível: 

- Frequência de clock: quantas operações por segundo.
- Arquitetura: quantos bits processa de uma vez (8, 16, 32 ou 64 bits).
- Unidades especiais: pode possuir ou não. Exemplo: FPU (Floating Point Unit, para cálculos com decimais) e MMU (Memory Management Unit, necessária para rodar Linux).

### 1.2 Memória:

Pode ser: 

**1. Memória Não-Volátil (Flash/ROM):** armazena o código do programa (firmware) de forma permanente. Mesmo sem energia, o conteúdo persiste. Quando o sistema liga, o processador busca as instruções a partir daqui. É lenta para escrita.

**2. Memória Volátil (RAM — Random Access Memory):** armazena as variáveis, pilhas de função e dados em uso durante a execução. É muito mais rápida que a flash para leitura e escrita. Todo seu conteúdo é perdido ao desligar o sistema. Geralmente é escassa e deve ser gerenciada com cuidado.

Alguns sistemas embarcados possuem ainda memória EEPROM ou áreas de NVS (Non-Volatile Storage) dentro da flash para armazenar pequenas configurações persistentes (senhas, calibrações, estados) que precisam sobreviver a reinicializações mas também precisam ser atualizadas durante a vida do produto.

### 1.3 Barramentos:

Os barramentos internos são as "estradas" que interligam o processador, a memória e os periféricos dentro do chip ou da placa. Sem eles, cada componente seria uma ilha isolada.Um barramento é composto por três grupos de sinais: 

- Barramento de Endereço: indica qual posição de memória ou qual periférico está sendo acessado.
- Barramento de Dados: transporta o dado em si.
- Barramento de Controle: sinais como clock e read/write que coordenam quem fala e quando.

### 1.4 Interfaces de Comunicação

Permitem que o chip converse com o mundo externo: outros chips na mesma placa, sensores, displays, ou sistemas remotos pela rede. Podem ser:

**1. Comunicação Cabeada (Wired):**

- UART (Universal Asynchronous Receiver-Transmitter): 
    - Usa dois fios (TX e RX). 
    - É assíncrona: transmissor e receptor precisam concordar previamente sobre a velocidade.
    - Ideal para comunicação ponto a ponto entre dois dispositivos, como a ESP32 e um módulo GPS. 
    - Alta velocidade.
- I2C (Inter-Integrated Circuit): 
    - Usa dois fios (SDA para dados e SCL para o clock). 
    - É sincrona: transmissor e receptor precisam concordar nada.
    - Permite conectar até 128 dispositivos no mesmo par de fios.
    - Dispositivos identificados por um endereço único de 7 bits. 
    - Ideal para sensores, displays OLED e potenciômetros digitais.
    - Menor Velocidade.
- SPI (Serial Peripheral Interface): 
    - Usa 3 ou 4 fios (MOSI, MISO, SCLK e um CS por dispositivo). 
    - É síncrono. 
    - Ideal para displays LCD/TFT, cartões SD, memórias flash externas e conversores de alta resolução.
- CAN (Controller Area Network): 
    - usa 2 fios diferenciais.
    - Ideal para ambientes com muita interferência eletromagnética (veículos, fábricas). 
    - Padrão na indústria automotiva e em robótica industrial.
- USB (Universal Serial Bus): 
    - Interface externa de alta velocidade.
    - Presente quando o sistema embarcado precisa se conectar a um computador ou a periféricos USB (câmeras, armazenamento, interfaces de áudio).

**2. Comunicação Sem Fio (Wireless):**

- Wi-Fi: 
    - Permite integrar o sistema embarcado a redes TCP/IP.
    - Possibilita comunicação com a internet, servidores em nuvem e outros dispositivos na mesma rede. 
- Bluetooth / BLE: 
    - Comunicação de curto alcance (~10 m). 
    - O BLE é especialmente relevante em IoT porque consome muito menos energia que o Bluetooth clássico

### 1.5 Periféricos Externos (I/O)

**1. Entrada (Sensores):** Capturam grandezas físicas e as convertem em sinais elétricos que o chip pode processar. Podem ser:

- Digitais: Botões, chaves, encoders, sensores de presença por infravermelho. Geram sinais de dois estados (0 ou 1).
- Analógicas: Sensores de temperatura (NTC/PTC), potenciômetros, sensores de luz (LDR), microfones. Geram tensões contínuas que precisam ser convertidas para digital pelo ADC (Analog-to-Digital Converter) interno do chip.

**2. Saída (Atuadores):** Recebem comandos do processador e produzem efeitos no mundo físico.

- Digitais: Acionados com um simples sinal alto ou baixo no GPIO. Exemplo: LEDs, relés, buzzer. 
- Analógicas: Converte um valor numérico em tensão contínua através do DAC (Digital-to-Analog Converter).
- PWM: Simula uma tensão analógica usando uma saída digital. Exemplo: motores DC (velocidade), servomotores (posição), LEDs com controle de brilho. 

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