package example1;

import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Example1 {

    public static void main(String[] args) {
        List<String> list = List.of("AAA", "B", "CCCCC", "DDD", "FFFFFF");

        List<String> res1 = list.stream()
                                 //intermediary operations
                                 .filter(s -> s.length() > 2)
                                 .collect(Collectors.toList());

        Set<String> res2 = list.stream()
                                .collect(Collectors.toSet());

        TreeSet<String> res3 = list.stream()
                                    .collect(Collectors.toCollection(() -> new TreeSet<>())); // TreeSet::new

    }
}
