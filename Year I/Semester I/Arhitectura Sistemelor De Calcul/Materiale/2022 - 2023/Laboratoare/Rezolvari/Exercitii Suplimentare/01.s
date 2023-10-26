.data
    curr_c: .asciz "a"
    x: .space 4
    y: .space 4
    z: .space 4
    sol: .space 4
    show: .asciz "(%s) %ld\n"
    read: .asciz "%ld %ld %ld"
.text
show_sol:
    pushl %ebp
    movl %esp, %ebp

    
    pushl 8(%ebp)
    pushl $curr_c
    pushl $show
    call printf
    popl %ebx
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

    mov 0(%esi), %eax
    inc %eax
    mov %eax, 0(%esi)

    popl %ebp
    ret

.globl main
main:
    lea curr_c, %esi
    pushl $z
    pushl $y
    pushl $x
    pushl $read
    call scanf
    popl %edx
    popl %edx
    popl %edx
    popl %edx

etA:
    mov x, %eax
    and $1, %eax
    mov %eax, sol

    pushl sol
    call show_sol
    popl %edx

etB:
    mov x, %eax
    xor %eax, %eax
    mov %eax, sol

    pushl sol
    call show_sol
    popl %edx

etC:
    mov x, %eax
    mov y, %ebx
    mov %eax, %ecx
    xor %ebx, %ecx
    xor %ebx, %ecx
    mov %ecx, sol

    pushl sol
    call show_sol
    popl %edx

etD:
    mov x, %eax
    mov %eax, %ebx
    sub $1, %ebx
    and %ebx, %eax
    mov %eax, sol

    pushl sol
    call show_sol
    popl %edx

etE:
    mov x, %eax
    mov y, %ebx
    mov %eax, %ecx
    mov %ebx, %edx
    not %edx
    and %eax, %edx
    not %ecx
    and %ecx, %ebx
    or %ebx, %edx
    mov %edx, sol

    pushl sol
    call show_sol
    popl %edx

etF:
    mov x, %eax
    mov y, %ebx
    mov %eax, %ecx
    mov %ebx, %edx
    not %ecx
    and %ecx, %eax
    not %edx
    and %edx, %ebx
    or %ebx, %eax
    mov %eax, sol

    pushl sol
    call show_sol
    popl %edx

etExit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80