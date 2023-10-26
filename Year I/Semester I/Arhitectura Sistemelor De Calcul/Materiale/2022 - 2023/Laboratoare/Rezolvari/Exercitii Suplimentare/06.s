.data 
    x: .space 4
    nr: .long 0
    read: .asciz "%ld"
    show: .asciz "%ld\n"
.text
.globl main
main:
    pushl $x
    pushl $read
    call scanf
    popl %edx
    popl %edx

    mov x, %ecx

etLoop:
    cmp $1, %ecx
    je etShow

    incl nr
    shr $1, %ecx

    jmp etLoop
    
etShow:
    pushl nr
    pushl $show
    call printf
    popl %edx
    popl %edx

    pushl $0
    call fflush
    popl %edx

etExit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80