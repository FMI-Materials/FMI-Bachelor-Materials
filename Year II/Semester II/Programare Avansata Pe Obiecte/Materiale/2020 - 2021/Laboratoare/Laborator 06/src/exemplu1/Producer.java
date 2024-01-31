package exemplu1;

import java.util.Random;

public class Producer extends Thread {

    public Producer(String name) {
        super(name);
    }

    @Override
    public void run() {
        Random random = new Random();
        while(true) {
            try {
                synchronized (Main.bucket) {
                    if (Main.bucket.size() < 100) {
                        int n = random.nextInt(1000); //[0,999]
                        Main.bucket.add(n);
                        Main.bucket.notifyAll();
                        System.out.println(Thread.currentThread().getName() + " added value " + n + " into the bucket");
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
