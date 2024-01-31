package exemplu4;

public class Consumer extends Thread {

    public Consumer(String name) {
        super(name);
    }

    public void run() {
        while(true) { //c1 c2
            if(!ListOfValues.bucket.isEmpty()) { //c1  //c2
                int n = ListOfValues.bucket.get(0); //c1 -> devine blocked pt ca asa decide jvm //c2
                ListOfValues.bucket.remove(0); //c2
                System.out.println(Thread.currentThread().getName() + " took out value " + n + " from the bucket"); //c2
            }
        }
    }
}
