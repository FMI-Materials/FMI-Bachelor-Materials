package exemplu1;

public class NumerePare extends Thread {

    public NumerePare(String name) {
        super(name);
    }

    @Override
    public void run() {
        for (int i=0; i<=10; i+=2) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
            System.out.println(i + " from Thread " + Thread.currentThread().getName());
        }
    }
}
