package exemplu2;

public class Test {

    public void a() {
            // nu este sincronizat
    }

    public void b() {
        //nesincronizat
        synchronized (this) {
            //
        }
        //nesincronizat
    }

    public synchronized void c() {
        //tot codul este sincronizat
    }
}
