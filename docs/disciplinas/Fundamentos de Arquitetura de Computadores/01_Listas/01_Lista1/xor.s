.data

.text
main: 
    li $v0,5 
    syscall
    move $s0, $v0

    li $t0, 0

    loop:
        beq $t0, $s0, end 

        li $v0, 12
        syscall 
        move $t1 , $v0

        li $v0, 12
        syscall 

        li $v0, 12
        syscall 
        move $t2 , $v0

        li $v0, 12
        syscall 
        
        beq $t1, $t2, false
        bne $t1, $t2, true

    false:
        li $v0, 1
        li $a0, 1 
        syscall

        li $v0, 11
        li $a0, 10
        syscall

        addi $t0, $t0, 1 
        j loop

    true:
        li $v0, 1
        li $a0, 2 
        syscall

        li $v0, 11
        li $a0, 10
        syscall

        addi $t0, $t0, 1 
        j loop

    end:
        li $v0, 10
        syscall
