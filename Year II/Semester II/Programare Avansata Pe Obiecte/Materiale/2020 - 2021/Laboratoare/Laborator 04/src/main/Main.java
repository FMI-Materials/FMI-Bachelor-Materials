package main;

/*  marius.scarlat@endava.com
    ->Throwable
                ->Exceptiopn ->checked (trebuie tratate sau aruncate mai departe folosind cuvantul cheie throws in semnatura metodei)
                                    ->mostenesc direct clasa Exception
                                                                    - IOException
                                                                    - SqlException
                                                                    - ClassNotFoundException

                             ->unchecked (sunt de runtime)
                                    -> mostenesc direct sau indirect clasa RuntimeException
                                                                    - ArithmeticException
                                                                    - NullPointerException
                                                                    - NumberFormatException
                ->Error == situatii negative pe care nu le putem trata in cod. (trebuie sa modificam logica)
                        -OutOfMemoryError
                        -StackOverflowError

               Modul de tratare al exceptiilor -> folosind throws care arunca exceptia
                                                mai departe si metoda urmatoare o sa trebuiasca sa trateze/arunce mai departe exceptia
                                                (throws)
                                               -> try -> catch -> finally
                                               ->try {} -> catch(ex1) -> catch(ex2) -> ... ->finally

                a() -> b() -> c()
 */
public class Main {

    public static void main(String args[]) {
        try {
            throw new NullPointerException();
        } catch(NullPointerException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            System.out.println("end of the program");
        }
        int x = 10/0;

        System.out.println(x);

//        throw new Exception();
    }
}
