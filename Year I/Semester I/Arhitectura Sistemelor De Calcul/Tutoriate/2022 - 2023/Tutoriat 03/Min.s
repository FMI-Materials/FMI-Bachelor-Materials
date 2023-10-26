.data
        a:      .space  4
        b:      .space  4
        c:      .space 4
        formatScanf: .asciz "%d %d %d"
        formatPrintf: .asciz "%d\n"

.text

min:
        pushl   %ebp
        movl    %esp, %ebp

        movl    8(%ebp), %eax

        cmp     12(%ebp), %eax
        jle     cont

        movl    12(%ebp), %eax

        cont:

        cmp     16(%ebp), %eax
        jle     cont1

        movl    16(%ebp), %eax

        cont1:


        popl    %ebp
        ret

.global main

main:

        citire:

        pushl   $a
        pushl   $b
        pushl   $c
        pushl   $formatScanf

                call scanf

        popl    %ebx
        popl    %ebx
        popl    %ebx
        popl    %ebx

        pushl   a
        pushl   b
        pushl   c

                call min

        popl    %ebx
        popl    %ebx
        popl    %ebx

        pushl   %eax
        pushl   $formatPrintf

                call printf

        popl    %ebx
        popl    %ebx


exit:

        movl    $1, %eax
        xorl    %ebx, %ebx
        int     $0x80
