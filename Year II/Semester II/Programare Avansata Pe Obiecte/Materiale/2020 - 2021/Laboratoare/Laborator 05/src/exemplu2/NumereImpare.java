package exemplu2;

public class NumereImpare implements Runnable {

    @Override
    public void run() {
        for(int i=1;i<=11;i+=2) {
//            System.out.println(i);
            System.out.println(Thread.currentThread().getName() + " " + i);
        }
    }
}
