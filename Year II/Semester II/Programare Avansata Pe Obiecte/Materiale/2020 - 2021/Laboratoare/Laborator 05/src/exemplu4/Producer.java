package exemplu4;

import java.util.Random;

public class Producer extends Thread {

    public Producer(String name) {
        super(name);
    }

    public void run() {
        Random random = new Random();
        //lista noastra poate avea maximum 100 de elemente
        while(true) {    // c1
            if(ListOfValues.bucket.size() < 100) { //c1
                int n = random.nextInt(1000); // [0,999]
                ListOfValues.bucket.add(n);

                System.out.println(Thread.currentThread().getName() + " added value " + n + " to the bucket" );
            }
        }
    }
}
