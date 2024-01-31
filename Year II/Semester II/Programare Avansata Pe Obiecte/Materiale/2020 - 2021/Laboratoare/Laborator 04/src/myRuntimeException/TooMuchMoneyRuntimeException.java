package myRuntimeException;

public class TooMuchMoneyRuntimeException extends RuntimeException {

    public TooMuchMoneyRuntimeException() {
        super("You don't have enough money in your account");
    }
}
