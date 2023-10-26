.data
    x: .space 4
    nr: .space 4
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
    mov $0, %eax

etLoop:
    cmp $0, %ecx
    je etShow

    add $1, %eax
    mov %ecx, %ebx
    dec %ebx
    and %ebx, %ecx
    jmp etLoop

etShow:
    mov %eax, nr
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
