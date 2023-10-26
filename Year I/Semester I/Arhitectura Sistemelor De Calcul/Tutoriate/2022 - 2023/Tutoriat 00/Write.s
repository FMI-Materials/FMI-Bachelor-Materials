# Resurse de baza assembly: https://flint.cs.yale.edu/cs421/papers/x86-asm/asm.html
# Mai multe informatii despre registri: https://www.swansontec.com/sregisters.html
# Si mai multe informatii (nu sunt absolut deloc necesare): https://qr.ae/pvVAnb

.data 
	str: .asciz "HW"
.text
.globl main

main:
	mov $4, %eax # Pentru functia scriere
	mov $1, %ebx # Parametrul1 - 1 = stdout
	mov $str, %ecx # Parametrul2 = adresa stringului
	mov $3, %edx # Parametrul3 = lungimea sirului (inclusiv terminatorul de sir '\0')
	int $0x80

	mov $1, %eax # Pentru exit
	xorl %ebx, %ebx # %ebx devine 0 prin xorare <=> mov $0, %ebx
	int $0x80
	
# Pentru a rula:
#
# gcc -m32 write.s -o write -no-pie
#
# Probabil parametrul -no-pie nu a fost predat, dar va poate da un warning in functie de versiunea de Ubuntu pe care o aveti instalata. E destul de greu de inteles cu cunostintele de pana acum (si in anul 2 la fel ;) ), dar aveti aici mai multe detalii in caz ca va intereseaza: https://stackoverflow.com/questions/43367427/32-bit-absolute-addresses-no-longer-allowed-in-x86-64-linux
