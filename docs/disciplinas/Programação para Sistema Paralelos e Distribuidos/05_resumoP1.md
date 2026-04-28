# Resumo P1

## 1. Introdução Sistemas Distribuídos

Mainframes -> Lies de Moore -> Microprocessadoes e Redes de alta velocidade.

### 1.1 Conceito

- Conceito Tanembaum: tem a visão do usuário
- Conceito Colouris: mais sobre comunicaçãp

### 1.2 Características

- Homogeneidade
- Middleware.
- Transparência.
- Interfaces publicadas.
- Interoperabilidade
- Portabilidade
- Extensibilidade.
- Segurança
- Escalabilidade
- Mascaramento de Falhas
- Concorrência;

### 1.3 Finalidades

1. Sistemas de Computação Distribuídos e de Alta Perfomance
- 1.1 Sistemas de Computação de Cluster: 
        - Homogeneo.
        - Local
- 1.2 Sistemas de Computação em Grade: 
        - Diferente.
        - Virtual

2. Sistema de Informação Distribuídos
- 2.1 Sistemas de Processamento de Transações (SPT): integridade, bancários
- 2.2 Integração de Aplicações Empresariais (EAI): comunicação, empresas
- 2.3 Sistemas Distribuídos Ubíquos e Pervasivos: focam em invisibilidade, wifi

## 2. Estilos Arquitetônicos 
Organização do Software

1. Arquitetura em Camadas.
- 1.1 Arquitetura Cliente-Servidor
- 1.2 Arquitetura em Múltiplas Camadas

2. Arquitetura Baseada em Serviços
- 2.1 Arquitetura Baseada em Objetos.
- 2.2 Arquitetura Baseada em Microsserviços.
- 2.3 Arquitetura Baseada em Recursos.

3. Arquitetura Baseadas Publicar-Subscrever
- 3.1 Baseada em Eventos
- 3.2 Espaço de Dados Compartilhados

### 2.1 Arquitetura em Camadas:
Fluxo: requisições de cima para baixo, respostas de baixo para cima.

#### 1. Cliente e Servidor
- Cliente: é ativo, envia um requisição ao servidor.
- Servidor: é passivo, esperando continuamente uma requisição para responder.

**Cliente Gordo e Magro**
- Cliente magro:
    - Possui pouco código (só interface).
    - Maioria do processamento e dados ficam no servidor.
    - Fácil de gerenciar.
    - Tendencia atual.
- Cliente gordo: 
    - possui  muito código.
    - cuida da interface e parte do processamento.
    - Díficl de gerenciar.

#### 2. Arquitetura de Múltiplas Camadas (IDP)
- Nível de Interface/Aplicação: janelas gráficas q o usuario lida.
- Nível de Processamento: lógica da aplicação
- Nivel de Dados: banco de dados

### 2.2 Arquitetura Baseada em Serviços
Os sistemas viram entidades

- Baseada em Objetos
- Baseada em Microserviços
- Baseada em Recursos

### 2.3 Arquiteturas Publicar-Subscrever
Há um middleware que faz a comunicação entre os sistemas.

- Desacoplamento no Espaço: remetende não quem é o destinatario e vice-versa.
- Descaoplamento no Tempo: remetendo e destinário nao precisam esta rodando ao mesmo tempo.

#### 1. Baseada em Eventos

- Um processa publicador anuncia um evento.
- Outros processos manifestam interesse.
- Desacomplado no espaço.
- Acoplado no tempo.

#### 2. Baseada em Dados Compartilhados

- Há um repositorio persistente.
- O processo publicador insere dados no repositorio.
- Os processos fazem buscas no repositorio para achar dados que eles querem.
- Desacoplado no espaço.
- Desacoplado no tempo.

