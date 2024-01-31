package exemplu3;

public class DB2Query implements Runnable {

    @Override
    public void run() {
        try {
            Thread.sleep(2000);
            System.out.println("DB query 2 ended....");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}