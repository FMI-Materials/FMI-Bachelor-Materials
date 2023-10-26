/*
    Citesc numarul n urmat de un sir cu n termneni, numere naturale.
    Determinati numarul maxim si frecventa acestuia!
*/

.data
    v:  .space 400
    n:  .space 4
    max:    .long 0
    count:  .long 0
    fr:     .long 0
    x:  .space 4
    formatScanf:    .asciz "%d"
    formatPrintf:   .asciz "%d %d\n"
.text

.global main

main:
    
citire:
    
    # scanf("%d", n);

    pushl   $n
    pushl   $formatScanf
    
    call    scanf

    popl    %ebx
    popl    %ebx

    for_citire:
    movl    count, %ecx
    cmpl    n, %ecx
    jge     exit_for_citire

    movl    $v, %esi            # esi = &v = adresa lui v[0]
    xorl    %edx, %edx
    movl    %ecx, %eax          # eax = count
    movl    $4, %ebx            # ebx = 4
    mull    %ebx                # eax = eax * ebx = count * 4
    addl    %eax, %esi          # esi = v[count]
 
    pushl   %esi
    pushl   $formatScanf
    
    call    scanf

    popl    %ebx
    popl    %esi

    movl    (%esi), %eax        # eax = v[i]

    cmpl    max, %eax           # if(v[i] > max)
    jle     continue

    # v[i] > max
    movl    %eax, max
    xorl    %edx, %edx
    movl    %edx, fr
    
    continue:

    cmpl    max, %eax
    jne     continue1

    incl    fr 

    continue1:

    incl    count

    jmp     for_citire

exit_for_citire:

    pushl   fr
    pushl   max
    push    $formatPrintf
    
    call    printf

    popl    %ebx
    popl    %ebx
    popl    %ebx
    

exit:
    movl    $1, %eax
    xorl    %ebx, %ebx
    int     $0x80
