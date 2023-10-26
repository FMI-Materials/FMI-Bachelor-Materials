.data
    read: .asciz "%ld %ld"
    show: .asciz "%ld %ld\n"
.text
swap:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movl 12(%ebp), %ebx
    xor %ebx, %eax
    xor %eax, %ebx
    xor %ebx, %eax

    pop %ebp
    ret

.globl main
main:
    pushl %ebp
    movl %esp, %ebp

    subl $8, %esp

    movl %ebp, %eax
    subl $8, %eax
    pushl %eax
    addl $4, %eax
    pushl %eax
    pushl $read
    call scanf
    addl $12, %esp

    pushl -8(%ebp)
    pushl -4(%ebp)
    call swap
    movl %eax, -4(%ebp)
    movl %ebx, -8(%ebp)
    addl $8, %esp

    pushl -8(%ebp)
    pushl -4(%ebp)
    pushl $show
    call printf
    addl $12, %esp

    pushl $0
    call fflush
    addl $4, %esp

    addl $8, %esp
    popl %ebp

et_exit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
