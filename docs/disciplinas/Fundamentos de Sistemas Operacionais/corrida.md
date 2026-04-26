# Condições de Corrida

---

## 1. O que é

* Situação em que **dois ou mais processos/threads** tentam acessar e modificar um recurso compartilhado **ao mesmo tempo**.
* O resultado depende da **ordem de execução** dos acessos.
* Como o **escalonador do SO** decide a ordem de execução e pode ocorrer **troca de contexto a qualquer instante**, não há garantia de consistência.

---

## 2. Exemplos de Condições de Corrida

### 2.1 Exemplo 1 – Incremento de variável

* Duas threads incrementam a mesma variável `x` (inicialmente 0) até 2.
* Dependendo da ordem de execução, o valor final pode estar incorreto.

```js title="Exemplo:"
// Caso 1 - Escalonamento: A → B
LOAD R1, x  (x = 0)
INC R1      (R1 = 1)
STORE R1, x (x = 1)

LOAD R1, x  (x = 1)
INC R1      (R1 = 2)
STORE R1, x (x = 2)
// Valor final: x = 2 ✅

// Caso 2 – Escalonamento: A → B → A
LOAD R1, x  (x = 0)
INC R1      (R1 = 1)

LOAD R1, x  (x = 0)
INC R1      (R1 = 1)
STORE R1, x (x = 1)

STORE R1, x (x = 1)
// Valor final: x = 1 ❌ (incremento perdido)
```

### 2.2 Exemplo 2 – Servidor de Impressão

```js title="Exemplo:"
// Situação
x = next;
escreve_pos(arq, x);
next = x + 1;

// Possibilidades
A → B: tudo ocorre bem → next = 9
A → B → A: ambos pegam next = 7 → sobrescrevem, e next = 8 (posição repetida!)
```

---

## 3. Regiões Críticas

* **Região crítica**: trecho de código onde há **leitura/escrita em recurso compartilhado**.

  * No exemplo 1: a operação de incremento.
  * No exemplo 2: a escrita na posição de impressão.

* **Funções de controle**:

  * Colocadas **antes e depois da região crítica**.
  * Impedem que dois processos entrem simultaneamente.
  * Garantem **exclusão mútua**.

### 3.1 Variáveis de Impedimento

* Usadas para indicar se um processo está na região crítica.
* Exemplo:

  * `0` → livre
  * `1` → ocupado

---

## 4. Considerações Finais

* Condições de corrida são erros **difíceis de detectar e reproduzir**.
* O controle deve ser feito por **sincronização** (exclusão mútua, semáforos, monitores, locks, etc.).
* Prevenir condições de corrida é essencial para garantir **consistência e integridade dos dados** em sistemas concorrentes.
