package streams.Example1;

import java.util.Arrays;
import java.util.List;

public class Example3 {

    public static void main(String[] args) {


        //operatii intermediare
        // anyMatch noneMatch allMatch

        List<Integer> list = Arrays.asList(1,5,6,3,8,9);

        boolean b1 = list.stream().anyMatch(x -> x % 2 == 0);   //true
        boolean b2 = list.stream().allMatch(x -> x % 2 == 0);  //false
        boolean b3 = list.stream().noneMatch(x -> x % 2 == 0); //false
    }
}
