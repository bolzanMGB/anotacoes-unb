# Transações

## 1. Definição

É um conjunto de operações DML que são executadas como uma única unidade lógica com o objetivo de garantir integridade, consistência e confiabilidade, mesmo diante de cenários de falhas de sistema e acesso simultâneo. Sua característica principal é:

> Ou tudo é feito, ou nada é feito

Por exemplo, ao transferir R$100 de uma conta A para conta B, isso envolve obrigatoriamente duas operações que devem ser feitas juntas:

- Debitar $100 da conta A.
- Creditar $100 da conta B.

## 2. Tipos de Falhas

| Tipo de Falha | Exemplo Prático | Como o SGBD Resolve |
| :--- | :--- | :--- |
| **Local** | Erro em uma transação (Ex: erro de sintaxe, divisão por zero). | Utiliza o **Registro de Log** para realizar o **Undo** (desfazer) apenas daquela transação. |
| **Global (Soft)** | Queda de energia ou falha no Sistema Operacional (interrupção do buffer). | Utiliza o **Log** e o **Checkpoint** para realizar o **Redo** (refazer transações confirmadas) e **Undo** (desfazer as não confirmadas). |
| **Global (Hard)** | Falha física (Ex: Disco queimado, corrupção de mídia). | **Restaura o Backup** mais recente e aplica o **Log de Transações** (se disponível e íntegro) para recuperar os dados até o momento da falha. |

## 3. Propriedades (ACID)

São as propriedades essenciais que uma transação deve cumprir.

## 4. Controle de Concorrência

**Execução serial:** Transações em sequência, uma após a outra. Mais seguro, mais lento;

**Execução Intercalada:** Transações feitas em paralelo (ao mesmo tempo). Menos seguro, menos lento.

### 4.1 Problemas em Execução Intercalada

**Leitura Inválida (Dirty Read):** Ocorre quando uma transação le dados modificados por outra transação que ainda não foi confirmada. Exemplo:

- T1 escreve um valor X=500, mas ainda não confirmou.
- T2 lê X=500, mas T1 faz ROLLBACK e X volta para 100.
- T2 usou um dado que "não existia".

**Leitura Não-Repetível (Nonrepeatable-Read):** Ocorre quando uma transação relê dados e encontra valores diferentes porque outra transação os modificou entre as leituras. Exemplo:

- T1 lê saldo=100.
- T2 altera saldo=150 e confirma.
- T1 lê novamente e vê saldo=150 (leitura não repetível).

**Leitura Fantasma (Phantom Read):** Quando uma transação le um conjunto de tuplas, mas outra transação inseriu ou removeu parte desse conjunto. Exemplo:

- T1 seleciona alunos com média > 7.
- T2 insere um novo aluno com média 9 e confirma.
- T1 refaz a mesma consulta e vê um novo aluno → leitura fantasma.


## 5. Níveis de Isolamento
São os graus de proteção contra os efeitos colaterais da execução simultânea de transações. Dita quais anomalias são permitidas e quais não são.

### 5.1 Read Committed:

Este nível garante que você só leia dados que já foram confirmados (commited). Diferente do Repeatable Read, o banco não coloca um "cadeado" permanente nas linhas durante a transação toda. Ele tira um "snapshot" rápido a cada novo comando SQL que você executa.

**Comportamento:** Se você ler a Linha A, e outra transação alterá-la e commitar logo em seguida, na sua próxima leitura (dentro da mesma transação) você já verá o valor novo. Ele mostra sempre a versão commitada mais recente no momento do comando.

**Vantagem:** Evita que o banco fique lento, pois não mantém travas ou versões antigas por muito tempo, sendo o nível preferido para sistemas de alta performance.

**Problema:** Sofre de "Leitura Não Repetível". O valor de uma mesma linha pode mudar entre dois SELECTs feitos dentro da mesma transação.

### 5.2 Repeatable read:

