# Data Query Language (DQL)

A linguagem de consulta é composta essencialmente pelo comando `SELECT`. O objetivo do DQL é buscar, cruzar, filtrar e formatar dados sem alterar o estado original do banco.

## 5.1 Sintaxe de uma Consulta
Embora a gente escreva a query começando pelo `SELECT`, o motor do banco de dados (como o PostgreSQL) processa a consulta em uma ordem diferente. Entender isso ajuda a evitar bugs de lógica. A ordem se da por:

1. `SELECT` (O que retornar)
2. `FROM` (De onde buscar)
3. `WHERE` (Filtros base)
4. `GROUP BY` (Agrupamento)
5. `HAVING` (Filtro pós-agrupamento)
6. `ORDER BY` (Ordenação)
7. `LIMIT / OFFSET` (Paginação)

## 5.1 WHERE
Filtra os dados antes de qualquer agrupamento

**Operadores Relacionais e Lógicos:** `=`, `<`, `>`, `<=`, `>=`, `<>` ou `!=`, `AND`, `OR`, `NOT`.
**IN:** Filtra valores dentro de uma lista específica.

**BETWEEN:** Filtra valores dentro de um intervalo.

**LIKE / ILIKE:** Busca por padrões de texto. Usa-se o "%":
- No início para buscar por palavras que começam com esse padrão.
- No fim para buscar palavras que terminam com esse padrão. 
- No início e no fim para buscar palavras que contenham em qualquer lugar esse padrão.

**Exemplo:** Busca por jaqueta ou botas que custam entre 500 e 1000 reais.

```sql
SELECT id_produto, nome, preco
FROM produto
WHERE (nome LIKE 'jaqueta' OR 'bota')
    AND preco BETWEEN 500.00 AND 1000.00;
```

## 5.2 GROUP BY e HAVING

Utilizado para gerar relatórios e sumarizar dados.

**Funções de Agregação:** COUNT (conta linhas), SUM(soma), AVG(média), MAX(valor máximo) e MIN(valor mínimo).

**GROUP BY:** Agrupa linhas que têm os mesmos valores em colunas específicas.

**HAVING:** É o equivalente ao WHERE, mas aplicado após o agrupamento (só funciona com funções de agregação).

**Exemplo:** Qual é o estoque total por categoria, apenas para categorias com mais de 50 itens?

```sql
SELECT id_categoria, SUM(quantidade_estoque) AS total_itens
FROM Produtos
GROUP BY id_categoria
HAVING SUM(quantidade_estoque) > 50;
```

## 5.3 LIMIT e OFFSET

**LIMIT:** Define a quantidade máxima de registros retornados.

**OFFSET:** Pula uma quantidade específica de registros (usado para trocar de página)

**Exemplo:** Buscando os itens da "Página 2" (assumindo 20 itens por página)

```sql
SELECT id_produto, nome, preco 
FROM Produto 
ORDER BY nome ASC 
LIMIT 20 OFFSET 20;
```


## 5.4 JOINs

Os JOINs são utilizados para consultar dados de duas ou mais tabelas relacionadas através de chaves estrangeiras (FK).

### 5.4.1 JOINs básicos

| Tipo de JOIN | O que faz? | Comportamento Prático |
| :--- | :--- | :--- |
| **INNER JOIN** | Retorna apenas os registros que têm correspondência em **ambas** as tabelas. | É a **interseção**. Se um dado não tem par na outra tabela, ele não aparece no resultado. |
| **LEFT JOIN** | Retorna **todos** os registros da tabela da esquerda (A), e os correspondentes da direita (B). | Se não houver par na direita, as colunas da tabela B virão preenchidas com `NULL`. |
| **RIGHT JOIN** | Retorna **todos** os registros da tabela da direita (B), e os correspondentes da esquerda (A). | O inverso do Left Join. É menos comum, pois geralmente se altera a ordem das tabelas no FROM para usar o Left. |
| **FULL JOIN** | Retorna registros quando há uma correspondência em **qualquer uma** das tabelas. | Traz tudo de ambos os lados. Onde não houver correspondência, preenche com `NULL`. |

imagem 108

**Exemplo:**

```sql
-- 1. INNER JOIN: 
-- Só mostra quem tem par: Aluno com curso e Curso com aluno.
SELECT a.nome AS Aluno, c.nome AS Curso
FROM Aluno a
INNER JOIN Cursos c ON a.id_curso = c.id_curso;

-- 2. LEFT JOIN: 
-- Traz TODOS os alunos da tabela da esquerda. 
-- Se um aluno não tiver curso, o nome do curso virá como NULL.
SELECT a.nome AS Aluno, c.nome AS Curso
FROM Aluno a
LEFT JOIN Cursos c ON a.id_curso = c.id_curso;

-- 3. RIGHT JOIN: 
-- Traz TODOS os cursos da tabela da direita.
-- Útil para ver quais cursos estão vazios (o nome do Aluno virá NULL).
SELECT a.nome AS Aluno, c.nome AS Curso
FROM Aluno a
RIGHT JOIN Cursos c ON a.id_curso = c.id_curso;

-- 4. FULL JOIN:
-- Traz absolutamente tudo de ambos os lados.
-- Mostra alunos sem curso E cursos sem alunos no mesmo resultado.
SELECT a.nome AS Aluno, c.nome AS Curso
FROM Aluno a
FULL OUTER JOIN Cursos c ON a.id_curso = c.id_curso;
```
### 5.4.2 JOINs avançados
Além dos cruzamentos básicos, podemos usar a lógica de `NULL` para transformar um JOIN em um filtro de exclusão.

| Nome Técnico | O que faz? | Lógica SQL |
| :--- | :--- | :--- |
| **Left Exclusive** | Traz apenas os registros da esquerda que **não possuem** par na direita. | `LEFT JOIN` + `WHERE B.id IS NULL` |
| **Right Exclusive** | Traz apenas os registros da direita que **não possuem** par na esquerda. | `RIGHT JOIN` + `WHERE A.id IS NULL` |
| **Full Inclusive** | É o `FULL OUTER JOIN` padrão. Traz tudo de todos. | `FULL OUTER JOIN` |
| **Full Exclusive** | Traz apenas os registros "órfãos" de ambos os lados (sem correspondência). | `FULL JOIN` + `WHERE A.id IS NULL OR B.id IS NULL` |

imagem 107
**Exemplos:**

```sql
-- 1. LEFT EXCLUSIVE: Alunos que NÃO estão em nenhum curso
-- Útil para o marketing do ERP focar em quem ainda não se matriculou.
SELECT a.nome
FROM Aluno a
LEFT JOIN Cursos c ON a.id_curso = c.id_curso
WHERE c.id_curso IS NULL;

-- 2. RIGHT EXCLUSIVE: Cursos que NÃO possuem nenhum aluno
-- Útil para o coordenador da UnB decidir se cancela uma turma.
SELECT c.nome
FROM Aluno a
RIGHT JOIN Cursos c ON a.id_curso = c.id_curso
WHERE a.id_aluno IS NULL;

-- 3. FULL EXCLUSIVE: Registros sem vínculo (erros de sistema ou dados órfãos)
-- Mostra alunos sem curso E cursos vazios ao mesmo tempo.
SELECT a.nome, c.nome
FROM Aluno a
FULL OUTER JOIN Cursos c ON a.id_curso = c.id_curso
WHERE a.id_aluno IS NULL OR c.id_curso IS NULL;
```