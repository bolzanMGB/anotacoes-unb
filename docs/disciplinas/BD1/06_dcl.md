# Data Control Language (DCL)

O DCL é utilizado pelos administradores de banco de dados (DBAs) e desenvolvedores para gerenciar quem pode visualizar ou manipular os dados. Ele é o pilar da segurança no Modelo Relacional.


## 1. Comandos Principais

| Comando | Função | Exemplo de Uso |
| :--- | :--- | :--- |
| **GRANT** | Concede privilégios de acesso a um usuário ou regra (role). | Dar permissão de `SELECT` para um novo dev. |
| **REVOKE** | Remove privilégios previamente concedidos. | Retirar permissão de `DELETE` de um usuário. |

## 2. Tipos de Privilégios Comuns

Você não precisa dar "acesso total" sempre. O DCL permite ser granular:
* `SELECT`: Apenas leitura.
* `INSERT`: Permite adicionar novos dados.
* `UPDATE`: Permite modificar dados existentes.
* `DELETE`: Permite remover registros.
* `ALL PRIVILEGES`: Acesso total ao objeto.

## 3. Exemplos Práticos

```sql
-- 1. Criando um usuário e dando permissão apenas de leitura (Segurança)
CREATE USER 'vendedor_junior' IDENTIFIED BY 'senha123';
GRANT SELECT ON Produto TO 'vendedor_junior';

-- 2. Dando permissão total em uma tabela específica para um gerente
GRANT ALL PRIVILEGES ON Pedidos TO 'gerente_vendas';

-- 3. Removendo a permissão de exclusão caso o cargo mude
REVOKE DELETE ON Produto FROM 'vendedor_junior';
```