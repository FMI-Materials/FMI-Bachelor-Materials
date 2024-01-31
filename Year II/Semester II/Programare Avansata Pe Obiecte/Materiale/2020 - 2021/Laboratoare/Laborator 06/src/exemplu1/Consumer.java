package exemplu1;

public class Consumer extends Thread {

    public Consumer(String name) {
        super(name);
    }

    @Override
    public void run() {
        while(true) {
            try {
                synchronized (Main.bucket) {
                    if (Main.bucket.size() != 0) { // Main.bucket.isEmpty()
                        int n = Main.bucket.get(0);
                        Main.bucket.remove(0);
                        Main.bucket.notifyAll();
                        System.out.println(Thread.currentThread().getName() + " took out value " + n + " from the bucket");
                    } else {
                        Main.bucket.wait();
                    }
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }

    }
}
