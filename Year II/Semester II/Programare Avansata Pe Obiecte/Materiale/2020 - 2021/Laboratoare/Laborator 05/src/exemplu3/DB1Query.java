package exemplu3;

public class DB1Query implements Runnable {

    @Override
    public void run() {
        try {
            Thread.sleep(3000);
            System.out.println("DB query 1 ended....");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
