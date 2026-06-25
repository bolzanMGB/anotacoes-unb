.data
    msg: .asciiz "overflow"

.text
main:
    li $v0, 5
    syscall
    move $t0, $v0

    li $v0, 5
    syscall
    move $t9, $v0

    li $v0, 5
    syscall
    move $t8, $v0

    xor $t3, $t9, $t8
    bgt $zero, $t3, teste

    j OF

teste:
    addu $a0, $t9, $t8
    li $v0, 1
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    li $v0, 10
    syscall

OF:
    addu $a0, $t9, $t8
    xor $t3, $a0, $t9
    bgt $zero, $t3, temOF

    li $v0, 1
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    li $v0, 10
    syscall

temOF:
    la $a0, msg
    li $v0, 4
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    li $v0, 10
    syscall
