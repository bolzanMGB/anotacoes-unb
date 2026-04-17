
# Triggers

## 1. Definição
São execuções disparadas pelo banco em função de eventos que ocorrem em:

- Uma tabela.
- Em operações DML (UPDATE, INSERT, DELETE).
- Em um momento (BEFORE ou AFTER).

## 2. Linguagens Procedurais
São linguagens que definem o que será executado pelo triggers, sendo a mais comum o PL/SQL. Elas auxiliam na:

- Definição de Regras de Negócio.
- Especificação de restrições;
- Calculo de atributos derivados.


## 3. Elementos de um Trigger

**Tabela Desencadeadora:** É a tabela que desencadeou o trigger.

**Instruções de Disparo:** São comandos DML: INSERT, UPDATE e DELETE.

**Timing:** Quando um trigger vai ser adicionado em relação a operação: BEFORE ou AFTER.

**Nível de Execução:**

- Statement-Level (FOR EACH STATEMENT): É executado uma única vez por instrução, independente de quantas linhas foram alteradas.
- Row-Level (FOR EACH ROW): É executado para cada linha afetada pela operação.

**Execute Procedure:** Função que vai desencadear o trigger.

**Identificadores de Correlação:** Variáveis que representam os dados da linha afetada pela operação DML. É utilizado em row level.

## 4. Exemplo:

```sql
--- Deseja-se manter a tabela Turma atualizada de acordo com as remoções ocorridas na tabela Matrícula

CREATE OR REPLACE FUNCTION update_turma() 
RETURNS trigger AS $update_turma$
BEGIN
 UPDATE Turma SET NAlunos = NAlunos - 1 
 WHERE Sigla = old.Sigla AND Letra = old.Letra;
RETURN NULL;
END;
$update_turma$ LANGUAGE plpgsql;

CREATE TRIGGER NroDeAlunos
AFTER DELETE ON Matricula
FOR EACH ROW 
EXECUTE PROCEDURE update_turma();
```

