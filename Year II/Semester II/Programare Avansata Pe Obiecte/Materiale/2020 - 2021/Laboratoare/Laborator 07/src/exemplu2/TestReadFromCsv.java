package exemplu2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class TestReadFromCsv {

    public static void main(String[] args) {

        try(var in = new BufferedReader(new FileReader("csvtext.txt"))) {

        String line = "";
        List<Person> personList = new ArrayList<>();

        while( (line = in.readLine()) != null ) {
            String []fields = line.replaceAll(" ", "").split(",");
            Person p = new Person(fields[0], Integer.parseInt(fields[1]));
            //personList.add(p);
        }
        for(Person p : personList) {
            System.out.println(p.toString());
        }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
