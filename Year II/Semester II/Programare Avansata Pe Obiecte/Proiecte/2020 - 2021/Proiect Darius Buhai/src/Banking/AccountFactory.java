package Banking;

public class AccountFactory {

    private static int uniqueId = 0;

    public static void incrementUniqueId(int inc) {
        AccountFactory.uniqueId += inc;
    }

    public Account createAccount(String name, int customerId){
        return new Account(name, customerId, uniqueId++);
    }

    public SavingsAccount createSavingsAccount(String name, int customerId){
        return new SavingsAccount(name, customerId, uniqueId++);
    }
}
