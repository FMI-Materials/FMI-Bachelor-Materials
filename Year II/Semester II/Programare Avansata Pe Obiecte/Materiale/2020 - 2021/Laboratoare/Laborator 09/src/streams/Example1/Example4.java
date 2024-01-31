package streams.Example1;

import java.util.Arrays;
import java.util.List;

public class Example4 {

    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(1,5,6,3,8,9);

        list.stream()
            .forEach(x -> {
                try{
                    m(x);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });

    }

    static void m(int x) throws Exception {
        if (x % 2 == 0 ) {
            throw new Exception(" ");
        }
    }
}
