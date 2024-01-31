package example2;

/* Stack si Heap

    Stack = variabilele locale se afla in stack
          = last in first out (LIFO)
          = fiecare thread are stackul propriu

    Heap = datele declarate
 */

public class Example1 {

    public static void main(String[] args) {
        m1();
    }

    static void m1() {
        int x = 10;
        m2();
    }

    static void m2() {
        m3();
        m4();
    }

    static void m3() {
//        m4();
    }

    static void m4() {}
}
