.data
    s: .space 12
.text
.globl main
main:
    mov $3, %eax
    mov $0, %ebx
    mov $s, %ecx
    mov $12, %edx 
    int $0x80

etShow:
    pushl $s
    call printf
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

etExit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
