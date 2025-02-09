Program:
- set de instructiuni 
- entitate pasiva
- reprezentat prin fisiere executabile (ELF)

Procesul:
- entitate activa
- programul in executie 
- reprezinta imaginea programului in memoria principala(RAM)

Cand vreau sa execut un proces, se creaza un PCB, care contine:
- pointer
- process state-ul
- process counter
- process number
- registers
- list of open files

Fiecare PCB nu stie de memoria fizica, este translatat intr-un proces cu memorie virtualizata:
- stack/ heap
- .text - zona executabila
- .data - date initializa
- data neintializate

MMU - memory management unit - mapeaza adrese virtuale la cele fizice

context switching

IPC
IPC SystemV
POSIX - apelurile de sistem/kernel

Metode de comunicare:
- pipes
- messages queues
- semaphores
- shared memory

C
- unistd.h - functiiile POSIX
Procesul poate fi in:
- user mode: probleme standard
- kernel mode: apeluri de sistem

pid_t getpid()
pid_t getppid()
pid_t fork()

int main(int argc, char* argv[], char* arge[])
arge - environment


daca semaforul este mai mic decat 0, face procesul blocant


