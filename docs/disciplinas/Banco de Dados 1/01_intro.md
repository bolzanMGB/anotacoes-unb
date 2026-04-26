# Introdução a Banco de Dados

## 1. Níveis de Abstração 

### 1.1 Nível Conceitual

É o nível que descreve o que os dados representam, sem se preocupar com tecnologia.

#### 1.1.1 Modelo Entidade-Relacionamento (MER)

É um modelo abstrato/teórico que define as regras de um negócio. Ele é formado por Entidades, Atributos e Relacionamentos.


#### 1.1.2 Modelo Entidade-Relacionamento Estendido (MERX)

É uma evolução do MER onde é adicionado os conceitos de orientação a objetos: Especialização,Generalização  e Agregação.


#### 1.1.3 Diagrama Entidade-Relacionamento (DER)

É a representação gráfica e visual do MER em um contexto específico. Enquanto o MER define os conceitos e regras, o DER é a ferramenta utilizada para documentar e comunicar essa estrutura. Nele é é usado símbolos gráficos, como Retângulos (Entidades), Elipses (Atributos) e Losangos (Relacionamentos), para representar um negócio.


## 2. Nível Lógico

Aqui o "desenho" do MER é traduzido para uma estrutura que o computador entende, mas ainda sem código.

### 2.1 Modelo Relacional (MRel)

É o modelo teórico que representa os dados em estrutras  tabelas/relações. Ele traduz o modelo conceitual (DER) para uma visão lógica, onde:

- Tabelas: Correspondem às Entidades do DER.

- Colunas: Definem os atributos da entidade.

- Linhas/Tuplas: Representam os Registros ou instâncias específicas (os dados em si), e não a entidade de forma genérica.

### 2.2 Modelo Lógico 

É a aplicação prática do Modelo Relacional para um problema específico.

## 3. Linguagens e Manipulação

### 3.1 Data Definition Language (DDL)

Comandos para criar a estrutura/esquema do banco, sendo os principais: CREATE, ALTER, DROP, TRUNCATE.

### 3.2 Data Manipulation Language (DML)

Comandos para mexer nos dados dentro das tabelas, sendo os principais: SELECT, INSERT, UPDATE, DELETE.

### 3.3 Data Query Language (DQL)

Comandos para consultar dados existentes nas tabelas, retornando as tuplas que baterem com a busca.

### 3.4 Data Control Language (DCL)

Comandos para controle o acesso e permissões dentro do banco, sendo os principais: GRANT e REVOKE.


## 4. Tipos de Integridade

**Integridade Referencial:** Se aplica em FKs e garante que relacionamento entre tabelas sejam válidos (sem órfãos).

**Integridade Entidade:** Se aplica em PKs e garante que cada registro seja único e identificável.

**Integridade Domínio:** Se aplica em tipos e constraints e garante que os valores respeitem o tipo e 
limites da coluna.

**Integridade Vazio:** Se aplica em Not Null e garante que campos essenciais sejam preenchidos.

## 5. Normalização
forma 1 forma 2 forma 3