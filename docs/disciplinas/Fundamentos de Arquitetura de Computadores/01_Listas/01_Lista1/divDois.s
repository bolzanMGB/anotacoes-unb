.data
n: .word 0
i: .word 0
mask: .word 0
result: .word 0

.text
.globl main

main:
    li $v0, 5
    syscall
    sw $v0, n

    li $v0, 5
    syscall
    sw $v0, i

    lw $t0, n
    lw $t1, i
    li $t2, 1
    sllv $t2, $t2, $t1
    addi $t2, $t2, -1
    and $t3, $t0, $t2
    sw $t3, result

    lw $a0, result
    li $v0, 1
    syscall

    li $v0, 10
    syscall
