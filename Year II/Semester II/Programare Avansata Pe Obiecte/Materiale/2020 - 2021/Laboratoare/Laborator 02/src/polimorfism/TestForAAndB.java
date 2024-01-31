package polimorfism;

public class TestForAAndB {

    public static void main(String[] args) {

        A a1 = new B();
        B b1 = (B) a1;

        b1.x = "String";

        a1.nr = 3;


        B b2 = new B();
        b2.x = "SECOND";

        B b3 = b2;
        System.out.println(b1.nr);

    }
}
