#!!!
#
#	ASIGURATI-VA CA MAKEFILE-UL ESTE IN ACELASI FOLDER CU CODUL SURSA
#
#	Pentru a rula codul puteti scrie in consola "make"
#	Pentru a sterge executabilul("helloworld") executati comanda "make clean", vor ramane doar codul sursa("helloworld.s") si fisierul makefile
#	Va recomand sa va faceti un fisier make in aceeasi maniera in situatiile in care trebuie sa compilati un cod de mai multe ori
#!!!	

.data
    s: .asciz "Hello, world!\n"
.text

.global main

main:
    
    #apelam functia de sistem write
    movl    $4, %eax    #   in eax punem codul functiei de sistem pe care o apelam
    
    movl    $1, %ebx    #   primul parametru al functiei write, 1 denota "stdout" (consola);
    #	NU VA RECOMAND, insa codul va rula "corespunzator" si daca puneti 0 sau 2 in %ebx!
    
    lea     s,  %ecx    #   al doilea parametru al functiei write, incarc in registru adresa variabilei s
    #   "lea s,%ecx" este echivalenta cu "movl $s, %ecx"
    movl    $15, %edx   #   ultimul parametru arata cat de mult se scrie in consola, fisier etc.
    
    int     $0x80

fin:    #simpla eticheta

    movl    $1, %eax    #   apelez functia de sistem exit/ return
    xorl    %ebx, %ebx  #   return 0;/ exit(0);
    #   "xorl %ebx, %ebx" este echivalenta cu "movl $0, %ebx"
    int     $0x80
