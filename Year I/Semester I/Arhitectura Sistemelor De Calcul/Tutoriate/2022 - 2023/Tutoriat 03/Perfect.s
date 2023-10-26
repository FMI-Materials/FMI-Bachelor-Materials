#
#	Program care citeste de la tastatura n, urmat de un sir cu n termeni.
#	Programul afiseaza pe ecran cate din aceste numere sunt perfecte!
#	Referinta: bit.ly/3VTjTJX
#	ASC - "Laborator Partea 0x01" - Sectiunea exercitii - exercitiul 1
.data
        x: .space 4
        n: .space 4
        formatScanf: .asciz "%d"
        formatPrintf: .asciz "%d\n"

.text

.global main

perfect:
        pushl   %ebp
        movl    %esp, %ebp

        subl    $8, %esp

        movl    8(%ebp), %eax           #       eax = n
        xorl    %edx, %edx              #       edx = 0

        movl    $2, %ecx                #       ecx = 2

        divl    %ecx                    #       eax = n /2

        movl    %eax, -4(%ebp)          # var1 = n / 2

        xorl    %ecx, %ecx              # ecx = 0
        movl    %ecx, -8(%ebp)          # var2 = 0 (suma)

        incl    %ecx
        for:
        cmp     -4(%ebp), %ecx          # for(int i = 1; i <= var1; ++i))
        jg      end_for

        xorl    %edx, %edx              # edx = 0
        movl    8(%ebp), %eax           # eax = arg

        divl    %ecx                    # eax/ecx

        cmp     $0, %edx
        jne cont

                addl    %ecx, -8(%ebp)

        cont:

        incl    %ecx
        jmp     for

        end_for:

        movl    -8(%ebp), %eax
        cmp     8(%ebp), %eax
        jne     cont1

        movl    $1, %eax

        jmp resume

        cont1:
        xorl    %eax, %eax

        resume:
        addl    $8, %esp

        popl    %ebp
        ret

main:

        pushl   $n
        pushl   $formatScanf

        call    scanf

        popl    %ebx
        popl    %ebx

        xorl    %ecx, %ecx
        xorl    %edx, %edx
for_main:
        cmp     n, %ecx
        jge     end_for_main

                pushl   %ecx            #       pregatesc restaurarea lui ecx
                pushl   %edx            #       pregatesc restaurarea lui edx

        pushl   $x
        pushl   $formatScanf

        call    scanf

        popl    %ebx
        popl    %ebx

        pushl   x

        call    perfect

        popl    %ebx

                popl    %edx
                popl    %ecx

        cmpl    $1, %eax                #       if(perfect(n))
        jne     cont2

        incl    %edx

        cont2:
        incl    %ecx
        jmp     for_main

end_for_main:
        pushl   %edx
        pushl   $formatPrintf

        call    printf

        popl    %ebx
        popl    %ebx

exit:
        movl    $1, %eax
        xorl    %ebx, %ebx
        int     $0x80
