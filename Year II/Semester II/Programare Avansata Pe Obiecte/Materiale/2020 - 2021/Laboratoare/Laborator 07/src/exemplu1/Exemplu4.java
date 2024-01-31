package exemplu1;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;

public class Exemplu4 {

    public static void main(String[] args) {

        //writer

        try {
            Writer writer = new FileWriter("test1.txt");
            BufferedWriter out = new BufferedWriter(writer);
            out.write("Hello World");
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
