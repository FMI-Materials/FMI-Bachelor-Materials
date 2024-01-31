package exemplu3;

public class DBProcess {

    public static void main(String[] args) {

        //query 1 dureaza 3 secunde
        //query 2 dureaza 2 secunda
        //daca ar rula pe acelasi thread => 5 secunde
        //daca ruleaza pe threaduri paralele => max(2,3) => 3 secunde

        //Trebuie sa ma asigur ca in momentul in care facem procesarea, cele 2 query-uri trebuie sa se fi terminat (lucram cu 3 threaduri)

        DB1Query db1 = new DB1Query();
        DB2Query db2 = new DB2Query();

        Thread t1 = new Thread(db1, "DB1 thread");
        Thread t2 = new Thread(db2, "DB2 thread");

        t1.start();
        t2.start();

        //t1.setPriority(); 1 -> 10 default este 5

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Processing.... " + Thread.currentThread().getName());

    }
}
