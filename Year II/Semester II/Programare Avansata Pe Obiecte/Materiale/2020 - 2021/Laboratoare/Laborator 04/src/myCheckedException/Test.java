package myCheckedException;

public class Test {

    public static void main(String[] args) {
        AccountController accountController = new AccountController();
        try {
            accountController.withdraw(150);
        } catch (TooMuchMoneyCheckedException e) {
            e.printStackTrace();
        }
//        try {
//            accountController.withdraw(150);
//        } catch (TooMuchMoneyCheckedException e) {
//            e.printStackTrace();
//        }
    }
}
