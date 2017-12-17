
.global mipsRandom

        .text 
        
mipsRandom:   
        li $v0, 42 #SysCall to get RandomInt
        move $a1,$a0 #UpperLimit
        syscall  #Request Random Int will return ans in $a0
        move $v0,$a0 #Move Result to return
        jr $ra



