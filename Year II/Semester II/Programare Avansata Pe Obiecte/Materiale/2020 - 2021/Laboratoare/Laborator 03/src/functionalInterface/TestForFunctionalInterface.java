package functionalInterface;

/*
Expresie lambda = folosim sa suprascriem o metoda dintr-o clasa abstracta local
                = implementeaza o singura metoda dintr-o interfata functionala

parameter -> expression
(parameter1, parameter2,...) -> expression
(parameter1, parameter2,...) -> { code block };
 */
public class TestForFunctionalInterface {
    public static void main(String[] args) {
        MyFirstFunctionalInterface myFirstFunctionalInterface = () -> System.out.println("orice");
        MyFirstFunctionalInterface myFirstFunctionalInterface1 = () -> {
            myFirstFunctionalInterface.execute2();
            myFirstFunctionalInterface.execute3();
        };

        myFirstFunctionalInterface.execute();
        myFirstFunctionalInterface1.execute();

    }
}
