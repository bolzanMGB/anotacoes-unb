# **Análise e Modelagem de Requisitos**

---

## **1. O que é**

A fase de **Análise e Modelagem** busca entender, estruturar e organizar os requisitos coletados na elicitação. Aqui, não basta apenas listar os requisitos; é necessário representá-los de forma clara e compreensível para que tanto os stakeholders quanto a equipe técnica consigam interpretar da mesma maneira.

---

## **2. Objetivos principais**

* Reduzir ambiguidades e inconsistências nos requisitos.
* Criar representações visuais que facilitem o entendimento.
* Conectar requisitos a personas, cenários e fluxos de uso reais.
* Preparar os requisitos para priorização, planejamento e rastreabilidade.

---

## **3. Como funciona**

### **3.1 Refinamento de Requisitos**

* **O que é:** Revisar os requisitos coletados para corrigir ambiguidades, redundâncias e incompletudes.
* **Exemplos:** Ajustar descrições vagas, remover duplicações ou requisitos contraditórios.
* **Uso:** Garantir que os requisitos estejam claros e consistentes antes da modelagem detalhada.

### **3.2 Classificação de Requisitos**

* **O que é:** Separar requisitos em funcionais e não funcionais.
* **Exemplos:**

  * Funcionais: “O sistema deve permitir login por biometria”.
  * Não funcionais: desempenho, segurança, usabilidade.
* **Uso:** Facilitar priorização, design e testes.

### **3.3 Representação Visual e Textual**

* **O que é:** Criar diagramas e modelos que ajudem a visualizar o sistema e suas interações.
* **Exemplos:** Diagramas de fluxo, diagramas UML, tabelas de requisitos.
* **Uso:** Melhorar comunicação entre equipe técnica e stakeholders.

### **3.4 Criação de Perfis de Usuário e Personas**

* **O que é:** Representar os usuários do sistema de forma estruturada.
* **Exemplos:**

  * Perfil de usuário: grupo de usuários com características comuns (idade, experiência, habilidades).
  * Persona: personagem fictício detalhando objetivos, frustrações e motivações.
* **Uso:** Priorizar funcionalidades e guiar decisões de design.

### **3.5 Mapeamento de Cenários e Fluxos de Trabalho**

* **O que é:** Descrever situações típicas de uso do sistema.
* **Exemplos:** Cenário principal (fluxo normal) e cenários alternativos (erros ou exceções).
* **Uso:** Validar casos de uso, identificar requisitos ocultos e auxiliar em testes.

---

## **4. Técnicas Comuns de Modelagem**

### **4.1 Casos de Uso**

* **O que é:** Descrevem interações entre atores e o sistema para atingir um objetivo.
* **Exemplos:** Login, cadastro de cliente, processamento de pedido.
* **Uso:** Identificar funções do sistema e validar requisitos funcionais.

### **4.2 Diagramas UML**

* **O que é:** Representações gráficas do sistema e suas interações.
* **Exemplos:**

  * Diagrama de sequência: interação entre objetos ao longo do tempo.
  * Diagrama de atividades: fluxo de processos.
  * Diagrama de classes: entidades e suas relações.
* **Uso:** Facilitar entendimento e documentação dos requisitos.

### **4.3 Histórias de Usuário**

* **O que é:** Pequenas descrições de funcionalidades do ponto de vista do usuário.
* **Exemplos:** “Como \[tipo de usuário], quero \[ação] para \[benefício]”.
* **Uso:** Guiar desenvolvimento ágil e priorização.

### **4.4 Especificação Suplementar**

* **O que é:** Documento que complementa casos de uso, descrevendo requisitos adicionais, normalmente não funcionais ou restrições.
* **Exemplos:** Desempenho, segurança, confiabilidade, requisitos legais.
* **Uso:** Registrar formalmente requisitos que não estão nos casos de uso.

### **4.5 Cenários**

* **O que é:** Narrativa de uma sequência de ações representando o uso do sistema em situações específicas.
* **Exemplos:** Fluxo normal de compra, fluxo alternativo em caso de falha de pagamento.
* **Uso:** Validar casos de uso, descobrir requisitos ocultos e criar testes.

### **4.6 Léxico / Glossário**

* **O que é:** Lista de termos e definições importantes para o projeto.
* **Exemplos:** “Usuário administrador: pessoa com permissão para gerenciar contas e dados do sistema”.
* **Uso:** Evitar ambiguidades e mal-entendidos entre stakeholders e equipe técnica.

### **4.7 Backlog**

* **O que é:** Lista priorizada de requisitos, funcionalidades e tarefas, geralmente usada em metodologias ágeis.
* **Exemplos:** Product backlog, sprint backlog.
* **Uso:** Servir como guia de desenvolvimento, priorizando itens por valor, urgência ou complexidade.

### **4.8 Requisitos Não Funcionais (NFR)**

* **O que é:** Descrevem como o sistema deve se comportar, em vez do que deve fazer.
* **Exemplos:**

  * Desempenho: “O sistema deve processar 1000 transações por segundo”.
  * Segurança: “Os dados devem ser criptografados em trânsito e em repouso”.
  * Usabilidade: “Usuários novos devem completar cadastro em menos de 3 minutos”.
* **Uso:** Garantir qualidade do sistema e aceitação pelo usuário.

