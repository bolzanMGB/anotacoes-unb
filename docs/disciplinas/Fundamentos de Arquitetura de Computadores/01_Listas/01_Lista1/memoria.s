li   $v0, 5
syscall
move $a0, $v0

li   $v0, 5
syscall
move $a1, $v0

li   $v0, 5
syscall
move $a2, $v0

mul $t0, $a1, 4         
add $t0, $s0, $t0      
lw $t1, 0($t0)          

add $t1, $t1, $a2      

mul $t2, $a0, 4         
add $t2, $s0, $t2      

sw $t1, 0($t2)          
