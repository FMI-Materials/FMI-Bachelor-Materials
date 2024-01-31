package streams.Example2;

import java.util.List;

//map si flat maps
public class Example2 {

    public static void main(String[] args) {
        //map ne ajuta sa schimbam tipul

        List<String> list = List.of("abcd", "efgh", "asgnfsad");


        list.stream() //"abcd", "efgh", "asgnfsad"
                   .map(s -> new StringBuilder(s).reverse())  // "dcba"...
                   .forEach(s -> System.out.println(s.toString()));

    }
}
