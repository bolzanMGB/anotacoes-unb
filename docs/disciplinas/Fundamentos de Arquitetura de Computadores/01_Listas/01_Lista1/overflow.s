.data
    msg:    .asciiz "overflow"   # Mensagem para indicar overflow

.text
main:
    # Lê o primeiro número
    li $v0, 5
    syscall
    move $s0, $v0

    # Lê o segundo número
    li $v0, 5
    syscall
    move $s1, $v0

    # Lê o terceiro número
    li $v0, 5
    syscall
    move $s2, $v0

    # Verifica se o primeiro número é zero (sem sinal)
    beq $s0, $zero, semsinal
    bne $s0, $zero, comsinal

comsinal:
    # Soma com sinal
    addu $t0, $s1, $s2

    # Verifica se os sinais de $s1 e $s2 são diferentes (sem overflow)
    xor $t1, $s1, $s2
    bge $t1, $zero, semOF         # Se $t1 >= 0, sem overflow

    # Verifica se os sinais de $t0 e $s1 são diferentes (overflow)
    xor $t1, $t0, $s1
    blt $t1, $zero, comOF         # Se $t1 < 0, overflow

semOF:
    # Sem overflow, imprime o resultado
    li $v0, 1
    move $a0, $t0
    syscall
    li $v0, 10
    syscall

comOF:
    # Overflow, exibe mensagem
    li $v0, 4
    la $a0, msg
    syscall
    li $v0, 10
    syscall

semsinal:
    addu $t0, $s1, $s2
    slt $t1, $t0, $s1    
    bnez $t1, semOF      # Se houve overflow, vai para o tratamento de overflow

    # Sem overflow, imprime o resultado
    li $v0, 1
    move $a0, $t0
    syscall
    li $v0, 10
    syscall

