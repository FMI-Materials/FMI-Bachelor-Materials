package streams.Example2;

import java.util.List;

//map si flat maps
public class Example1 {

    public static void main(String[] args) {
        //map ne ajuta sa schimbam tipul

        List<String> list = List.of("abcd", "efgh", "asgnfsad");

        //suma tuturor lungimilor stringurilor

        var x =list.stream() //"abcd", "efgh", "asgnfsad"
                   .map(s -> s.length())  // 4 4 8
                   .reduce(0, (a,b) -> a + b); // 0 + 4 = 4; 4 + 4 = 8; 8 + 8 = 16;
        System.out.println(x);
    }
}
