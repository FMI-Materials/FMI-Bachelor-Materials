.data
    sir: .asciz "wefme pym dsvvs"
    n: .long 4
    formatPrintf: .asciz "%s\n"

.text
.globl main

main:
    xorl %ecx, %ecx
    for:
        xorl %eax, %eax
        movb sir(, %ecx, 1), %al
        cmpb $0, %al
        je print

        cmpb $97, %al
        jl for_next
        cmpb $122, %al
        jg for_next

        subb $4, %al
        cmpb $96, %al
        jle cycle

        store:
            movb %al, sir(, %ecx, 1)
            jmp for_next

        cycle:
            movl $96, %ebx
            subb %al, %bl
            movb %bl, %al
            movl $122, %ebx
            subb %al, %bl
            movb %bl, %al
            jmp store

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

