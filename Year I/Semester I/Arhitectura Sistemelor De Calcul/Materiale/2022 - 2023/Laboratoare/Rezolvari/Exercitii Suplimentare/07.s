.data
    n: .space 4
    max: .long 0
    read: .asciz "%ld"
    show: .asciz "%ld\n"
.text
.globl main
main:
    pushl $n
    pushl $read
    call scanf
    popl %edx
    popl %edx

    mov n, %ecx

etLoop:
    cmp $0, %ecx
    je etShow

    mov %ecx, %eax
    shr $1, %eax
    and %eax, %ecx
    incl max

    jmp etLoop

etShow: 
    pushl max
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
