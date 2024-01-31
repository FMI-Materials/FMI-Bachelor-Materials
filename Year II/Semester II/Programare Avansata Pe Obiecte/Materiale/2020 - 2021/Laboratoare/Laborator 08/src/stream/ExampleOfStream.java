package stream;

import java.util.Arrays;
import java.util.List;

public class ExampleOfStream {

    public static void main(String[] args) {


        List<Integer> list = Arrays.asList(1,2,3,4,5,6,7,8);

//        for(int i : list) {
//            if (i % 2 == 0) {
//                System.out.println(i);
//            }
//        }

        list.stream() //[1,2,3,4,5,6,7,8]
            .filter(x -> x % 2 == 0)  //[2,4,6,8]  Predicate = functional interface
            .forEach(x -> System.out.println(x));  // Consumer 


    }
}