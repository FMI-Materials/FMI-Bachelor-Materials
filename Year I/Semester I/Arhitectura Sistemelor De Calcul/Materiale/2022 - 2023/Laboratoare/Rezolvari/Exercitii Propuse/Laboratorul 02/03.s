.data
    a: .space 4
    b: .space 4
    c: .space 4
    min: .space 4
    read: .asciz "%ld %ld %ld"
    show: .asciz "%ld\n"
.text
.globl main
main:
    pushl $c
    pushl $b
    pushl $a
    pushl $read
    call scanf
    popl %ebx
    popl %ebx
    popl %ebx
    popl %ebx

    mov a, %eax
    cmp b, %eax
    jle etAIsBelow

    mov b, %eax
    cmp c, %eax
    jle etBIsLowest

    mov c, %eax
    mov %eax, min
    jmp etExit

etAIsBelow:
    cmp c, %eax
    jle etAIsLowest

    mov c, %eax
    mov %eax, min
    jmp etExit

etAIsLowest:
    mov a, %eax
    mov %eax, min
    jmp etExit

etBIsLowest:
    mov b, %eax
    mov %eax, min

etExit:
    pushl min
    pushl $show
    call printf
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
