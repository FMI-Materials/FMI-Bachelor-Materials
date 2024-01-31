package polimorfism;

public class B extends A{
    String x;

    void m() {
        super.m();
        System.out.println("Inside class B");
    }
}
