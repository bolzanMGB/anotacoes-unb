# Fundamentos Assembly MIPS

---

## 1. Tipos de Linguagem de Programação

### 1.1 Linguagem de Máquina

* É o **nível mais baixo**, interpretado diretamente pelo processador.
* Usa apenas **códigos binários (0 e 1)**, sem nenhuma abstração.
* **Vantagens:** rápido e eficiente, sem camadas extras.
* **Desvantagens:** muito difícil para humanos lerem/escreverem e específico para cada hardware.



```c title="Exemplo hipotético:"
10110000 01100001
```

---

### 1.2 Linguagem de Montagem (Assembly)

* Representação **simbólica** da linguagem de máquina.
* Usa **mnemônicos** (`ADD`, `SUB`, `MOV`, `LW`, etc.) no lugar de binário puro.
* Cada instrução Assembly corresponde a **1 instrução de máquina**.
* Depende do hardware → cada arquitetura (x86, MIPS, ARM) tem seu Assembly próprio.
* Necessita de um **Assembler** para traduzir para linguagem de máquina.

Exemplo MIPS:

```asm title="Exemplo MIPS:"
add $t0, $t1, $t2   # $t0 = $t1 + $t2
```

---

### 1.3 Linguagens de Alto Nível

* Mais próximas da linguagem humana, independentes do hardware.
* Ex: **Python, C, Java, C++**.
* Precisam de **Compiladores** ou **Interpretadores** para transformar o código em Assembly/Linguagem de máquina.

**Diferença:**

* **Compilador (ex.: C):** traduz o código inteiro para binário antes da execução.
* **Interpretador (ex.: Python):** traduz e executa **linha por linha**.


```c title="Exemplo em C:"
int soma(int a, int b) {
    return a + b;
}
```

---

## 2. Arquiteturas RISC x CISC

### 2.1 RISC (Reduced Instruction Set Computer)

* Poucas instruções, simples e rápidas.
* Cada instrução geralmente executa em **1 ciclo de clock**.
* Uso eficiente do hardware.
* Exemplo: **MIPS, ARM**.

### 2.2 CISC (Complex Instruction Set Computer)

* Conjunto de instruções maior e mais complexo.
* Algumas instruções realizam tarefas de alto nível, mas são mais lentas.
* Foco na eficiência do software (menos linhas de código).
* Exemplo: **x86 (Intel/AMD)**.

---

## 3. Registradores no MIPS

* São **pequenas memórias internas do processador** (muito rápidas).
* No MIPS, existem **32 registradores de 32 bits**.
* Servem para armazenar **dados temporários**, **endereços de memória** e **valores de controle**.

Exemplos de registradores:

* `$t0–$t9`: registradores temporários.
* `$s0–$s7`: valores salvos.
* `$a0–$a3`: passagem de argumentos em funções.
* `$v0–$v1`: valores de retorno de funções.
* `$ra`: endereço de retorno (para JAL/JR).

---

## 4. Estrutura de um Código em Assembly MIPS

```asm
.data                        # Declaração de variáveis
msg:    .asciiz "Hello, World!"  # String armazenada na memória
num1:   .word 5                  # Número inteiro
num2:   .word 10
result: .word 0

.text                         # Seção de código
main:
    lw $t0, num1              # Carrega num1 em $t0
    lw $t1, num2              # Carrega num2 em $t1
    add $t2, $t0, $t1         # Soma $t0 + $t1 → $t2
    sw $t2, result            # Salva o resultado na memória

    li $v0, 4                 # Chamada de sistema para imprimir string
    la $a0, msg
    syscall

    li $v0, 10                # Finaliza o programa
    syscall
```

---

## 5. Tipos de Dados

* **word** → 32 bits
* **half** → 16 bits
* **byte** → 8 bits
* **asciiz** → strings terminadas em `\0`

---

## 6. Pseudo-Instruções

São **atalhos** fornecidos pelo Assembler para simplificar a escrita.

