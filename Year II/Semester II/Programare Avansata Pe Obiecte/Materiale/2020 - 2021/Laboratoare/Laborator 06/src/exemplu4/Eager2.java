package exemplu4;

public class Eager2 {

    private static Eager2 instance = new Eager2();

    private Eager2() {
        while (true) {
            Eager1.getInstance().log();
            System.out.println(Eager2.getInstance());
        }
    }

    public static Eager2 getInstance() {
        return instance;
    }
}
