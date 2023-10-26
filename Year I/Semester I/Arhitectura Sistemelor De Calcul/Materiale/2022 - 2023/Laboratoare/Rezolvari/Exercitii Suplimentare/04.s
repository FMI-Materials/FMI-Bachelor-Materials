.data
    x: .space 4
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

    mov $1, %ecx

etLoop:
    cmp x, %ecx
    ja etShow

    mov %ecx, %eax
    mov $2, %ebx
    mul %ebx
    mov %eax, %ecx
    jmp etLoop

etShow:
    mov %ecx, x
    pushl x
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