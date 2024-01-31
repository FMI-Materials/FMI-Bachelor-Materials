package myCheckedException;

public class AccountController {

    public static final double AMOUNT_OF_MONEY = 100;

    public void withdraw(double amount) throws TooMuchMoneyCheckedException {
        if (amount > AMOUNT_OF_MONEY) {
            throw new TooMuchMoneyCheckedException();
        } else {
            System.out.println("ceva");
        }
    }
}
