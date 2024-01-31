package exemplu1;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Exemplu5 {

    //reader

    public static void main(String[] args) {

        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("test1.txt")));

            String line = null;
            while( (line = in.readLine()) != null ) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