* São traduzidas em **uma ou mais instruções reais** de máquina.


```asm title="Exemplos:"
li   $t0, 10    # carrega imediato (Load Immediate)
move $t0, $t1   # copia valor de $t1 para $t0
la   $t0, var   # carrega endereço de memória em $t0
```

---

## 7. System Calls

São chamadas que o programa faz ao **Sistema Operacional** para realizar funções de I/O.

Tabela (em MIPS, `$v0` guarda o código da operação):

| Código (\$v0) | Operação           | Argumento (`$a0`, `$a1`…)         | Resultado         |
| ------------- | ------------------ | --------------------------------- | ----------------- |
| 1             | Imprimir inteiro   | `$a0 = inteiro`                   | -                 |
| 4             | Imprimir string    | `$a0 = endereço`                  | -                 |
| 5             | Ler inteiro        | -                                 | `$v0 = inteiro`   |
| 8             | Ler string         | `$a0 = endereço`, `$a1 = tamanho` | String na memória |
| 10            | Encerrar programa  | -                                 | -                 |
| 11            | Imprimir caractere | `$a0 = caractere`                 | -                 |
| 12            | Ler caractere      | -                                 | `$v0 = caractere` |

```asm title="Exemplo MIPS:"
.data
msg: .asciiz "Digite um número: "

.text
main:
    li $v0, 4
    la $a0, msg
    syscall

    li $v0, 5
    syscall
    move $t0, $v0     # guarda inteiro lido em $t0
```

---

## 8. Instruções Aritméticas

```asm title="Comandos em MIPS:"
add  $t0, $t1, $t2   # soma
sub  $t0, $t1, $t2   # subtração
mul  $t0, $t1, $t2   # multiplicação
div  $t0, $t1        # divisão
addi $t0, $t1, 10    # soma imediato
```

---

## 9. Acesso à Memória

**Load (carregar da memória)**

```asm title="Exemplo:"
lw $t0, 32($s2)   # $t0 = A[8]
```

**Store (salvar na memória)**

```asm title="Exemplo:"
sw $t0, 48($s2)   # A[12] = $t0
```

---

## 10. Instruções Lógicas e Deslocamento

**Intruções Lógicas**

* `and`, `or`, `xor`, `nor`

**Deslocamento**

* `sll`, `srl`

```asm title="Exemplo deslocamento:"
sll $t0, $s0, 4   # desloca 4 bits à esquerda (multiplica por 2^4)
srl $t0, $s0, 2   # desloca 2 bits à direita (divide por 2^2)
```

---

## 11. Controle de Fluxo

### 11.1 Chamada a Procedimentos

**JAL (Jump and Link):** chama função e salva retorno em `$ra`.

**JR (Jump Register):** retorna de função.


```asm title="Exemplo:"
main:
    li $a0, 5
    li $a1, 10
    jal soma
    move $a0, $v0
    li $v0, 1
    syscall

soma:
    add $v0, $a0, $a1
    jr $ra
```

---

### 11.2 Instruções de Desvio Condicional

* `beq` → branch if equal
* `bne` → branch if not equal
* `slt` → set less than


```asm title="Exemplo loop:"
li $t0, 0      # contador
li $t1, 5      # limite

loop:
    beq $t0, $t1, fim
    addi $t0, $t0, 1
    j loop

fim:
    li $v0, 10
    syscall
```

---

## 12. Representação de Números

* **Magnitude com sinal**
* **Complemento de 1**
* **Complemento de 2 (mais usado no MIPS)**
* **Excesso de N (para expoentes em ponto flutuante)**

---

## 13. Multiplicação e Divisão de Inteiros

Usa registradores especiais **HI** e **LO**.


```asm title="Exemplo:"
mult $t0, $t1   # resultado 64 bits
mflo $s0        # pega parte baixa
mfhi $s1        # pega parte alta

div $t0, $t1    # quociente em LO, resto em HI
mflo $s2
mfhi $s3
```

