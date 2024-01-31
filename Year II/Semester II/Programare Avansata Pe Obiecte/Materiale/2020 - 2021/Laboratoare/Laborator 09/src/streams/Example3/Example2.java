package streams.Example3;

import java.util.*;

public class Example2 {

    public static void main(String[] args) {

        List<String> list = List.of("1r2432amsd", "351kasod", "2104i21asd");

        String digits = "0123456789";

        var x= list.stream() //"1r2432amsd", "351kasod", "2104i21asd"
                    .flatMap(s -> Arrays.stream(s.split(""))) //"1", "r","2", "4"...
                    .filter(c -> digits.contains(c))
                    .count();


        Set<String> set = new HashSet<>();
        set.stream();

        Map<String, String> map = new HashMap<>();

        System.out.println(x);
    }
}
