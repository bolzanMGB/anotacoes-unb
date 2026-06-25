.data
    custo: .double 0.0
    lucro: .word 0
    impostos: .word 0

.text
main:

    li $v0, 7
    syscall
    s.d $f0, custo

    li $v0, 5
    syscall
    sw $v0, lucro

    li $v0, 5
    syscall
    sw $v0, impostos

    l.d $f8, custo

    lw $t0, lucro
    mtc1 $t0, $f2
    cvt.s.w $f2, $f2
    div.s $f4, $f2, $f8
    mul.s $f4, $f4, $f8

    lw $t1, impostos
    mtc1 $t1, $f6
    cvt.s.w $f6, $f6
    div.s $f10, $f6, $f8
    mul.s $f10, $f10, $f8

    add.s $f12, $f8, $f4
    add.s $f12, $f12, $f10

    li $v0, 2
    syscall

    li $v0, 10
    syscall
