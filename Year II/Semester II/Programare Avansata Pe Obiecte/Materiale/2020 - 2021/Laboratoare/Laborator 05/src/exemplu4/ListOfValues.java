package exemplu4;

import java.util.ArrayList;
import java.util.List;

public class ListOfValues {

    public static List<Integer> bucket = new ArrayList<>();

    public static void main(String[] args) {
        // un producer de numere
        // un consumer de numere
        //ambele ruleaza in paralel

        Consumer consumer = new Consumer("Consumer1");
        Producer producer = new Producer("Producer1");

        Consumer consumer1 = new Consumer("Consumer2");
        Producer producer2 = new Producer("Producer2");

        consumer.start();
        consumer1.start();

        producer.start();
        producer2.start();
    }
}
