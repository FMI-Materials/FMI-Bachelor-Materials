package example1;

import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class Example3 {

    public static void main(String[] args) {
        List<String> list = List.of("AAA", "B", "CCCCC", "DDD", "FFFFFF", "B");

        Map<String, Integer> res = list.stream()
                                        .collect(Collectors.toMap(
                                                s -> s,
                                                s -> s.length(),
                                                (a,b) -> a + b
                                        ));

        System.out.println(res);

        TreeMap<String, Integer> res1 = list.stream()
                .collect(Collectors.toMap(
                        s -> s,
                        s -> s.length(),
                        (a,b) -> a + b,
                        () -> new TreeMap<>()
                ));

        System.out.println(res1);


    }
}
