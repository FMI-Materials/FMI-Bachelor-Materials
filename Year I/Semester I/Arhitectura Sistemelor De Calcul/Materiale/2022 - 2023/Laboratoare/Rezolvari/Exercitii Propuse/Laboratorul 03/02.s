.data
    n: .space 4
    show: .asciz "%s\n"
    s: .space 100
    t: .space 100
.text
.globl main
main:
    pushl $s
    call gets
    popl %ebx

    pushl $s
    call strlen
    popl %ebx

    mov $0, %edx
    mov %eax, n
    mov n, %ecx

    lea s, %esi
    lea t, %edi

etLoop:
    mov -1(%esi, %ecx, 1), %ebx
    mov %ebx, (%edi, %edx, 1)

    inc %edx
    loop etLoop

etWrite:
    mov $0, %ebx
    mov %ebx, (%edi, %edx, 1)

    pushl $t
    pushl $show
    call printf
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

etExit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
