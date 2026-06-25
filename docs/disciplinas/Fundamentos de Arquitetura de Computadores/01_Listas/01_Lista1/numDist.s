elemDistintos:
    li $v0, 0
    li $t0, -1
    li $t1, 0

loop:
    beq $t1, $a1, end
    sll $t2, $t1, 2
    add $t3, $a0, $t2
    lw $t4, 0($t3)
    beq $t4, $t0, skip
    addi $v0, $v0, 1
    move $t0, $t4

skip:
    addi $t1, $t1, 1
    j loop

end:
    jr $ra
