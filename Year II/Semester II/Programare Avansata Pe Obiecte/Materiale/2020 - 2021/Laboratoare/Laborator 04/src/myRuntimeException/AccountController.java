package myRuntimeException;

public class AccountController {

    public static final double AMOUNT_OF_MONEY = 100;

    public void withdrawMoney(double amount) {

        if(amount > AMOUNT_OF_MONEY) {
            throw new TooMuchMoneyRuntimeException();
        } else {
            System.out.println("ceva");
        }

    }
}
