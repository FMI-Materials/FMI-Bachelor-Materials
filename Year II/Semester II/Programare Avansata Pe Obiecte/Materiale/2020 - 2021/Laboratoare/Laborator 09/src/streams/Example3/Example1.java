package streams.Example3;

import java.util.List;

public class Example1 {

    public static void main(String[] args) {
        //flatMap


        List<List<Integer>>list = List.of(List.of(1,2,3,4,5), List.of(2,3,5,6,8), List.of(4,9,2,4));

        var x = list.stream() //List<Integer> [1,2,3,4,5],[2,3,5,6,8],[4,9,2,4]
                    //.map(y -> y.ad)     //List -> List
                    .flatMap(l -> l.stream()) //Integers [1,2,3,4,5,2,3,5,6,8,4,9,2,4]
                    .reduce(0, (a,b) -> a + b);
        System.out.println(x);
    }
}
