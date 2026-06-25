.data
    teste: .double 100.00
.text
main: 

    l.d $f8, teste
    li $v0, 7
    syscall
    mov.d $f2, $f0
    li $v0, 7
    syscall
    mov.d $f4, $f0
    li $v0, 7
    syscall
    mov.d $f6, $f0
    div.d $f10, $f4, $f8 
    mul.d $f14, $f10, $f2 
    div.d $f10, $f6, $f8 
    mul.d $f16, $f10, $f2 
    add.d $f12, $f14, $f16
    add.d $f12, $f12, $f2
    li $v0, 3
    syscall