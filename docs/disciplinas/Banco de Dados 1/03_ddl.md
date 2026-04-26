# Data Definition Language (DDL)

## 1. Definição inicial de Tabelas 

O comando padrão para definir tabelas segue a seguinte sintaxe:

```sql
CREATE TABLE NomeAtributo{
    atributo_1 TIPO,  
    atributo_2 TIPO, 
}
```

### 1.1 Principais Tipos de dados

| Categoria | Tipo | Descrição | Exemplo de Uso |
| :--- | :--- | :--- | :--- |
| **Numéricos** | `INT` ou `INTEGER` | Números inteiros (positivos ou negativos). | IDs, quantidades, idade. |
| | `BIGINT` | Inteiros de 8 bytes (para números muito grandes). | IDs em sistemas globais, populações. |
| | `DECIMAL(p,s)` | Números decimais exatos com precisão fixa. | Preços, saldos bancários. |
| | `FLOAT` / `REAL` | Números de ponto flutuante (precisão aproximada). | Coordenadas GPS, cálculos científicos. |
| | `SERIAL` | Inteiro autoincrementável (comum no Postgres). | Chaves Primárias (PK). |
| **Texto** | `VARCHAR(n)` | String de tamanho variável (até o limite *n*). | Nomes, emails, endereços. |
| | `CHAR(n)` | String de tamanho fixo (preenche com espaços). | Siglas de Estados (UF), códigos fixos. |
| | `TEXT` | String de tamanho ilimitado (ou muito grande). | Descrições longas, posts de blog. |
| **Data/Hora** | `DATE` | Apenas data (AAAA-MM-DD). | Data de nascimento. |
| | `TIME` | Apenas hora (HH:MM:SS). | Horário de abertura. |
| | `TIMESTAMP` | Data e hora combinadas. | Registro de criação (created_at). |
| | `INTERVAL` | Representa um período de tempo. | "30 days", "1 hour". |
| **Outros** | `BOOLEAN` | Valores lógicos (True/False ou 1/0). | `is_active`, `tem_estoque`. |
| | `JSON` / `JSONB` | Armazena dados no formato JSON. | Configurações, metadados flexíveis. |
| | `UUID` | Identificador Único Universal (36 caracteres). | PKs que não seguem sequência lógica. |
| | `BYTEA` / `BLOB` | Dados binários (arquivos, imagens). | Fotos de perfil (raro em produção). |


### 1.2 Constraints de Integridade SQL

As constraints são regras aplicadas às colunas para garantir a validade e a consistência dos dados.

| Constraint | Descrição | Exemplo de Uso |
| :--- | :--- | :--- |
| **NOT NULL** | Garante que uma coluna não pode ter valores nulos. O preenchimento é obrigatório. | Nomes, CPFs, Senhas. |
| **UNIQUE** | Garante que todos os valores em uma coluna sejam distintos (não permite duplicatas). | E-mails, Nomes de Usuário. |
| **PRIMARY KEY** | Uma combinação de `NOT NULL` e `UNIQUE`. Identifica unicamente cada registro na tabela. | ID, Código do Produto. |
| **FOREIGN KEY** | Garante a integridade referencial. Liga uma coluna a uma Chave Primária de outra tabela. | `id_categoria` na tabela `Produtos`. |
| **CHECK** | Garante que os valores em uma coluna satisfaçam uma condição específica (expressão lógica). | `preco > 0` ou `idade >= 18`. |
| **DEFAULT** | Define um valor padrão para a coluna caso nenhum valor seja fornecido no INSERT. | `data_criacao` como `CURRENT_TIMESTAMP`. |

### 1.3 Ações Referenciais (Foreign Key Behaviors)
As ações referenciais definem o comportamento automático do banco de dados em operações de `UPDATE` ou `DELETE` na tabela pai (referenciada).

