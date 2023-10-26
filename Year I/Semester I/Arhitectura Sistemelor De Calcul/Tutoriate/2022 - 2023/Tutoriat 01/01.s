.data
    x: .space 4
    formatScanf: .asciz "%d"
    formatPrintf: .asciz "Numarul cu semnul inversat este %d\n"
    formatPrintf2: .asciz "Numarul incrementat este %d\n"

.text
.globl main

main:
    # Citire
    pushl $x
    pushl $formatScanf
    call scanf
    popl %edx
    popl %edx

    # Prima metoda - inmultire cu -1
    movl $0xFFFFFFFF, %eax
    movl x, %ebx
    xorl %edx, %edx
    imul %ebx


    # Afisare
    pushl %eax
    pushl $formatPrintf
    call printf
    popl %edx
    popl %edx

    # ########

    # A doua metoda - complement la 2
    movl x, %eax
    not %eax
    addl $1, %eax


    # Afisare
    pushl %eax
    pushl $formatPrintf
    call printf
    popl %edx
    popl %edx

    # ########

    # A treia metoda - neg
    movl x, %eax
    neg %eax


    # Afisare
    pushl %eax
    pushl $formatPrintf
    call printf
    popl %edx
    popl %edx

    # ########

    # Incrementare cu not si neg
    movl x, %eax
    not %eax
    neg %eax


    # Afisare
    pushl %eax
    pushl $formatPrintf2
    call printf
    popl %edx
    popl %edx


    # ########

    # Incrementare cu lea
    movl x, %eax
    lea 0x1(%eax), %eax


    # Afisare
    pushl %eax
    pushl $formatPrintf2
    call printf
    popl %edx
    popl %edx



    # Iesire
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80

