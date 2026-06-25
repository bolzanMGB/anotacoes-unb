.data

.text
    .globl main

main:
    li $v0, 6
    syscall
    mov.s $f12, $f0

    li $v0, 5
    syscall
    move $t0, $v0

    li $v0, 5
    syscall
    move $t1, $v0

    mtc1 $t0, $f0
    cvt.s.w $f0, $f0
    mul.s $f0, $f12, $f0

    mtc1 $t1, $f1
    cvt.s.w $f1, $f1
    mul.s $f1, $f12, $f1

    add.s $f12, $f12, $f0
    add.s $f12, $f12, $f1

    li $v0, 2
    mov.s $f12, $f12
    syscall

    li $v0, 10
    syscall