| Ação | Descrição | Comportamento Prático |
| :--- | :--- | :--- |
| **CASCADE** | Propaga a alteração/exclusão para os registros filhos. | Se deletar o Aluno, todas as Matrículas dele somem automaticamente. |
| **SET NULL** | Define a coluna da Chave Estrangeira nos filhos como `NULL`. | Se o Curso for deletado, o campo `id_curso` no Aluno fica vazio. |
| **SET DEFAULT** | Define a FK nos filhos para o valor padrão (`DEFAULT`) da coluna. | Se a Disciplina sumir, a Matrícula aponta para uma disciplina "Padrão". |
| **RESTRICT** | Impede a operação no pai se houver qualquer registro filho ligado. | O banco dá erro e não deixa deletar o Curso enquanto houver alunos nele. |
| **NO ACTION** | Semelhante ao RESTRICT, mas a verificação é feita no fim da transação. | Verifica a integridade apenas após todas as alterações do comando. |
---

### 1.4 Casos Específicos

#### 1.4.1 Relacionamento 1:N

**Regra:** A PK do lado "1" vira uma FK do lado "N".

**Exemplo:** Um curso tem VÁRIOS Alunos. Um Aluno possui UM curso.


```sql

CREATE TABLE Curso(
    id_curso INT PRIMARY KEY
);

CREATE TABLE Aluno(
    id_aluno INT PRIMARY KEY,
    id_curso INT,
    FOREIGN KEY (id_curso) REFERENCES Curso(id_curso)
);

```

#### 1.4.2 Relacionamento N:M

**Regra:** Você obrigatoriamente cria uma nova tabela (tabela associativa). Ela terá as PKs das duas tabelas originais como FKs.

**Exemplo:** Uma disciplina é cursada por VÁRIOS alunos. Um aluno cursa VÁRIAS disciplinas.


```sql

CREATE TABLE Disciplina(
    id_disciplina INT PRIMARY KEY
);

CREATE TABLE Aluno(
    id_aluno INT PRIMARY KEY,
);

CREATE TABLE Matricula(
    id_aluno INT,
    id_disciplina INT,
    PRIMARY KEY (id_aluno, id_disciplina),
    FOREIGN KEY (id_aluno) REFERENCES Aluno(id_aluno),
    FOREIGN KEY (id_disciplina) REFERENCES Disciplina(id_disciplina)
);

```


### 1.4.4 Entidade Fraca

**Regra:** A PK da entidade fraca deve ser composta: (PK da Forte + Atributo Discriminador). Além disso, usa-se o ON DELETE CASCADE para que, se o "pai" sumir, o "filho" também suma.

**Exemplo:** Um funcionário possui dependentes. Os dependentes só existem se os funcionários existirem.


```sql

CREATE TABLE Funcionario (
    id_funcionario INT PRIMARY KEY
);

CREATE TABLE DEPENDENTE (
    id_funcionario INT,
    nome_dependente VARCHAR(100),
    PRIMARY KEY (id_funcionario, nome_dependente),
    FOREIGN KEY (id_funcionario) REFERENCES Funcionario(id_funcionario) ON DELETE CASCADE
);

```

### 1.4.5 Herança (Especialização e Generalização)

**Regras:** Existem duas formas principais de fazer isso no DDL:

- Tabela Única (Single Table): Uma tabela com todos os campos e uma coluna tipo (gera muitos campos nulos).

- Tabelas Separadas (Class Table ): Uma tabela para a classe "pai" e tabelas específicas para os "filhos" que referenciam os atributos do pai por meio de FK.

**Exemplo:** Uma pessoa pode ser Aluno ou Professor.


```sql
-- Single Table

CREATE TABLE Pessoa(
    id_pessoa INT PRIMARY KEY,
    tipo_pessoa VARCHAR(10) NOT NULL,

    matricula VARCHAR(20),
    salario DECIMAL (10,2)

    CONSTRAINT chk_tipo CHECK (tipo_pessoa in ('ALUNO', 'PROFESSOR'))
);

CREATE TABLE Aluno(
    matricula_aluno INT PRIMARY KEY
);

CREATE TABLE Professor(
    salario_professor INT PRIMARY KEY
);
```


