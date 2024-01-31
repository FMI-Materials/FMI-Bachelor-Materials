package streams.Example2;

import java.util.List;

public class Example3 {

    public static void main(String[] args) {

        //avem mai multe tipuri de map
        //incepem cu un stream
        //map() => stream ---> stream
        //mapToInt() => stream ---> IntStream
        //mapToLong() => stream ---> LongStream
        //mapToDouble => stream ---> DoubleStream

        List<String> list = List.of("abcd", "asdna", "sdwad");

        var x= list.stream()
                    .mapToInt(s -> s.length()) //Stream ==> IntStream
//                    .map(s -> s) //IntStream ==> IntStream
//                    .mapToObj(x -> x)
//                    .mapToInt(x -> x)
                    .sum();

        System.out.println(x);
    }
}
