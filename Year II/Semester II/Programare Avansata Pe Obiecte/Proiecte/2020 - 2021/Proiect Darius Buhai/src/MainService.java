import Banking.*;
import Customer.Customer;
import Customer.CustomerFactory;
import Customer.CustomerDatabase;

import java.text.ParseException;
import java.util.*;

public class MainService {

    /// Storage
    private List<Customer> customers = new ArrayList<>();
    private List<Account> accounts = new ArrayList<>();
    private List<SavingsAccount> savingsAccounts = new ArrayList<>();
    private List<Transaction> transactions = new ArrayList<>();

    private final Map<String, Account> accountsMap = new HashMap<>();
    private final CustomerFactory customerFactory = new CustomerFactory();
    private final AccountFactory accountFactory = new AccountFactory();

    private CustomerDatabase customerDatabase = null;
    private TransactionDatabase transactionDatabase = null;
    private AccountDatabase accountDatabase = null;
    private SavingsAccountDatabase savingsAccountDatabase = null;

    /// Getters
    public List<Customer> getCustomers() {
        return customers;
    }
    public List<Account> getAccounts() {
        return accounts;
    }
    public List<SavingsAccount> getSavingsAccounts() {
        return savingsAccounts;
    }
    public List<Transaction> getTransactions() {
        return transactions;
    }

    /// Setters
    public void setCustomers(List<Customer> customers){
        this.customers = customers;
    }
    public void setAccounts(List<Account> accounts) {
        this.accounts = accounts;
    }
    public void setSavingsAccounts(List<SavingsAccount> savingsAccounts) {
        this.savingsAccounts = savingsAccounts;
    }
    public void setTransactions(List<Transaction> transactions) {
        this.transactions = transactions;
    }

    public MainService(CustomerDatabase customerDatabase, TransactionDatabase transactionDatabase, AccountDatabase accountDatabase, SavingsAccountDatabase savingsAccountDatabase) {
        this.customerDatabase = customerDatabase;
        this.transactionDatabase = transactionDatabase;
        this.accountDatabase = accountDatabase;
        this.savingsAccountDatabase = savingsAccountDatabase;

        this.customers = customerDatabase.read();
        this.transactions = transactionDatabase.read();
        this.accounts = accountDatabase.read();
        this.savingsAccounts = savingsAccountDatabase.read();

        this.linkAccounts();
    }

    public MainService(){ }

    /// Utils
    private Customer getCustomerFromInput(Scanner in) throws Exception{
        if(this.customers.size()==0)
            throw new Exception("No customers added!");
        if(this.customers.size()==1)
            return customers.get(0);
        System.out.println("Customer id [0-"+(this.customers.size()-1)+"]: ");
        int customerId = Integer.parseInt(in.nextLine());
        return customers.get(customerId);
    }

    public void linkAccounts(){
        for(var account: this.accounts)
            this.accountsMap.put(account.getIBAN(), account);
    }

    /// Actions
    public void createCustomer(Scanner in) throws ParseException {
        Customer newCustomer = customerFactory.createCustomer(in);
        this.customers.add(newCustomer);
        var newAccount = accountFactory.createAccount(newCustomer.getFirstName() + " " + newCustomer.getLastName(), newCustomer.getCustomerId());
        this.accounts.add(newAccount);
        if(this.customerDatabase!=null)
            this.customerDatabase.create(newCustomer);
        if(this.accountDatabase!=null)
            this.accountDatabase.create(newAccount);
        System.out.println("Customer created");
    }

    public void getCustomer(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        System.out.println(customer.toString());
    }

    private Account getAccountFromInput(Scanner in, Customer customer) throws Exception {
        List<Account> customersAccounts = customer.filterAccounts(this.accounts);
        System.out.println("Customer accounts: " + customersAccounts);
        System.out.println("Choose IBAN: ");
        var IBAN = in.nextLine();
        if(!this.accountsMap.containsKey(IBAN))
            throw new Exception("Invalid IBAN number!");
        var account = accountsMap.get(IBAN);;
        if(account.getCustomerId() != customer.getCustomerId())
            throw new Exception("The given IBAN number is not associated with the selected customer");
        return account;
    }

    public void getCustomerAmount(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        var customerAccounts = customer.filterAccounts(this.accounts);
        double totalAmount = 0;
        for(var account: customerAccounts)
            totalAmount += account.getAmount();
        System.out.println(customer.getFirstName() + " " + customer.getLastName() + " has a total amount of: " + totalAmount + " lei in his accounts.");
    }

