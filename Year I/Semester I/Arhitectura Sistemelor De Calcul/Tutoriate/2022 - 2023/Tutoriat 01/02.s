.data
    x: .space 4
    formatScanf: .asciz "%d"
    formatPrintf: .asciz "%d\n"

.text
.globl main

main:
    # Citire
    pushl $x
    pushl $formatScanf
    call scanf
    popl %edx
    popl %edx

    movl x, %ecx
    for:
        # Verificam daca e 1
        cmp $1, %ecx
        je final_for

        # Verificam daca este par
        movl %ecx, %eax
        movl $2, %ebx
        xorl %edx, %edx
        divl %ebx

        cmp $0, %edx
        je par

        # Impar
        movl $3, %eax
        xorl %edx, %edx
        mull %ecx
        movl %eax, %ecx
        incl %ecx

        jmp print_for


        par:
            movl %eax, %ecx
            jmp print_for

        
        print_for:
            # Afisare
            pushl %ecx
            pushl $formatPrintf
            call printf
            popl %edx
            popl %ecx

            jmp for



    final_for:
       


    exit:
        # Iesire
        movl $1, %eax
        xorl %ebx, %ebx
        int $0x80

