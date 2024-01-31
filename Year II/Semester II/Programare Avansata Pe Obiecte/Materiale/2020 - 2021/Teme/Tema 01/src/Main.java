import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    private static Scanner getFileInput() throws FileNotFoundException {
        File myObj = new File("example.txt");
        return new Scanner(myObj);
    }

    private static Scanner getKeyboardInput(){
        return new Scanner(System.in);
    }

    public static void main(String[] args) {
        try{
            Scanner in = getFileInput();
            Tournament tournament = new Tournament(in);
            tournament.show();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
}
