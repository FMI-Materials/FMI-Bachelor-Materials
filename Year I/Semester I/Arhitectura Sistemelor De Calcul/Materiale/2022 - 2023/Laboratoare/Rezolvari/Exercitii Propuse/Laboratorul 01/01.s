.data
    x: .space 4
    y: .space 4
    read: .asciz "%ld %ld"
    show: .asciz "%ld %ld\n"
.text
.globl main
main:
    pushl $y
    pushl $x
    pushl $read
    call scanf
    popl %ebx
    popl %ebx
    popl %ebx

etChange:
    mov x, %eax
    mov y, %ebx

    xor %ebx, %eax
    xor %eax, %ebx
    xor %ebx, %eax 

    mov %eax, x
    mov %ebx, y

etShow:
    pushl y
    pushl x
    pushl $show
    call printf
    popl %ebx
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

etExit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
