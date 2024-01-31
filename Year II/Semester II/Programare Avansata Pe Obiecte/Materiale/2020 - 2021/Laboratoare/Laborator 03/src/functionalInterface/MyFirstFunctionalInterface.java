package functionalInterface;
/*
Interfata = o clasa pur abstracta care este privita ca un contract. Adica clasa x care implementeaza interfata y o sa stie sa faca tot ce este in y.
            (defineste ce poate face un obiect si nu ceea ce este obiectul respectiv)
interfata functionala = -interfata cu o singura metoda abstracta
                        -putem avea oricate metode concrete DAR una singura abstracta
@FunctionalInterface = anunta programatorul si compilatorul ca interfata este functionala pentru a nu mai adauga alte metode abstracte
 */
@FunctionalInterface
public interface MyFirstFunctionalInterface {

    void execute();

    default void execute2() {
        System.out.println("orice dar din execute2");
    }

    default void execute3() {
        System.out.println("orice din execute3");
        execute2();
        execute();
    }

}
