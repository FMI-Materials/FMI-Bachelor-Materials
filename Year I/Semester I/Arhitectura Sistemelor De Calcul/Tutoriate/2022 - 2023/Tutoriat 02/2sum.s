/*
    Uitati-va mai intai la rezolvarea in C!
*/

.data
    n:  .space 4
    x:  .space 4
    i:  .long 0
    j:  .long 0
    v:  .space 400
    formatScanf:    .asciz "%d"
    formatScanf1: .asciz "%d %d\n"
.text

.global main

main:
    #citire n si x  -- scanf("%d %d", &n, &x);
    pushl   $x
    pushl   $n
    pushl   $formatScanf1
    
    call    scanf

    popl    %ebx
    popl    %ebx
    popl    %ebx

    #citire elemente in vector

    xorl    %ecx, %ecx      # i = 0

    for_citire:
    cmpl    n, %ecx         #   for(int i = 0; i < n; ++i)
    jge     exit_citire
    
            pushl   %ecx            #   pregatesc restaurarea lui ecx

    #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    xorl    %edx, %edx      #   edx = 0 -- obligatoriu cand facem inmultiri/ impartiri
    lea     v, %esi         #   esi = &v
    movl    %ecx, %eax      #   eax = i
    movl    $4, %ecx        #   ecx = 4 
    mull    %ecx            #   eax = 4 * i
    addl    %esi, %eax      #   eax = v[i] -- de ce nu 4 * i? Am scris in modul in care ati scrie in C
    #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    

    #citire v[i] -- scanf("%d", &v[i]);
    pushl   %eax            #   &v[i]
    pushl   $formatScanf
    
    call    scanf

    popl    %ebx
    popl    %ebx

            popl    %ecx            #   ecx este restaurat

    incl    %ecx
    jmp for_citire

exit_citire:

    lea     v, %esi

    for_1:                  #   for(int i = 0; i < n; ++i)
    movl    i, %ecx
    cmpl    n, %ecx
    jge     exit_for1

    incl    %ecx
    movl    %ecx, j

    for_2:                  #   for(int j = i + 1; j < n; ++j)
    movl    j, %ecx
    cmpl    n, %ecx
    jge     inc_i

    movl    (%esi, %ecx, 4), %eax           #   eax = v[j]
    movl    i, %ecx
    movl    (%esi, %ecx, 4), %edx           #   edx = v[i]
    addl    %edx, %eax                      #   eax = v[i] + v[j]
    
    cmpl    x, %eax         #   if(v[i] + v[j] == x)
    je      sol

    incl    j    

    jmp     for_2

    inc_i:
    incl    i
    jmp     for_1

sol:
    pushl   j
    pushl   i
    pushl   $formatScanf1
    
    call    printf
    
    popl    %ebx
    popl    %ebx
    popl    %ebx

exit_for1:

exit:
    movl    $1, %eax
    xorl    %ebx, %ebx
    int     $0x80
