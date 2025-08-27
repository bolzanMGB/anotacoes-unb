# Modelo Entidade-Relacionamento (MER) 

## 1. Construtores Sintáticos

O MER é formado por:

* **Conjunto de Entidades (CE)**;
* **Conjunto de Relacionamentos (CR)**;
* **Atributos** (podem ser de entidades ou de relacionamentos).

O esquema conceitual criado usando-se o MER é chamado de **Diagrama Entidade relacionamento (DER)**
---

## 2. Conjunto de Entidades (CE)

**Entidade**: objeto do mundo real que pode ser distinguido dos demais (ex.: Pessoa, Carro, Produto).

**Conjunto de Entidades (CE)**: coleção de entidades semelhantes (mesma estrutura e significado).

**Notação**: retângulo.

---

## 3. Conjunto de Relacionamentos (CR)

**Relacionamento**: associação entre entidades.

**Conjunto de Relacionamentos (CR)**: todas as ocorrências de um mesmo tipo de associação.

**Notação**: losango.

### 3.1 Papéis

Cada entidade participa do relacionamento com um **papel** (ex.: Médico “atende” Paciente).

### 3.2 Cardinalidade

Define quantas vezes uma entidade pode participar de um relacionamento:

* 1:1 → um para um
* 1\:N → um para muitos
* N\:M → muitos para muitos

### 3.3 Grau

Número de conjuntos de entidades em um relacionamento:

* **Binário**: envolve 2 entidades;
* **Ternário**: envolve 3 entidades;
* **N-ário**: envolve N entidades.

---

## 4. Atributos

### 4.1 Atributos de Entidade

Descrevem propriedades das entidades.
* **Notação**: elipses ligadas ao retângulo da entidade.

### 4.2 Atributos de Relacionamento

Descrevem propriedades do relacionamento (ex.: Data de um relacionamento “Atende”).
* Nem todo relacionamento precisa ter atributos.

### 4.3 Chaves

* **Chave Simples**: um atributo identifica unicamente uma entidade (ex.: CPF).
* **Chave Composta**: conjunto de atributos necessário para identificar (ex.: Matrícula + Código Disciplina).

### 4.4 Tipos de Atributos

* **Simples**: indivisível (ex.: CPF).

* **Composto**: pode ser decomposto (ex.: Endereço → Rua, Cidade, CEP).

* **Monovalorado**: só um valor por entidade (ex.: Data de Nascimento).

* **Multivalorado**: vários valores possíveis (ex.: Telefones).

* **Armazenado**: gravado no banco (ex.: Data de Nascimento).

* **Derivado**: calculado a partir de outros (ex.: Idade a partir da data de nascimento).

---

## 5. Restrições de Participação

### 5.1 Participação Total (Dependência Existencial)

Toda entidade de A deve obrigatoriamente estar associada a uma entidade de B.

* Notação: **linha dupla**.

### 5.2 Participação Parcial

Nem toda entidade participa do relacionamento.

* Notação: **linha simples**.

### 5.3 Entidade Fraca

* Não possui chave primária própria.
* Depende de uma **entidade forte (owner)** para identificação.
* Usa **chave parcial** (traço pontilhado).
* Cardinalidade sempre **1\:N ou 1:1 (nunca N\:M)**.
* Notação:

    * Retângulo duplo para entidade fraca;
    * Losango duplo para relacionamento identificador;
    * Linha dupla indica participação obrigatória no relacionamento.


---

## 6. Agregação

### 6.1 Conceito

Permite tratar um relacionamento como uma **entidade**.

### 6.2 Exemplos

* Agregação de Atributos: Pessoa composta por Nome, CPF, Data Nascimento.
* Agregação de CE + CR: quando um relacionamento precisa ser representado como entidade (ex.: Consulta formada por Médico, Paciente e Data).

---

## 7. Generalização e Especialização

### 7.1 Generalização

Cria um **supertipo** a partir de características comuns de várias 
entidades.

* Exemplo: Pessoa → (Aluno, Professor, Funcionário).
* **Herança**: subtipos herdam atributos e relacionamentos do supertipo.
* **Relacionamento “is-a”**: Aluno é uma Pessoa.

### 7.2 Especialização

* Processo inverso: divide uma entidade genérica em subtipos.
* Exemplo: Pessoa → Aluno, Professor, Funcionário.

### 7.3 Tipos de Especialização

* **Múltiplos níveis**: mais de dois níveis de especialização.
* **Herança múltipla**: um subtipo tem mais de um supertipo (ex.: Anfíbio → Aquático + Terrestre).

### 7.4 Restrições de Generalização

* **Disjunção** (D):

    * **Exclusiva (E)** → cada entidade pertence a apenas um subtipo.
    * **Sobreposição (S)**  → uma entidade pode estar em vários subtipos.

* **Totalidade**:

    * **Total (T)** → toda entidade do supertipo deve pertencer a algum subtipo.
    * **Parcial (P)** → algumas entidades do supertipo não precisam estar em subtipos.

### 7.5 Combinações Possíveis

* (P,E) → Parcial + Exclusiva.
* (P,S) → Parcial + Sobreposta.
* (T,E) → Total + Exclusiva.
* (T,S) → Total + Sobreposta.

## 8. Resumo Notações