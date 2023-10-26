.data
    sir: .space 101
    formatScanf: .asciz "%101[a-zA-z .]"
    formatPrintf: .asciz "%s\n"

.text
.globl main

main:
    # Citire
    pushl $sir
    pushl $formatScanf
    call scanf
    popl %edx
    popl %edx

    xorl %eax, %eax
    xorl %ecx, %ecx
    movl $for_next, %edx
    for:
        xorl %eax, %eax
        movb sir(,%ecx, 1), %al
        cmpl $0, %eax
        je print

        cmpb $97, %al
        jge maybe_small
        jmp *%edx

        maybe_small:
            cmpb $122, %al
            jg for_next

            subl $32, sir(, %ecx, 1)
            jmp *%edx

        for_next:
            incl %ecx
            jmp for
        

    print:
        # Afisare
        pushl $sir
        pushl $formatPrintf
        call printf
        popl %edx
        popl %ecx


    exit:
        # Iesire
        movl $1, %eax
        xorl %ebx, %ebx
        int $0x80

