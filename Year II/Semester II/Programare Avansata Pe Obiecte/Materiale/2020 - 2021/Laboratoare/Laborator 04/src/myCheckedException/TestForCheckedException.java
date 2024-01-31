package myCheckedException;

public class TestForCheckedException {
    public static void main(String[] args) throws MyFirstCheckedException {
        MyFirstCheckedException ex = new MyFirstCheckedException();

        throw ex;
    }
}
