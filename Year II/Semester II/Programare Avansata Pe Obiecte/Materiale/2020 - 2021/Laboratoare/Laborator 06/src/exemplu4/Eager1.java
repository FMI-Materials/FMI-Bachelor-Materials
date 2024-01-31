package exemplu4;

public class Eager1 {

    private static Eager1 instance = new Eager1();

    private Eager1() {

    }

    public static Eager1 getInstance() {
        return instance;
    }

    public void log() {
        System.out.println("Log");

    }
}
