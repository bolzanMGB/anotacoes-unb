# Revisão de Lógica

## 1. Proposições e Conectivos

| Conectivo | Nome | Símbolo | Tradução | Regra de Ouro (Para ser Verdade) |
| :--- | :--- | :---: | :--- | :--- |
| **Conjunção** | E | $\land$ | "p e q" | Só é **V** se ambas forem verdadeiras. |
| **Disjunção** | OU | $\lor$ | "p ou q" | É **V** se pelo menos uma for verdadeira. |
| **Condicional** | Se... então | $\to$ | "Se p, então q" | Só é **F** se a primeira for **V** e a segunda for **F** (Vera Fischer). |
| **Bicondicional** | Se e somente se | $\leftrightarrow$ | "p sse q" | É **V** se ambas forem iguais (**V** e **V** ou **F** e **F**). |
| **Disjunção Exclusiva** | Ou... ou | $\underline{\lor}$ | "Ou p ou q" | É **V** se forem diferentes (uma **V** e outra **F**). |


## 2. Negações

### 2.1 Negação da Conjunção
Troca o conectivo por "OU" e nega ambas as proposições.
> ~(p ∧ q) ≡ (~p ∨ ~q)

**Exemplo:**
"Vou à escola e não aprendo" ≡ "Não vou à escola ou aprendo."


### 2.2 Negação da Disjunção
Troca o conectivo por "E" e nega ambas as proposições.

> ~(p ∨ q) ≡ (~p ∧ ~q)

**Exemplo:**
"Corro ou caminho" ≡ Não corro e não caminho.


### 2.3 Negação da Condicional

A regra é o **MANÉ**: troca o "Se" por "E", **MA**ntém a primeira **E** **NE**ga a segunda. 

> ~(p → q) ≡ (p ∧ ~q)

**Exemplo:**
"Se chover, eu levo o guarda-chuva" ≡ Chove e eu não levo o guarda-chuva.


### 2.4 Negação da Disjunção Exclusiva

Troca o "Ou... ou" pelo conectivo **"Se e somente se"** (Bicondicional). Mantém as frases como estão.
> ~(p <u>∨</u> q) ≡ (p ↔ q)

**Exemplo:**
"Ou estudo ou durmo" ≡ Estudo se e somente se durmo.

---

### 2.5 Negação do Bicondicional

Troca o "Se e somente se" pelo conectivo **"Ou... ou"** (Disjunção Exclusiva). Mantém as frases como estão.
> ~(p ↔ q) ≡ (p <u>∨</u> q)

**Exemplo:**
"Sou feliz se e somente se você está aqui" ≡ Ou sou feliz ou você está aqui.


## 3. Quantificadores

Os principais quantificadores são: Todo, ALgum e Nenhum.

| Proposição Original | Negação (O que derruba a frase) | Regra Mental  |
| :--- | :--- | :--- |
| **TODO** A é B | **ALGUM** A **NÃO** é B | **PEA (Pelo menos um, Existe, Algum) + NÃO**: Basta um contraexemplo para a regra geral cair. |
| **NENHUM** A é B | **ALGUM** A é B | Se eu digo que ninguém veio, você prova que menti se mostrar **pelo menos uma** pessoa que veio. |
| **ALGUM** A é B | **NENHUM** A é B | A negação do "existe ao menos um" é dizer que não existe **nenhum**. |
| **ALGUM** A **NÃO** é B | **TODO** A é B | A negação da "exceção" (um que não é) é a "regra geral" (todos são). |



## 4. Teoria dos Conjuntos
| Símbolo | Nome | Exemplo | Descrição |
| :---: | :--- | :--- | :--- |
| $\in$ | Pertence | $x \in A$ | Um **elemento** está dentro do conjunto. |
| $\notin$ | Não pertence | $y \notin A$ | O elemento está fora do conjunto. |
| $\subset$ | Está contido | $A \subset B$ | O conjunto A está dentro do conjunto B. |
| $\supset$ | Contém | $B \supset A$ | O conjunto B engloba o conjunto A. |
| $\cup$ | União | $A \cup B$ | Elementos que estão em A **OU** em B. |
| $\cap$ | Intersecção | $A \cap B$ | Elementos que estão em A **E** em B. |
| $\emptyset$ | Vazio | $A = \emptyset$ | Conjunto sem nenhum elemento. |


## 5. Funções

função composta

função inversa

algebra de função

função sobrejotora, injetora, bijetora

dominio, contradominio, imagem