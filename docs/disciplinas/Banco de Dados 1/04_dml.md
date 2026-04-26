# Data Manipulation Language (DML)

## 1. INSERT

Adiciona novos registros/objetos (tuplas) em uma tabela. Para isso, a ordem dos valores deve bater com as colunas declaradas

**Exemplo:**

```sql
-- Inserindo um registro 
INSERT INTO Produto (id_produto, nome, preco, em_estoque) 
VALUES (1, 'Bota Chelsea Wyatt', 1200.00, true);

-- Inserindo múltiplos registros de uma vez (Bulk Insert) 
INSERT INTO Produto (id_produto, nome, preco, em_estoque) 
VALUES 
    (2, 'Jaqueta Detroit J97', 850.00, true),
    (3, 'Jaqueta Detroit J01', 900.00, false);
```

## 2. UPDATE

Modifica os dados de um ou mais registros que já existem na tabela. Sempre é necessário a cláusula WHERE em produção, a menos que a regra de negócio exija alterar o banco inteiro de uma vez.

**Exemplo:**

```sql
-- Atualizando o preço e o status de um produto específico
UPDATE Produto 
SET preco = 1350.00, em_estoque = false 
WHERE id_produto = 1;
```

## 3. DELETE

Remove um ou mais registros específicos de uma tabela a partir de um condição da cláusula WHERE, ao contrário do TRUNCATE (que é DDL),que limpa a tabela inteira de forma estrutural e não aceita WHERE.

```sql
-- Removendo um produto específico do catálogo
DELETE FROM Produto 
WHERE id_produto = 3;
```