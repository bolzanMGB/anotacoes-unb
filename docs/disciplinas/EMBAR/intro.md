# Introdução Sistemas Embarcados

---

## 1. Definição

Um sistema embarcado é um sistema de hardware e software combinado, feito para executar uma função específica continuamente. Essa função faz parte de um sistema maior e tem conexão com o mundo físico.

Eles geralmente leem o mundo externo através de sensores, processam esses dados e alteram o mundo externo através de atuadores. São exemplos: SmartTVs, micro-ondas, airbags e smartwatches.

---

## 4. Características

**Especificação:** aplicação bem definida e pré-definida.

**Restrições de tempo-real:** hard real-time ou soft real-time.
- Confiabilidade e segurança.
- Eficiência energética: muitos operam com bateria.
- Baixo custo.
- Restrição de memória.

---
## 3. Classificações

**Sistema similares à computadores de propósito geral:** video games, tablets, smartphones.
**Sistemas de controle:** controle de eletrodomésticos.
**Processamento de Sinais:** radar, decodificador de TV.
**Comunicação e redes:** telefones, roteadores.

---

## 5. Componentes de Arquitetura

![Inserção](../../assets/pngs/93.png){align=center }

### 5.1 Hardware
**Processador:** É o cérebro. Pode ser um microcontrolador (MCU), um microprocessador (MPU) ou um DSP (Processador Digital de Sinais).

**Memória:** Armazena tanto o código (Software) quanto os dados temporários. Em SE, costuma ser Flash (para o programa) e RAM (para variáveis).

**Periféricos e Dispositivos de Entrada e Saída:**

- Entradas Analógicas (ADC): Converte sinais do mundo real (como temperatura ou voltagem) em número que o processador entende.
- Saídas Analógicas (DAC): Faz o caminho inverso, transformando dados digitais em sinais elétricos para controlar algo.
- Entrada/Saídas Digitais: Lidam com estados binários (0 ou 1).

**Interfaces de Comunicação:** São os protocolos que permitem o processador falar com outros chips e redes.

### 5.2 Software

**Software do Sistema:**
- RTOS: Usado para gerenciar tarefas de restrições de tempo.
- Ferramentas de Debug: Essenciais para ver erros enquanto o código roda.

**Aplicação:** É o código final que você escreve. Ex: caso sensor de temperatura ler > 40°, ligar o ventilador.

## 6. Software Embarcado

### 6.1 Requisitos

## 7. Projeto de um Sistema Embarcado

## 8. Arquiteturas de Hardware
### 8.1 Microcontroladores
### 8.2 Processador de Propósito Geral (GPP)
