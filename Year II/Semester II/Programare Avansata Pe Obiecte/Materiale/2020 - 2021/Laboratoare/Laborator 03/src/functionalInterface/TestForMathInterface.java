package functionalInterface;

public class TestForMathInterface {

    public static void main(String[] args) {
//        int a = 5;
        MathFunctionalInterface mathFunctionalInterface1 = (int a, int b) -> {

            if (a > b) {
                return a - b;
            } else if (b > a) {
                return b - a;
            } else {
                System.out.println("sunt egale");
                return 0;
            }
        };

        MathFunctionalInterface mathFunctionalInterface2 = ( int a, int b) -> a * b;

        MathFunctionalInterface mathFunctionalInterface3 = (int a, int b) -> {
            if (a != 0) {
                return b / a;
            } else if (b != 0) {
                return a / b;
            } return 0;
        };

        System.out.println(doSmth(5, 5, mathFunctionalInterface1));
        System.out.println(doSmth(5, 5, mathFunctionalInterface2));
        System.out.println(doSmth(5, 5, mathFunctionalInterface3));

    }

    public static int doSmth(int a, int b, MathFunctionalInterface mathFunctionalInterface) {

        return mathFunctionalInterface.calculate(a, b);
    }


}
