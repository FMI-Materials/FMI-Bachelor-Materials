.data
    n: .space 4
    read: .asciz "%ld"
    isPrime: .asciz "The number is prime\n"
    isNotPrime: .asciz "The number is not prime\n"
.text
.globl main
main:
    pushl $n
    pushl $read
    call scanf
    popl %ebx
    popl %ebx

    mov n, %eax
    cmp $0, %eax
    je etNotPrime

    cmp $1, %eax
    je etNotPrime

    cmp $2, %eax
    je etPrime

    mov $0, %edx
    mov $2, %ebx
    div %ebx
    cmp $0, %edx
    je etNotPrime

    mov $3, %ecx

etLoop:
    cmp n, %ecx
    jae etPrime

    mov n, %eax
    mov %ecx, %ebx
    mov $0, %edx
    div %ebx
    cmp $0, %edx
    je etNotPrime

    add $2, %ecx
    jmp etLoop

etNotPrime:
    pushl $isNotPrime
    call printf
    popl %ebx
    jmp etExit

etPrime:
    pushl $isPrime
    call printf
    popl %ebx

etExit:
    pushl $0
    call fflush
    popl %ebx

    mov $1, %eax
    xor %ebx, %ebx
    int $0x80