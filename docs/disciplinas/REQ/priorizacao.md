# Priorização de Requisitos

---

## 1. O que é

A priorização de requisitos é o processo de **definir a ordem de importância** dos requisitos identificados, levando em conta o valor para o negócio, a urgência, os riscos, as restrições técnicas e os interesses dos stakeholders.

O objetivo é ajudar na **tomada de decisão** sobre quais requisitos devem ser implementados primeiro, quais podem ser adiados e quais podem ser descartados.

---

## 2. Objetivos principais

* Garantir que os requisitos mais críticos sejam atendidos primeiro.
* Ajudar na gestão de tempo, custo e esforço do projeto.
* Balancear as necessidades dos stakeholders com as restrições do sistema.
* Evitar conflitos e alinhar expectativas sobre entregas.

---

## 3. Como funciona

A priorização ocorre depois que os requisitos já foram **elicitados e documentados**. Normalmente é feita de forma **colaborativa com os stakeholders**, usando critérios como:

* Valor de negócio;
* Frequência de uso;
* Impacto no usuário;
* Custo/esforço de implementação;
* Riscos e dependências.

---

## 4. Técnicas Comuns de Priorização

**4.1 MoSCoW**

* Classifica requisitos em quatro categorias:

  * **Must Have**: indispensáveis.
  * **Should Have**: importantes, mas não críticos.
  * **Could Have**: desejáveis, mas não necessários.
  * **Won’t Have (for now)**: fora do escopo atual.
* Técnica simples e muito usada em metodologias ágeis.

---

**4.2 \$100 (ou 100 Points Method)**

* Cada stakeholder recebe 100 pontos (ou “dinheiros fictícios”).
* Eles distribuem os pontos entre os requisitos conforme a importância.
* O resultado mostra a prioridade relativa segundo a percepção dos stakeholders.

---

**4.3 First Things First (FTF)**

* Cada requisito é avaliado em dois eixos: **Valor** e **Custo**.
* Normalmente se usa uma fórmula para calcular a prioridade, como:

  $$
  \text{Prioridade} = \frac{Valor}{Custo}
  $$
* Requisitos com maior relação valor/custo são priorizados.

---

**4.4 Three-Level Scale**

* Classificação simples em três níveis:

  * **Alta prioridade**
  * **Média prioridade**
  * **Baixa prioridade**
* Fácil de aplicar em projetos menores ou no início da análise.

---

**4.5 Ranking por pares (Pairwise Comparison / Analytic Hierarchy Process - AHP)**

* Requisitos são comparados **dois a dois**.
* Stakeholders decidem qual dos dois é mais importante.
* O processo gera um ranking global de prioridade.
* A versão mais sofisticada é o **AHP**, que usa matriz de decisão com pesos.

---

**4.6 Kano Model**

* Classifica requisitos segundo a **satisfação do usuário**:

  * **Básicos**: esperados, ausência causa insatisfação.
  * **Desempenho**: aumentam a satisfação proporcionalmente.
  * **Encantadores**: surpreendem positivamente, mas ausência não gera insatisfação.

---

**4.7 WSJF (Weighted Shortest Job First)** *(muito usado em SAFe/Agile)*

* Calcula prioridade com base em:

  $$
  WSJF = \frac{\text{Valor do Negócio + Urgência + Redução de Risco}}{\text{Tamanho ou Esforço}}
  $$
* Foca em maximizar valor entregue no menor tempo possível.

