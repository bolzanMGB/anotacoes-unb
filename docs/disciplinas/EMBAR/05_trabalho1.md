# Trabalho 1: Controle de Cruzamentos de Trânsito com Câmeras LPR

## 1. Contexto
Desenvolver um sistema de controle e monitoramento de cruzamentos de sinais de trânsito. Esse sistema vai ser enviado a uma Raspberry Pi, que está conectada numa ESP32,onde o sistema de trânsito esta sendo simulado. 

Na ESP32, está rodando um código que simula uma lógica de tráfego com carros virtuais, pistas, semáforos, radares, faixas de pedreste e etc, que é transmitida e visualizada em uma interface (dashboard).

Assim, A ESP32 também simula que os carros e o sistema são reais usando eletricidade. Quando um carro virtual, por exemplo, passa pelo sensor no simulador, a ESP32 manda 3.3V no pino físico da GPIO da Raspberry Pi.

## 2. Arquitetura do Sistema


```
┌──────────────────────────────────────────────────────────────┐
│                     Raspberry Pi                             │
│                                                              │
│  ┌─────────────────┐     TCP/IP     ┌────────────────────┐   │
│  │ Servidor Central│◄──────────────►│ Servidor Dist. 1   │   │
│  │                 │     TCP/IP     ├────────────────────┤   │
│  │  (Monitora e    │◄──────────────►│ Servidor Dist. 2   │   │
│  │   Coordena)     │                └────────────────────┘   │
│  └────────┬────────┘                        │                │
│           │ RS485 MODBUS                    │ GPIO           │
└───────────┼─────────────────────────────────┼────────────────┘
            │                                 │
            ▼                                 ▼
┌───────────────────────────────────────────────────────────────┐
│                          ESP32                                │
│                                                               │
│  Câmeras LPR (MODBUS slave)    Semáforos / Sensores / Botões  │
│  0x11 · 0x12 · 0x13 · 0x14    (GPIO — entradas e saídas)      │
│                                                               │
│  Widget ThingsBoard (MQTT)                                    │
│  → Modo Noite/Dia  · Carro de Emergência                      │
└───────────────────────────────────────────────────────────────┘
```

**1. Servidores Distribuídos**

Atuam lidando diretamente com o hardware: 

- RPI envia um código de 3 bits, através dos pinos GPIO, para a ESP32 via GPIO, enviando códigos de 3 bits da ESP32 para a RPi.
- Sensores do simulador ou botões do dashboard mandam bits em nível alto para os pinos da GPIO, que é detectado pela RPi através de código do usuário. 

Eles realizam o tratamento de sensores e interrupções, reportando estados e eventos de forma assíncrona ao Central. Há dois servidores distribuídos e cada um controla um cruzamento, sendo que cada cruzamento possui:

- 2 semáforos.
- 2 botões de pedestre.
- 2 sensores de velocidade.
- 2 câmeras LPR (License Plate Recognition) de velocidade.

**2. Servidor Central**

É a parte exterior a simulação. Ele recebe dados dos cruzamento e manda respostas para eles, envia esses dados oa dashboard e faz a integração de protocolos distintos

## 3. Funcionamento





### 2.3 Funcionamento Geral


## 3. Conexões GPIO (RPi -> ESP32)

### 3.1 Controle de Semáforos (RPi → ESP32)
### 3.2 Sensores de Velocidade (ESP32 → RPi)
### 3.2 Botões de Pedestre (ESP32 → RPi)

## 4. Integração RS485 (MODBUS RTU)

### 4.1 Endereços dos Dispositivos
### 4.2 Mapa de Registradores das Câmeras LPR 
### 4.3 Mapa de Registradores do Estado do Sistema 

## 5. Requisitos do Sistema

### 5.1 Servidores Distribuídos

Código que deve controlar as responsabilidades de:

