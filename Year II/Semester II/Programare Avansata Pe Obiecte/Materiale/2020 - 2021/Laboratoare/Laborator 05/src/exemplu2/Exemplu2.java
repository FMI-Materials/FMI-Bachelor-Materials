package exemplu2;

public class Exemplu2 {

    public static void main(String[] args) {

        NumereImpare numereImpare1 = new NumereImpare(); //s-a creat o instanta a obiectului NumereImpare
        Thread t1 = new Thread(numereImpare1, "Numere Impare");
        t1.start();

        System.out.println("END " + Thread.currentThread().getName());
    }
}
