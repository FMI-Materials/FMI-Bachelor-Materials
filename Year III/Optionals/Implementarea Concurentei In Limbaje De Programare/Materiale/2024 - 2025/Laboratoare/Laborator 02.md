Multithreading

Java - Prod-Cons / Reader-Writer/ Filosofi

Cerinta: vrem ca doua procese sa comunice printr-un segment de memorie partajata(1 byte)
Tatal pune in seg de memorie caractere de la a-z`
Fiul acceseaza mereu caracterul scris de tata si il afiseaza la stdout


tata:  'a' 'b'
    fiu: 'b' - daca nu facem arbitraj de memorie

IPC - sem, shm, msg 
avem functii de get/set/control

struct sembuf:  
-   sem_num - indexul sem din array
-  sem_op - increment/decrement
-  flag - daca este sau nu blocant

IPC_PRIVATE = se acceseaza doar din ierarhie direct (bunic - tata - fiu)

https://pastebin.com/aQFEu7de


MUltithreading - JAVA

Creere:
 - extends Threads
 - implements Runnable
 - metode anonime - JAVA(23)

Doua threaduri, una face ++, una --, daca nu sunt sincroniztae, rezultatul final != 0

Sincronizare variabile JAVA:
- synchronized pe functie
- variabile atomice
https://pastebin.com/3DxE1DJ8








