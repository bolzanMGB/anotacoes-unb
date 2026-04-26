# Lógica Proposional Booleana


## 1. Conceitos Elementares

### 1.1 Termos Primitivos:
- Verdadeiro;
- Falso;
- Proposição

### 1.2 Axiomas:
- Princípio do 3° Excluído: Uma proposição é verdadeira ou é falsa.
- Princípio da Não-Contradição: Uma proposição não pode ser , simultaneamente, verdadeira e falsa.

### 1.3 Proposições:
- A duração de um dia é de 24 horas.
- A metade de dois mais dois é igual a três.

### 1.4 Não-Proposições:
- Cuidado! Curva acentuada à esquerda!
- Onde fica a agência bancária mais próxima?

### 1.5  Operadores Lógicos

| Conectivo  | Simbolo  | Significado | 
| ----------- | ----------- | ----------- | 
| Conjunção |  p ∧ q | V somente quando ambas p e q sao V |
| Disjunção |  p ∨ q | V quando pelo menos p ou q é V |
| Disjunção Exclusiva|  p $\veebar$ q | F quando ambas p e q tem mesmo valor lógico |
| Condicional |  p $\rightarrow$ q | F somente quando p é V e q é F |
| Bicondicional |  p $\leftrightarrow$ q | F somente quando p e q tem valores lógicos distintos |
| Negação |  $\neg$p | V quando p é F e F quando p é V |


### 1.6 Tabela Verdade 
Exemplo P = p ∧ q → r

| $p$ | $q$ | $r$ | $p \land q$ | $(p \land q) \rightarrow r$ |
| :---: | :---: | :---: | :---: | :---: |
| V | V | V | V | **V** |
| V | V | F | V | **F** |
| V | F | V | F | **V** |
| V | F | F | F | **V** |
| F | V | V | F | **V** |
| F | V | F | F | **V** |
| F | F | V | F | **V** |
| F | F | F | F | **V** |



### 1.7 Sentença Aberta 

Uma sentença aberta S(x) em x é uma expressão na qual o símbolo x ocorre uma
ou mais vezes e que, caso todas as ocorrências de x sejam substituídas por um
mesmo valor v, S(v) se torna uma proposição.

pode ser falso ou verdadeiro
E(x) = x > 2 É
E(x) = X + 1 Não é

### 1.8 Quantificadores                                                         

Quantificador Existencial: Seja S(x) uma sentença aberta. O quantificador existencial ∃ é utilizado na construção ∃x.S(x), a qual significa que existe pelo menos um x tal que S(x) é verdadeira.

Quantificador Universal: Seja S(x) uma sentença aberta. O quantificador universal ∀ é utilizado na construção ∀x.S(x), a qual significa que, para todos os valores de x, S(x) é verdadeira.

consulta: unb(A)
utilizar ; para continuar ou . para parar
na ordem em que foram declarados.

