package example3;

/*
    Heap: aici se aloca efectiv memoria pentru obiecte.
          se afla obiectele care pot fi dealocate
          heap-ul este unul singur
    Referintele se stocheaza in stack
    Obiectele in sine se aloca in heap(tot ce tine de o instanta se duce in heap)

    Heap-ul are mai multe zone: 1. EDEN  ====> aici se instantiaza prima data un obiect( se creeaza)
                                2. SURVIVAL 0 ====> daca garbage collector-ul nu curata obiectele din eden, acestea ajung in S0
                                3. SURVIVAL 1 ====> daca garbage collector-ul nu curata obiectele din S0, acestea ajung in S1
                                4. OLD GENERATION ====> daca garbage collector-ul nu curata obiectele din S1, acestea ajung in Old Generation
                                5. Permanent Generation ===> instante ale tipurilor folosite pt a crea obiecte
 */
public class Example1 {

    public static void main(String[] args) {
        int x = 10;
        Cat c = new Cat();

        Cat c1 = c;

        c = null;

        System.gc(); //gc = garbage collector
                    // tu poti apela functia dar nu iti garanteaza nimeni ca o sa se si ruleze

    }
}