```sql
-- Class Table

-- Tabela "Pai" (Superclasse)
CREATE TABLE Pessoa(
    id_pessoa INT PRIMARY KEY
);

-- Tabela "Filha" Aluno (Subclasse)
CREATE TABLE Aluno (
    id_pessoa INT PRIMARY KEY,
    matricula VARCHAR(20) NOT NULL,
    FOREIGN KEY (id_pessoa) REFERENCES Pessoa(id_pessoa) ON DELETE CASCADE
)

-- Tabela "Filha" Professor (Subclasse)
CREATE TABLE Professor (
    id_pessoa INT PRIMARY KEY, 
    salario DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (id_pessoa) REFERENCES Pessoa(id_pessoa) ON DELETE CASCADE
);
```

### 1.4.6 Agregação

**Regra:** No MER, a agregação é quando um relacionamento é tratado como uma entidade para se relacionar com outra coisa. No DDL, você trata a tabela associativa (do relacionamento agregado) como uma tabela normal e cria uma FK apontando para ela.

Exemplo: Uma "Entrevista" que acontece entre um "Candidato" e uma "Vaga".


```sql
CREATE TABLE Candidato(
    id_candidato INT PRIMARY KEY
);

CREATE TABLE Vaga(
    id_vaga INT PRIMARY KEY
);

CREATE TABLE Entrevista(
    id_entrevista INT PRIMARY KEY,
    id_candidato INT,
    id_vaga INT,

    FOREIGN KEY (id_candidato) REFERENCES Candidato (id_candidato),
    FOREIGN KEY (id_vaga) REFERENCES Vaga (id_vaga)
);
```

## 2. Manutenção e Evolução de Tabelas

O DDL também gerencia as mudanças na estrutura após ela já ter sido criada.

### 2.1 ALTER TABLE
O comando `ALTER` é crítico porque bancos de dados em produção raramente podem ser apagados e recriados. Ele é usado para:

**Adicionar Colunas:**
    ```sql
    ALTER TABLE Aluno ADD COLUMN data_nascimento DATE NOT NULL DEFAULT '2000-01-01';
    ```

**Modificar Tipos de Dados:**
    ```sql
    ALTER TABLE Produto ALTER COLUMN preco TYPE DECIMAL(10,2) USING (preco::numeric);
    ```

**Gerenciar Constraints (Regras):**
    ```sql
    -- Adicionando uma Unique Constraint tardia
    ALTER TABLE Aluno ADD CONSTRAINT unique_email UNIQUE (email);
    
    -- Removendo uma regra
    ALTER TABLE Aluno DROP CONSTRAINT unique_email;
    ```
### 2.2. DROP 

O `DROP` apaga a estrutura, os dados, os índices e os gatilhos associados. É irreversível.

**DROP TABLE:** Exclui a tabela.

**DROP INDEX:** Remove um índice de performance.

**Cláusula CASCADE:** Se você tentar dar um DROP em uma tabela que é "pai" de outra, o banco impedirá. Use `CASCADE` para apagar a tabela e todas as referências (FKs) que apontam para ela.

```sql
DROP TABLE Cursos CASCADE;
```

### 2.3. TRUNCATE 
Muitos confundem com o `DELETE`, mas o `TRUNCATE` é um comando DDL, não DML.

**Diferença Fundamental:** O `DELETE` apaga linha por linha e gera logs de recuperação para cada uma (lento). O `TRUNCATE` desaloca o espaço em disco da tabela de uma vez (instantâneo).

**Reset de Contadores:** O `TRUNCATE` reinicia contadores de colunas `SERIAL` ou `AUTO_INCREMENT`.

```sql
-- Esvazia a tabela de logs do sistema de forma rápida
TRUNCATE TABLE Logs_Acesso;
```
