package streams.Example1;

import java.util.Random;
import java.util.function.Supplier;
import java.util.stream.Stream;

public class Example2 {

    public static void main(String[] args) {

        Stream<Integer> stream1 = Stream.empty(); //sursa finita

        Stream<Integer> stream2 = Stream.of(1,2,3,4,5,6,7,8,9); //sursa finita
//        stream2.filter(x -> x % 2 != 0).forEach(x -> System.out.println(x));


        Supplier<Integer> supplier = () -> new Random().nextInt();
        Stream<Integer> stream3 = Stream.generate(supplier); //sursa infinita
        stream3.limit(10).forEach(x -> System.out.println(x));
    }
}
