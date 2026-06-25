main:
    li $v0, 5
    syscall
    move $a0, $v0

    li $v0, 5
    syscall
    move $a1, $v0

    j multfac

multfac:

    blt $a0, $zero, Mneg
    blt $a1, $zero, Qneg

    j iniciar

Mneg: 
    not  $a0, $a0
    addi $a0, $a0, 1

    blt $a1, $zero, Qneg

    j iniciar


Qneg: 
    not  $a1, $a1
    addi $a1, $a1, 1

    j iniciar

iniciar:
    move $t1, $zero
    move $t2, $a1

    li $t9, 32
    li $t8, 1

    j passo2

passo2:
    li $t3, 0
    andi $t3, $t2, 1
    bne $t3, $zero, passo2B
    j passo3

passo2B:
    add $t1, $t1, $a0
    j passo3

passo3:
    li $t3, 0
    andi $t3, $t1, 1 
    sll $t3, $t3, 31

    srl $t1, $t1, 1
    srl $t2, $t2, 1
    or $t2, $t2, $t3

    j passo4

passo4:
    bge $t8, $t9, end
    addi $t8, $t8, 1
    j passo2

end:
    li $v0, 1
    move $a0, $t1
    syscall

    li $v0, 1
    move $a0, $t2
    syscall

    mtlo $t2
    mthi $t1
    li $v0, 10
    syscall

    

