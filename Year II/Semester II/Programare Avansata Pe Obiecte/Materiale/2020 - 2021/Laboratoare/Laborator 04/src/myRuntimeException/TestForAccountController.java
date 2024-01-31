package myRuntimeException;

public class TestForAccountController {

    public static void main(String[] args) {
        var accountController = new AccountController();

        accountController.withdrawMoney(150);
    }
}
