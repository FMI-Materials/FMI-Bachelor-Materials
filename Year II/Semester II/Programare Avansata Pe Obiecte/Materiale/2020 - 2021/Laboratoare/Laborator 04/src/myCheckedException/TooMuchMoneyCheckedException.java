package myCheckedException;

public class TooMuchMoneyCheckedException extends Exception{

    public TooMuchMoneyCheckedException() {
        super("Not enough money");
    }
}