**1. Controlar os semáforos via GPIO obedecendo a temporização.**
2. **Controlar os botões de pedestre** via GPIO: ao detectar o acionamento, antecipar a mudança de estado do semáforo correspondente (respeitando o tempo mínimo de verde já decorrido);
3. **Medir a velocidade dos veículos** via GPIO (sensores A e B): calcular a velocidade a partir do intervalo de tempo entre os pulsos, contar a passagem de cada veículo;
4. **Reportar ao Servidor Central** (via TCP/IP, a cada 2 segundos) a contagem de veículos por sensor;
5. Ao detectar veículo **acima de 60 km/h**, enviar imediatamente aviso (*push*) ao Servidor Central com: `{cruzamento, sensor_id, velocidade_kmh, timestamp}`;
6. Obedecer comandos do Servidor Central para **modo noturno** (amarelo intermitente) e **modo de emergência** (via principal verde, cruzamento vermelho);
7. Configurar-se automaticamente para o cruzamento 1 ou 2 a partir de um **arquivo de configuração** (pinos, porta TCP, etc.).


### 5.2 Servidor Central

O código do Servidor Central deve atender as seguintes responsabilidades:

1. **Manter conexão TCP/IP** com os dois Servidores Distribuídos;
2. **Ler periodicamente** (via MODBUS RS485, endereço 0x20) o estado Noite/Dia e o estado de Emergência;
3. Ao detectar **modo noturno**, comandar ambos os Servidores Distribuídos para ativar o **amarelo intermitente**;
4. Ao detectar **veículo de emergência**, comandar ambos os cruzamentos para **abrir passagem** na via principal até o evento ser encerrado;
5. Ao receber aviso de infração de velocidade de um Servidor Distribuído, **acionar a câmera LPR** correspondente via MODBUS RS485 e **registrar a multa** (placa, velocidade, câmera, timestamp, valor da multa) em arquivo de log;
6. Manter **histórico de passagens** de veículos por cruzamento e via;
7. Prover **interface** (terminal ou web) com as seguintes informações por cruzamento:
   - Fluxo de tráfego por sensor (carros/min);
   - Velocidade média por sensor (km/h);
   - Total de infrações de velocidade e respectivas multas;
   - Comandos manuais em que o usuário possa controlar o estado dos semáforos e o modo noturno (piscar amarelo);  
8. **Armazenar de modo persistente** (arquivo) o estado atual para que possa ser reestabelecido em caso de reinicialização.


### 5.3 Requisitos Gerais

1. Em qualquer linguagem, deve haver instruções explícitas de como instalar e executar o sistema;
2. Para C/C++, é mandatório o uso de **Makefile** com todas as dependências no projeto;
3. Cada serviço deve poder ser **iniciado independentemente** e aguardar a conexão dos demais;
4. Qualquer queda de comunicação deve ser **reestabelecida automaticamente** sem perda de função;
5. O código deve ser modular com arquitetura bem definida. Programas completos em arquivo único terão a nota de arquitetura em Zero.
5. O repositório deve conter um arquivo **README** descrevendo a instalação, configuração e uso.


## 6. Detalhes de Implementação

### 6.1 Cálculo de Velocidade

O sensor de velocidade possui dois pinos (A e B). Na passagem de um veículo:

- O pino A é ativado (borda de subida) primeiro;
- O pino B é ativado (borda de subida) após um intervalo $\Delta t$;
- A velocidade é calculada por:

$$v = \frac{2\;\text{m}}{\Delta t} \times 3{,}6 \quad [\text{km/h}]$$

No simulador, $\Delta t$ varia entre **15 ms** (≈ 480 km/h) e **300 ms** (≈ 24 km/h).

### 6.2 Modo Noturno

Quando ativado, o Servidor Distribuído deve alternar o código dos semáforos entre o estado **0** (amarelo) e o estado **4** (vermelho total / apagado) com período de **2 segundoa** (1s em cada estado), simulando o pisca-pisca amarelo.

### 6.3 Modo de Emergência

Quando ativado, os Servidores Distribuídos devem manter a respevtiva via liberada (sinal verde) até receber a desativação do Servidor Central.

### 6.4 Registro de Multas (Log)

O arquivo de log deve conter, para cada multa:

```
timestamp | cruzamento | sensor | velocidade (km/h) | câmera MODBUS | placa | confiança (%) | Valor da Multa
```