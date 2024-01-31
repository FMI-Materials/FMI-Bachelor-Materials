package exemplu1;

import java.util.ArrayList;
import java.util.List;

/*
        synchronized(Object object)
        -> se executa blocul acela de cod care are synchronizied fara intreruperi
        -> din moment ce un thread acceseaza blocul de cod care este synchronized,
                                celelalte threaduri vor fi nevoite sa astepte pana acesta se termina
        Cum folosim synchronized?
            -> Mai intai avem nevoie sa stabilim blocul de cod care va fi folosit
            -> Avem nevoie apoi de un obiect care poate fi orice obiect
            -> Orice obiect din java poate fi un monitor
            -> Trebuie gasit un monitor care sa fie comun pentru producer si consumer
            -> Daca folosim this in synchronized(), practic vom sincroniza blocul de cod cu instanta clasei (nu ne dorim asta acum)

    Object.wait() -> face threadul meu sa astepte (pe monitor)
    Object.notify() -> anunta urmatorul thread ca poate trece in runnable
    Object.notifyAll() -> anunta toate threadurile ca pot trece in runnable
    Urmatorul thread ??? = este decis de catre JVM


 */
public class Main {

    public static List<Integer> bucket = new ArrayList<>();

    public static void main(String[] args) {
        Producer producer = new Producer("producer");
        Producer producer1 = new Producer("producer1");

        Consumer consumer = new Consumer("consumer");
        Consumer consumer1 = new Consumer("consumer1");

        producer.start();
        producer1.start();

        consumer.start();
        consumer1.start();
    }
}
