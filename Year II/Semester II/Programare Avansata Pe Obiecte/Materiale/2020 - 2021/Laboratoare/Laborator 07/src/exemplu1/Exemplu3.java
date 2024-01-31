package exemplu1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Exemplu3 {

    public static void main(String[] args) {
//        BufferedReader in = new BufferedReader(new InputStreamReader(System.in))
//        try (in) {
//            String line = in.readLine();
//            System.out.println(line);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }


        //works with java9+

        try (var in = new BufferedReader(new InputStreamReader(System.in))) {
            String line = in.readLine();
            System.out.println(line);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
