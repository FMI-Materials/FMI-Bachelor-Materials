.data
    format_scan: .asciz "%ld"
    zero: .asciz "Numarul este zero\n"
    positive: .asciz "Numarul este pozitiv\n"
    negative: .asciz "Numarul este negativ\n"
.text
check:
    pushl %ebp
    movl %esp, %ebp

    cmp $0, 8(%ebp)
    je check_is_zero
    jl check_is_negative

    pushl $positive
    jmp check_end

check_is_zero:
    pushl $zero
    jmp check_end

check_is_negative:
    pushl $negative

check_end:
    call printf
    popl %edx

    pushl $0
    call fflush
    popl %edx

    popl %ebp
    ret

.globl main

main:
    pushl %ebp
    movl %esp, %ebp

    subl $4, %esp

    movl %ebp, %eax
    subl $4, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp

    pushl -4(%ebp)
    call check
    addl $4, %esp

    addl $4, %esp
    popl %ebp

et_exit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
