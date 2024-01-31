package exemplu1;


/*
        Threads in java
                - putem sa cream un thread prin extinderea clasei Thread
                    -> pentru a porni un thread, avem metoda .start() (!!!!)
                - putem implementa interfata Runnable

Thread life cycle:
 NEW ---.start()----> RUNNABLE -------> RUNNING -----terminare instructiuni-----> DEAD
                                                                     ------.sleep(), .wait()---------> BLOCKED ------>RUNNABLE----> RUNNING --->DEAD(HAPPY FLOW)
                                                                                                               ---InterruptedException--->DEAD
        Avantaje pentru implementare Runnable si mostenire Thread
                - cand mostenim Thread, nu mai putem mosteni alte clase si se realizeaza o relatie de tipul is-A (Obiectul meu devine un Thread)
                        pe cand la interfata, obiectul meu nu se modifica, practic devine un task (are metoda run a unui Thread)
                - flexibilitate

*/
public class Exemplu1 {

    public static void main(String []args) {
        NumerePare t1 = new NumerePare("Numere Pare"); //NEW

        t1.start(); //RUNNABLE ----> RUNNING Pentru a porni threadul
        //t1.run();  pentru a rula metoda run din t1 pe threadul main
        System.out.println("END from " + Thread.currentThread().getName());

    }
}

/*
        END 0 2 4 6 8 10
        0 END 2 4 6 8 10
        0 2 END 4 6 8 10
        ...............
        0 2 4 6 8 10 END
 */
