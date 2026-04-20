# Sobre o Projeto

## 1. Tema

Desenvolver um Micromouse que resolve labirintos.

## 2. Objetivo

O objetivo do micromouse será encontrar uma sala retangular no centro do labirinto. Serão três labirintos:

- 1° terá 4x4 células, com 72cm de lado
- 2° terá 8x8 células, com 144 cm de lado;
- 3° terá 16x16 células, com 288 cm de lado.


## 3. Requisitos Funcionais

### 3.1 Interface Web
#### 3.1.1 Exibição do tipo de labirinto
O sistema deve identificar e exibir o tipo de labirinto selecionado para o percurso atual.

#### 3.1.2 Exibição do mapeamento e trajeto
Em relação ao percurso atual, o sistema deve exibir e atualizar em tempo real o mapeamento da localização e o trajeto do Micromouse no labirinto.

#### 3.1.3 Exibição da bateria disponível
O sistema deve exibir e atualizar em tempo real a porcentagem de bateria disponível do Micromouse.

#### 3.1.4 Exibição da bateria consumida
O sistema deve exibir e atualizar em tempo real a porcentagem de bateria consumida pelo Micromouse durante o trajeto.

#### 3.1.5 Exibição do tempo de percurso
O sistema deve exibir e atualizar em tempo real a telemetria do tempo decorrido até a conclusão ou interrupção do desafio.

#### 3.1.6 Status do desafio
Após a conclusão do percurso, o sistema deve exibir se o desafio foi cumprido com sucesso ou não.

#### 3.1.7 Exibição da velocidade média
Após a conclusão do percurso, o sistema deve exibir a velocidade média mantida pelo Micromouse.

### 3.2 Consultas no Banco de Dados
#### 3.2.1 Persistência por tipo de labirinto
Após a conclusão do desafio, os dados finais devem ser armazenados em um banco de dados, categorizados de acordo com o tipo de labirinto.

#### 3.2.2 Consulta de trajetos históricos
O sistema deve permitir a consulta e exibição de dados de qualquer trajeto específico armazenado, independentemente do tipo de labirinto.

## 4. Requisitos Não Funcionais

### 4.1 Desempenho e Eficiência 
#### 4.1.1 Latência de Telemetria
O sistema web deve receber, processar e exibir os dados de localização, velocidade e bateria do Micromouse com uma latência máxima de 200 ms.

#### 4.1.2 Tempo de Execução do Algoritmo
O algoritmo de navegação deve processar a tomada de decisão em um tempo inferior a ?.

#### 4.1.3 Otimização de Trajeto
O número de passos executados pelo algoritmo no caminho final não deve exceder ? do caminho ótimo calculado.

### 4.2 Precisão e Confiabilidade
#### 4.2.1 Integridade dos Dados
O sistema deve garantir que 100% dos dados de telemetria recebidos sejam persistidos no banco de dados sem perdas.

### 4.3 Usabilidade e Visualização
#### 4.3.1 Adaptabilidade da Interface
O sistema web deve ajustar automaticamente a escala visual do mapeamento para os três tipos de labirinto (4x4, 8x8 e 16x16), garantindo a visibilidade integral das células.

#### 4.3.2 Atualização de Status em Tempo Real
O indicador de "Desafio Cumprido" deve ser ativado imediatamente após o robô detectar a entrada na área de destino central.

#### 4.3.3 Responsividade Multiplataforma
A interface web deve adaptar-se automaticamente a diferentes resoluções, garantindo 0% de elementos cortados ou sobrepostos