    public void getCustomerAccounts(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        List<Account> customersAccounts = customer.filterAccounts(this.accounts);
        System.out.println(customersAccounts.toString());
    }

    public void createCustomerAccount(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        System.out.println("Account name: ");
        String name = in.nextLine();
        Account newAccount = this.accountFactory.createAccount(name, customer.getCustomerId());
        accounts.add(newAccount);
        accountsMap.put(newAccount.getIBAN(), newAccount);
        if(this.accountDatabase!=null)
            this.accountDatabase.create(newAccount);
        System.out.println("Account created");
    }

    public void createCustomerSavingsAccount(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        System.out.println("Savings Account name: ");
        String name = in.nextLine();
        SavingsAccount newSavingsAccount = this.accountFactory.createSavingsAccount(name, customer.getCustomerId());
        this.savingsAccounts.add(newSavingsAccount);
        if(this.savingsAccountDatabase!=null)
            this.savingsAccountDatabase.create(newSavingsAccount);
        System.out.println("Savings Account created");
    }

    public void createCustomerCard(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        var account = this.getAccountFromInput(in, customer);
        System.out.println("Card Holder name: ");
        var name = in.nextLine();
        account.addCard(name);
    }

    public void loadCustomerAccount(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        System.out.println("How much do you want to load into your account?: ");
        int amount = Integer.parseInt(in.nextLine());
        var customerAccounts = customer.filterAccounts(this.accounts);
        customerAccounts.get(0).setAmount(amount);
        System.out.println("The account has been loaded!");
    }

    public void createTransaction(Scanner in) throws Exception {
        System.out.println("From account (IBAN): ");
        var IBAN1 = in.nextLine();
        System.out.println("To account (IBAN): ");
        var IBAN2 = in.nextLine();
        System.out.println("Amount: ");
        int amount = in.nextInt();
        System.out.println("Description: ");
        var description = in.nextLine();

        Account account1 = null, account2 = null;

        if(accountsMap.containsKey(IBAN1))
            account1 = accountsMap.get(IBAN1);
        if(accountsMap.containsKey(IBAN2))
            account2 = accountsMap.get(IBAN2);

        if(IBAN1.equals(IBAN2))
            throw new Exception("Cannot send transaction to same account");
        if(account1==null || account2==null)
            throw new Exception("Cannot find IBAN numbers!");
        if(account1.getAmount() < amount)
            throw new Exception("Insufficient founds!");

        account1.setAmount(account1.getAmount() - amount);
        account2.setAmount(account2.getAmount() + amount);

        var newTransaction = new Transaction(IBAN1, IBAN2, amount, description);
        this.transactions.add(newTransaction);
        if(this.transactionDatabase!=null)
            this.transactionDatabase.create(newTransaction);
        if(this.accountDatabase!=null){
            this.accountDatabase.update(account1);
            this.accountDatabase.update(account2);
        }
        System.out.println("Transaction finished");
    }

    public void closeAccount(Scanner in) throws Exception {
        var customer = this.getCustomerFromInput(in);
        var account = this.getAccountFromInput(in, customer);

        if(customer.filterAccounts(this.accounts).size()<=1)
            throw new Exception("There has to be at least one bank account associated with the user!");
        if(account.getAmount()!=0)
            throw new Exception("The account savings are not empty!");
        this.accountsMap.remove(account.getIBAN());
        this.accounts.remove(account);
        if(this.accountDatabase!=null)
            this.accountDatabase.delete(account);
        System.out.println("Account closed!");
    }

    public void getCustomerAccount(Scanner in) throws Exception{
        var customer = this.getCustomerFromInput(in);
        var account = this.getAccountFromInput(in, customer);
        System.out.println(account.toString());
    }

    public void getCustomerTransactions(Scanner in) throws Exception{
        var customer = this.getCustomerFromInput(in);
        System.out.println("Show all transactions? (y/n)");
        String showAll = in.nextLine();
        if(showAll.equals("y")) {
            System.out.println(customer.filterTransactions(accounts, transactions));
        }
        else{
            System.out.println("Select year: ");
            var year = in.nextInt();
            System.out.println(customer.filterTransactions(accounts, transactions, year));
        }
        System.out.println();
    }

}