Este nível garante que, se você leu a Linha A, ela será a mesma até o fim. O banco coloca um "cadeado" nas linhas que você tocou. Se mudarem o valor de algo que você acessou durante a sua transação, você continuará vendo os valores originais e irá concluir a transação.

**Problema:** Não resolve o fantasma. Se durante a sua transação alguém inserir uma nova linha e commitar, você irá ver valores diferentes ao concluir a transação.

### 5.3 Serializable:

Este é o nível mais alto. Ele não trava apenas as linhas, ele trava o intervalo da consulta.

O banco tira um snapshot dos dados antes da transação e você apenas ve os dados de acordo com essa snapshot. Se alguém mudar os dados durante a sua transação, ocorre um erro e sua transação nao ocorre.

| Nível | Leitura Suja | Leitura Não Repetível | Leitura Fantasma |
| :--- | :---: | :---: | :---: |
| **Read Uncommitted** | Sim | Sim | Sim |
| **Read Committed** | **NÃO** | Sim | Sim |
| **Repeatable Read** | **NÃO** | **NÃO** | Sim |
| **Serializable** | **NÃO** | **NÃO** | **NÃO** |

## 6. Locks

É uma trava que impede qualquer outra transação de ler ou escrever no dado enquanto a transação atual estiver modificando.

**Write Lock:**

- Usado com transações que modificam (UPDATE/DELETE/INSERT).
- Impede qualquer outra transação de ler ou escrever no dado enquanto a transação atual estiver modificando.

**Read Lock:**

- Usado com transação de SELECT.
- Impede que outras transações escrevam ou modificam o dado enquanto ele está sendo lido.
- Permite a leitura compartilhada.

**Range lock:**

- Usado com transações de grupos (select + where).
- Impede que novas tuplas de um dado sejam alteradas/adicionadas.


| Tipo de Lock | Permite Leitura? | Permite Escrita? | Objetivo Principal |
| :--- | :---: | :---: | :--- |
| **Write Lock** (Exclusivo - X) | Não |  Não | **Exclusividade total**: impede que qualquer outra transação leia ou modifique o dado enquanto ele está sendo alterado. |
| **Read Lock** (Compartilhado - S) | Sim | Não | **Consistência de Leitura**: várias transações podem ler o mesmo dado ao mesmo tempo, mas nenhuma pode alterá-lo até que todos os Read Locks sejam liberados. |
| **Range Lock** (Intervalo) | Não | Não | **Evitar Fantasmas**: bloqueia a inserção de novas tuplas em um intervalo específico (Ex: `WHERE idade BETWEEN 20 AND 30`) para garantir que o conjunto não mude. |

## 7. Comandos Básicos
Estes comandos gerenciam as alterações feitas por comandos DML e garantem as propriedades ACID.

| Comando SQL | Função |
| :--- | :--- |
| **START TRANSACTION** ou **BEGIN** | Inicia explicitamente uma nova transação. |
| **SET TRANSACTION ISOLATION LEVEL** | Define o nível de isolamento (Read Committed, Serializable, etc.) para a transação atual. |
| **COMMIT** | Salva permanentemente todas as alterações feitas na transação no banco de dados. |
| **ROLLBACK** | Aborta a transação e desfaz todas as alterações, retornando o banco ao estado anterior ao BEGIN. |
| **SAVEPOINT** | Cria um "ponto de restauração" dentro de uma transação para permitir rollbacks parciais. |

**Exemplo**

```sql
-- Inicia a transação
BEGIN;

SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

-- Debita R$100,00 da conta A
UPDATE contas
SET saldo = saldo - 100
WHERE nome = 'Conta A';

-- Credita R$100,00 na conta B
UPDATE contas
SET saldo = saldo + 100
WHERE nome = 'Conta B';

-- Confirma as mudanças
COMMIT;

-- Caso der algum erro
ROLLBACK;
```