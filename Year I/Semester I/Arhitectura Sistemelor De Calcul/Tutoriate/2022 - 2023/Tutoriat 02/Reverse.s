#   Afisati inversul unui sir!

.data
    s:      .space 50
    cpy:    .space 50
    len:    .space 4
    index:  .space 4
    n:      .long 50
    stdin:  .asciz "stdin"
.text

.globl main

main:

    pushl   $s              # pun pe stiva adresa lui s (sir de caractere)
    call    gets            
    popl    %ebx            # optional doar in cazul asta
    
    pushl   $s              # optional doar in cazul asta
    call    strlen
    popl    %ebx           

    movl    %eax, len       # in eax a fost returnata lungimea sirului s  
    decl    %eax            # eax = len - 1 
    movl    %eax, index     # index = len - 1

    xorl    %ecx, %ecx      # ecx = 0
    
    lea     s, %esi         # esi = &s
    lea     cpy, %edi       # edi = &cpy

for:
    cmpl    len, %ecx       # 
    je      exit_for        # 

    movl    index, %ebx     # 
    movb    (%esi, %ebx, 1), %al        # al = s[inedx] 
    
    movb    %al, (%edi, %ecx, 1)        # cpy[i] = s[index] 
    
    incl    %ecx
    decl    index

    jmp     for

exit_for:
    movb    $0, %al 
    movb    %al, (%edi, %ecx, 1)        # cpy[i] = s[index] 

    push    $cpy
    call    puts
    popl    %ebx

exit:
    movl    $1, %eax
    xorl    %ebx, %ebx
    int     $0x80
