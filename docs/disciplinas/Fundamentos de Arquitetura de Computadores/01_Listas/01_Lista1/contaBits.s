.data
    msg: .asciiz "overflow"

.text
main:
    li $v0, 5
    syscall
    move $t0, $v0

    li $v0, 5
    syscall
    move $t1, $v0

    li $v0, 5
    syscall
    move $t2, $v0

    beqz $t0, sem_sinal
    beq $t0, 1, com_sinal

sem_sinal:
    addu $a0, $t1, $t2
    li $v0, 1
    syscall

    j fim

com_sinal:
    add $a0, $t1, $t2
    xor $t3, $a0, $t1
    bltz $t3, overflow

    li $v0, 1
    syscall

    j fim

overflow:
    la $a0, msg
    li $v0, 4
    syscall

fim:
    li $v0, 10
    syscall
