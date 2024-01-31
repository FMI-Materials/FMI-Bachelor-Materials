package exemplu1;

public class Exemplu1 {

    /*
    Stream = canal de comunicare unidirectional intre 2 endpointuri
           = pe canalul de comunicare datele se trimit sub forma de bytes
           = stau la baza oricarui tool de comunicare(rabbit mq, solace)
    Streams Input = read
    Streams Output = write

    Low Level Streams : InputStream, OutputStream, FileInputStream, FileOutputStream
    High Level Streams : BufferedReader/Writer, ObjectInputStream, ObjectOutputStream, PrintStream, PrintWriter


    Streams sunt resurse. Adica trebuie inchise la final

     Exceptiile aruncate folosind streamuri:
            IOException
            FileNotFoundException (extinde IOException)

      try with resources =>
      try(resource) {

      } catch(Exception e) {e.printStackTrace()}
     */

    public static void main(String[] args) {

        System.out.println(":)");
        //PrintStream => high level stream
    }
}
