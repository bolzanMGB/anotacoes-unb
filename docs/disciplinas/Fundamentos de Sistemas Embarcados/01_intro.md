# Introdução Sistemas Embarcados

## 1. Definição


Um Sistema Embarcado é um sistema de hardware e software combinados projetado para executar continuamente uma mesma função específica e predefinida.

Eles se difere de computadores de propósito geral por estes não terem sido fabricados com uma ideia prévia e exata de suas funções.

Sistemas Embarcados executam funções que fazem parte de um todo maior, como por exemplo um Airbag de um carro.

Além disso, muitas vezes suas funções envolvem a captura e leitura de dados do mundo reais (através de sensores) e o retorno de ações com base no processamento desses mesmos dados.

Exemplos: SmartTVs, aeronaves, micro-ondas, airbags e smartwatches.


## 2. Características

**1. Aplicação predefinida:** O código que vai rodar é conhecido desde o início do projeto.

**2. Confiabilidade e Restrições de tempo real:** Muitas vezes aplicações embarcadas precisam funcionar corretamente em todas as condições, incluindo falhar parciais. A sua resposta a eventos externos deve ocorrer sempre dentro do prazo (deadline), e caso esse deadline for perdido as consequências podem ser catastróficas. Exemplo: equipamento médico e aeronave.

**3. Restrições de Energia:** Geralmente são alimentados por bateria e precisam de técnicas para minimizar o consumo de energia.

**4. Custo e tamanho:** Geralmente são fabricados em alta escala. Assim, alguns centavos a menos ou a mais no custo de uma unidade faz toda a diferença e por isso são projetados para cumprir apenas o suficiente para a função desejada.

## 3. Áreas de Aplicação

Sistemas embarcados estão em todo lugar: aviação (fly-by-wire, FADEC), automotivo (ABS, airbag, injeção eletrônica), telecomunicações (roteadores, switches), robótica (controladores de motores, visão computacional), automação industrial (CLPs, SCADA), eletrodomésticos, dispositivos médicos, eletrônicos de consumo e IoT.

## 5. Arquitetura de Software

### 5.1 Camada de Abstração de Hardware

Código que manipula diretamente os registradores, bits e endereços de memória do processador. Ela esconde a complexidade do hardware e fornece funções amigáveis. Inclui:

- Drivers.
- HAL (Hardware Abstraction Layer).

### 5.2 Modelo de Gerenciamento

Define como o tempo e as tarefas do processador serão gerenciados. O sistema deve adotar uma das seguintes estratégias principais:

**1. Bare Metal:**  Sem Sistema Operacional, baseado em Super Loop e Interrupções. 

O processador liga, executa as configurações iniciais (setup()) e entra em um loop infinito (while(1)). Eventos críticos e assíncronos são tratados pausando o loop temporariamente através de Interrupções de hardware.

**2. RTOS (Real-Time Operating System):** Com Sistema Operacional minimalista focado em tempo real e prazos rígidos (deadlines). Exemplo: Kernel FreeRTOS.

O código é dividido em funções independentes chamadas Tasks. O Kernel (núcleo do S.O) utiliza um escalonador para "fatiar" o tempo do processador (ex: roda a Task A por 1ms, depois a Task B por 1ms), permitindo multitarefa e concorrência baseada em prioridades.

**3. GPOS (General Purpose Operating System)** Com Sistema Operacional de proósito geral, é um linux customizado e reduzido para a aplicação.

Utilizado em processadores mais robustos (GPPs/SoCs). Gerencia memória complexa (via MMU), sistemas de arquivos grandes e múltiplas aplicações simultâneas, sacrificando o determinismo rígido de tempo real em prol de alta capacidade de abstração e rede.

### 5.3 Camada Intermediária (Middleware)

Softwares e bibliotecas que rodam acima da infraestrutura de execução para resolver problema sem que você precise reescrevê-los do zero. Inclui:

### 5.4 Camada de Aplicação

O código exclusivo do seu projeto que consome as funções do Middleware e HAL para executar a sua lógica do negócio.



