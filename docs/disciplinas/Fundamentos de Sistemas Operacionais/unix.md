# Fundamentos UNIX

---

## 1. Criação de Processos

### 1.1 Identificadores

* **pid (process id):** identificador único de um processo.
* **ppid (parent process id):** identificador do processo pai.


```c title="Exemplo:"
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t meupid = getpid();
    printf("Pid atual do processo: %d\n", meupid);

    pid_t pidpai = getppid();
    printf("Pid do pai do processo: %d\n", pidpai);
    return 0;
}
```

### 1.2 fork()

* Cria uma **cópia do processo atual** (pai → filho).
* Pai e filho continuam a execução do mesmo ponto.
* O filho herda quase toda a tabela de processos do pai.

- **Retorno:**

    -  0 → processo filho.
    -  pid do filho → processo pai.

```c title="Exemplo:"
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t id_filho;

    printf("Processo inicial possui pid: %d\n", getpid());
    id_filho = fork();
    if (id_filho == 0)
        printf("Olá, sou o processo filho de pid: %d!\n", getpid());
    else
        printf("Olá, sou o processo pai (%d) e criei o filho: %d!\n", getpid(), id_filho);
    return 0;
}

// Saída esperada:
// Processo inicial possui pid: 16370
// Olá, sou o processo pai (16370) e criei o filho: 16371!
// Olá, sou o processo filho de pid: 16371!
```

---

## 2. Carga de Arquivo Executável

* **fork():** cria processos por clonagem (mesmo programa).
* **exec():** substitui o processo atual por um novo programa.

  * O pid continua o mesmo, mas código e dados são substituídos.
  * Retorna apenas em caso de falha.
  * Em caso de sucesso:

    * Código do programa atual é descartado.
    * O processo carrega o novo programa na memória.
    * A execução começa do início (`main()`).

### 2.1 Famílias de funções exec

**Formas de passar argumentos:**

  * `v`: argumentos em vetor → `execv("/bin/ls", argv)`.
  * `l`: argumentos em lista variada → `execl("/bin/ls", "ls", "-l", NULL)`.

**Onde procurar o programa:**

  * `p`: procura no PATH → `execlp("ls", "ls", "-l", NULL)`.
  * sem `p`: exige caminho completo → `execl("/bin/ls", "ls", "-l", NULL)`.

**Variáveis de ambiente:**

  * Com `e`: permite passar variáveis de ambiente.
  * Sem `e`: herda o ambiente do processo atual.

---

## 3. Sinais

### 3.1 O que são

* Mecanismo do UNIX para **comunicação entre processos**.
* Alteram o comportamento do processo alvo.
* Ao receber um sinal, o processo pode:

  * Ser interrompido e executar um **handler** (função tratadora).
  * Ignorar o sinal.

### 3.2 Exemplos de sinais

* `SIGTERM`: Terminar (padrão).
* `SIGKILL`: Finalização forçada (não pode ser ignorado).
* `SIGUSR1`, `SIGUSR2`: Uso definido pelo usuário.
* `SIGSEGV`: Acesso inválido à memória (segfault).
* `SIGFPE`: Erro de ponto flutuante.

### 3.3 Envio de sinais

**Pelo terminal:**

  1. Executar o programa.
  2. Encontrar o pid com `ps aux | grep nome_do_programa`.
  3. Enviar sinal: `kill -SIGUSR1 2240`.

**No código em C:**

        ```c
        kill(pid_filho, SIGUSR1);
        ```

### 3.4 Exemplo completo

```c title="Exemplo:"
#include <signal.h>
#include <stdio.h>

int contador = 0;

void handler(int signal_number) {
    contador++;
}

int main() {
    struct sigaction sa = {};
    sa.sa_handler = &handler; // define o tratador
    sigaction(SIGUSR1, &sa, NULL);
    // Quando esse processo receber SIGUSR1, executa handler

    printf("Pressione E para terminar a execução:\n");

    while (getchar() != 'E') ;

    printf("SIGUSR1 recebido %d vezes\n", contador);
    return 0;
}
```

---

## 4. Término de Processos

### 4.1 Formas de término

**Por sinais:** `SIGTERM`, `SIGKILL`.

**Voluntariamente:**

- Retornando da função `main`.
- Chamando `exit()`:
      * `exit(0)`: sucesso.
      * `exit(1)`: erro.

### 4.2 Comunicação com processo pai

* **wait():** processo pai bloqueia até o filho terminar.
* **pause():** processo atual pausa até receber sinal.
* **Macros úteis:**

    * `WIFEXITED(status)`: verifica se o filho terminou normalmente.
    * `WEXITSTATUS(status)`: obtém valor de retorno do filho.

### 4.3 Processos Zumbis

**Normal:** pai cria filho, depois chama `wait()` para receber informações de término.

**Zumbi:** filho termina, mas o pai não chama `wait()`. O processo permanece na tabela como "zumbi" até o pai coletar seu status.

```c title="Exemplo:"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho > 0)
        sleep(6);
    else
        exit(0);
    wait(NULL); // elimina o zumbi
    return 0;
}
```

---

## 5. Considerações Finais

* **fork + exec** são a base para criação e substituição de processos no UNIX.
* **Sinais** permitem comunicação e controle.
* O gerenciamento de término é essencial para evitar processos zumbis.
