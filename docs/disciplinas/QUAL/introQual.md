# Introdução

---

https://aprender3.unb.br/pluginfile.php/3230264/mod_resource/content/2/_LO%20QSW1%20UND1%20Introducao%20a%20qsw.pdf

https://aprender3.unb.br/pluginfile.php/3230265/mod_resource/content/3/LO%20Fatores%20de%20qualidade%20galin2018.pdf

https://aprender3.unb.br/pluginfile.php/3230273/mod_resource/content/0/QSW1%20A03%20Dimensoes%20da%20qualidade%20de%20sw.pdf

## 1. Conceito de qualidade:

**Definição (IEEE):** grau em que o sistema, componente ou processo satisfaz:

- Requisios especificados;
- Necessidades ou expectitativas do cliente/usuário;

**Autores clássicos:**

- Crosby (1979): Qualidade é conformidade com requisitos.
- Juran (1988): Qualidade é ausência de deficiências.
- Pressman: Conformidade a requisitos funcionais e não-funcionais, padrões e boas práticas.
- Galin (2004): Inclui requisitos, padrões de contrato e boas práticas implícitas.

---

## 2. Princípios básicos da qualidades:

- Qualidade deve ser pensada **desde o início**.
- **Lucros com qualidade** podem demorar, mas aparecem.
- **Cliente em primeiro lugar** (não quem desenvolve).
- Decisões com base em **fatos e dados**.
- Gestão participativa: qualidade envolve todos.
- Todos os artefatos do desenvolvimento podem ser avaliados.

---

## 3. Visões da Qualidade de Software:
São as diferentes formas de interpretar o que significa qualidade no contexto da Engenharia de Software. São elas:

**Transcendental:**

- Qualidade vista como algo subjetivo ou ideal;
- Algo difícil de definir, mas reconhecível quando se vê. Um achismo.
- Exemplo: softwate elegante ou bonito;

**Baseada no Usuário:**

- Qualidade é medida pelo quanto o software saisfaz o usuário final;
- Grau em que o produto atende às expectativas do usuário;
- Exemplo: usabilidade (interface simples, intuitiva), um sistema pode ser tecnicamente impecável, mas se não for intuitivo, o usuário não considera de qualidade.;

**Baseada no Produto:**

- Qualidade depende das características técnicas do software;
- Avalia de forma objetiva:complexidade do código, manutenibilidade, desempenho; 
- Qualidade interna, resulta em qualidade externa (relação causal);
- Exemplo: código bem estruturado gera menso falhas e aumenta a qualidade percebida para o usuário.

**Baseada na Manufatura (processo):**

- Qualidade do processo de desenvolvimento influencia o produto;
- Exemplo: seguir boas práticas ágeis e CMMI melhora o resultado;

**Baseada em valor:**

- Relação qualidade x custo;
- Considera o ponto de vista do cliente: até que ponto vale a pena investir em mais confiabilidade, desempenho ou suporte?
- Exemplo: quanto o cliente está disposto a pagar por mais confiabilidade, em alguns casos, não compensa gastar mais para atingir “perfeição” se o cliente aceita uma versão “boa o suficiente”.

---

## 4. Qualidade no Ciclo de Vida:

**Qualidade interna:** propriedades internas de software (código, arquitetura);

**Qualidade externa:** como o software se comporta quando executado;

**Qualidade em uso:** percepção do usuário (eficácia, eficiência, satisfação);

São sempre avaliadas por validação e verificação.

---

## 5. Dimensões da Qualidade

### 5.1 Modelo McCall:

Modelo que define a qualidade de software através de três grandes perspectivas a várias dimensões específicas. São elas:

**5.1.1 Fatores de Operação do Produto:**
Foca em como o software funciona durante o uso:

- Correção: o software realiza corretamentos os requisitos que deveria executar.
- Confiabilidade: o software é confiável, funciona sem falhar durante a operação.
- Eficiência: o software é eficiente, uso adequado e otimizado dos recursos (CPU, memória etc.)
- Integridade: o software é seguro.
- Usabilidade: o software tem usabilidade de fácil uso pelo usuario;

**5.1.2 Fatores de Revisão do Produto:**
Foca em mudanças e manutenção do software. 

- Manutenibilidade: é fácil de localizar e corrigir defeitos;
- Flexibilidade: é fácil de adaptar ou modificar o software;
- Testabilidade: é fácil de testar o software;

**5.1.3 Transição do produto:**
Foca na capacidade do software de se adaptar a novos ambientes.

- Portabilidade: é facil de transferir o software par aoutro ambiente;
- Reusabilidade: é possivel usar partes do software em outros sistemas;
- Interoperabilidade: é possivel se comunicar/trabalhar com outros sistemas;

---

### 5.2 FURPS:
Define a qualidade 5 características principais:

- **Functionality (Funcionalidade):** funcionalidades, segurança, interoperabilidade.

- **Usability (Usabilidade):** interface, consistência, facilidade de uso, documentação.

- **Reliability (Confiabilidade):** disponibilidade, tolerância a falhas, precisão.

- **Performance (Desempenho):** tempo de resposta, eficiência, consumo de recursos.

- **Supportability (Suportabilidade):** manutenibilidade, testabilidade, adaptabilidade, extensibilidade.

---

### 5.4 Modelo ISO/IEC 25010
Define a qualidade em 8 características principais:

- **Functional suitability:** Adequação, o software atende às funções e necessidades especificadas.

- **Performance efficiency:** Eficiência, uso adequado e otimizado de recursos (tempo de resposta, processamento, memória).

- **Compatibility:** Compatibilidade, capacidade de coexistir e interagir com outros sistemas.

- **Usability:** Usabilidade, facilidade de aprendizado, operação e satisfação do usuário.

- **Reliabilit:** Confiabilidade, probabilidade de o software funcionar corretamente sem falhas.

- **Security:** Segurança, proteção contra acessos não autorizados e vulnerabilidades.

- **Maintainability:** Manutenibilidade, facilidade de modificar, corrigir ou adaptar o software.

- **Portabilit:** Portabilidade, facilidade de transferir ou adaptar o software para outros ambientes/plataformas.

### 5.3 Modelo SQuaRE (Software Quality Requirements and Evaluation):

O SQuaRE é um framework que reúne várias normas ISO/IEC relacionadas — conjuntos de padrões internacionais — e padroniza a forma de definir, medir e avaliar a qualidade de produtos de software. Ele é formado por: 

**5.3.1 Gestão da Qualidade (ISO/IEC 2500n):**
Define Modelos, termos, definições para uso nas demais seções da SQuare.

**5.3.2 Modelo de Qualidade (ISO/IEC 2501n):**
Apresenta um modelo detalhado da qualidadedo produto e da qualidade em uso incluindo características.

- **Modelo de Qualidade do Produto:** funcionalidade, compatibilidade, usabilidade, segurança, manutennabilidade, portabilidade e confiabilidade.
- **Modelo de Qualidade em Uso:** efetividade, eficiência, satisfação (utilidade, conforto, prazer e confiança).

**5.3.3 Medição da Qualidade (ISO/IEC 2502n):**
Define como medir as características do software.
Ex.: métricas, indicadores, métodos de coleta de dados.

**5.3.4 Requisitos de Qualidade (ISO/IEC  2503n):**
Define como especificar os requisitos de qualidade no projeto.
Ex.: requisitos de desempenho, confiabilidade, usabilidade.

**5.3.5 Avaliação da Qualidade (ISO/IEC 2504n):**
Define como avaliar e validar se o software atende aos requisitos de qualidade.
Ex.: auditorias, testes, revisões de métricas.