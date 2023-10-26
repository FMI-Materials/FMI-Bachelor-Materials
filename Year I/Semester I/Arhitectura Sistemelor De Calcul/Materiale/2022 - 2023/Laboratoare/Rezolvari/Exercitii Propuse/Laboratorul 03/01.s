.data
    max: .space 4
    ap: .space 4
    n: .space 4
    x: .space 4
    read: .asciz "%ld"
    show: .asciz "%ld %ld\n"
.text
.globl main
main:
    pushl $n
    pushl $read
    call scanf
    popl %ebx
    popl %ebx

    pushl $x
    pushl $read
    call scanf
    popl %ebx
    popl %ebx

    mov x, %eax
    mov %eax, max
    movl $1, ap

    mov $1, %ecx

etLoop:
    cmp %ecx, n
    je etExit

    pusha
    pushl $x
    pushl $read
    call scanf
    popl %ebx
    popl %ebx
    popa

    mov max, %eax

    cmp x, %eax
    je etEqual
    jl etGreater

    inc %ecx
    jmp etLoop

etEqual:
    incl ap
    inc %ecx
    jmp etLoop

etGreater:
    mov x, %eax
    mov %eax, max
    movl $1, ap
    inc %ecx
    jmp etLoop

etExit:
    pushl ap
    pushl max
    pushl $show
    call printf
    popl %ebx
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
