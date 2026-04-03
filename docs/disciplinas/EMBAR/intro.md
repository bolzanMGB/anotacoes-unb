# Introdução Sistemas Embarcados

---

## 1. Definição

Um sistema embarcado é um sistema de hardware e software combinado, feito para executar uma função específica continuamente. Essa função faz parte de um sistema maior e tem conexão com o mundo físico.

Eles geralmente leem o mundo externo através de sensores, processam esses dados e alteram o mundo externo através de atuadores. São exemplos: SmartTVs, micro-ondas, airbags e smartwatches.

---

## 2. Características

**Especificação:** Aplicação bem definida e pré-definida.

**Restrições de tempo-real:** A resposta do sistema deve ocorrer dentro de um limite de tempo rigoroso.

- Hard Real-Time: Se o tempo limite for perdido, o sistema falha totalmente. Ex: acionamento de airbag.

- Soft Real-Time: Perde o limite de tempo diminui qualidade, mas ão destrói o sistema. Ex: atraso em um vídeo de uma plataforma de streaming

**Confiabilidade e Tolerância a Falhas:** Precisam operar anos sem reinicialização ou update de software ou falhas físicas.

**Eficiência Energética:** mMuitos operam com baterias.

**Baixo custo e Restrição de memória**


---

## 3. Arquitetura de Hardware

![Inserção](../../assets/pngs/93.png){align=center }

### 3.1 Componentes

A arquitetura de software é escolhida com base da necessidade de poder de processamento, consumo de bateria e custo. Principais componentes são:

**Unidade Central (Chip)**

- **Processador:** O núcleo que executa as instruções matemáticas e lógicas.

- **Memória:** Armazena tanto o código do software (Flash), quanto os dados temporários (RAM).

**Barramentos:** São as estradas internas que conectam o processador à memória e às interfaces, permitindo que os dados trafeguem entre eles.

- **Interfaces de Comunicação:** Permitem conversar com outros dispositivos. Ex: Wi-Fi, Bluetooth.

**Periféricos Externos**

- **Sensores:** Entradas analógicas ou digitais que capturam dados (ex: temperatura, pressão).

- **Atuadores:** Saídas analógicas ou digitais que realizam a ação no mundo físico (motores, telas).


### 3.2 Categorias de Dispositivos de Processamento

Os dispositivos de processamento são os diferentes tipos de chips que formam o núcleo do hardware. Cada um organiza o processador, a memória e os periféricos de uma forma específica para atender a diferentes necessidades:

**Microcontroladores (MCUs)**

São computadores em um único chip. Nele processador, memória e periféricos estão embutidos em uma única pastilha de silício.

São extremamente baratos, consomem pouquíssima energia e resolvem 90% dos problemas de automação básica e eletrodoméstico.

**Processadores de Propósito Geral (GPPs)**

Chips poderosos, mas arquiteturalmente "dependentes". Eles não têm memória RAM ou interfaces de disco internas; dependem de componentes externos soldados na placa.

Usados quando há necessidade de alto processamento ou interfaces gráficas pesadas. Exemplos: Processadores ARM Cortex-A (como no Raspberry Pi) ou Intel Core.

**Processadores de Sinais Digitais (DSPs)**

Microprocessadores projetados especificamente para cálculos matemáticos contínuos e pesados. Utilizam a "Arquitetura Harvard", que possui vias separadas para dados e instruções, permitindo processar informações muito mais rápido.

Possuem unidades MAC (Multiply-and-Accumulate) que conseguem multiplicar e somar números em um único ciclo de clock.São essenciais para processamento de áudio, voz, radares, sonares e telecomunicações.

**FPGAs (Field Programmable Gate Arrays)**

Hardware que pode ser "reprogramado" pelo usuário. Ao invés de escrever um software que roda em um processador fixo, você escreve um código que fisicamente reestrutura o chip para criar circuitos digitais customizados.

Compostos por uma enorme matriz de unidades lógicas e chaves de interconexão configuráveis.

Executam tarefas em paralelo com velocidade extrema. São usados em processamento de vídeo em tempo real ou cálculos de altíssima velocidade.

**ASICs (Application Specific Integrated Circuits)**

Circuitos integrados fabricados e "fundidos" na fábrica para fazer apenas uma tarefa. Não podem ser reprogramados.

Possuem a maior eficiência energética e velocidade possível. Embora o custo de criar o primeiro chip seja na casa dos milhões, eles se tornam centavos quando fabricados em grande escala (ex: chip controlador do seu mouse ou do micro-ondas).

**SoCs (System-on-Chip) e MPSoCs**

O ápice da integração. Colocam GPPs, Placas de Vídeo (GPUs), interfaces Wi-Fi/Modem e até FPGAs dentro de um mesmo chip físico. Os Multiple Processor System-on-Chip (MPSoCs) usam múltiplos núcleos (cores) diferentes no mesmo chip interligados por uma rede interna (Network-on-chip).

A maior parte dos processadores de smartphones modernos (Snapdragon, Apple A-Series) são SoCs/MPSoCs, pois economizam espaço físico e entregam poder computacional massivo.

## 4. Cenário de Mercado

**Principais Aplicações:** 
- Controle Industrial e Automação (32%).
- Eletrônicos de Consumo (29%).
- Internet das Coisas (25%).

**Linguagens de Programação:**
- C   (56%).
- C++ (29%).

**Sistemas Operacionais:**
- Linux.
- FreeRTOS;
- Bare metal (código direto no hardware).
