package Banking;

import Card.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class Account implements Comparator<Transaction> {
    protected String IBAN;
    protected String swift;
    protected double amount;
    protected String name;
    protected int customerId;

    protected List<Card> cards = new ArrayList<>();

    private final CardFactory cardFactory = new CardFactory();

    public Account(String IBAN, String swift, double amount, String name, int customerId){
        this.IBAN = IBAN;
        this.swift = swift;
        this.amount = amount;
        this.name = name;
        this.customerId = customerId;
    }

    public Account(String name, int customerId, int uniqueId) {
        this.IBAN = this.generateIBAN(uniqueId);
        this.swift = this.generateSwift();
        this.amount = 0;
        this.name = name;
        this.customerId = customerId;
    }

    public Account(ResultSet in) throws SQLException {
        this.IBAN = in.getString("IBAN");
        this.swift = in.getString("swift");
        this.amount = in.getDouble("amount");
        this.name = in.getString("name");
        this.customerId = in.getInt("customerId");
    }

    public List<Transaction> filterTransactions(List<Transaction> allTransactions){
        List<Transaction> transactions = new ArrayList<>();
        for(var transaction: allTransactions)
            if(transaction.getFromIBAN().equals(this.IBAN))
                transactions.add(transaction);
        return transactions;
    }

    public List<Transaction> filterTransactions(List<Transaction> allTransactions, int year){
        List<Transaction> transactions = new ArrayList<>();
        for(var transaction: allTransactions)
            if(transaction.getFromIBAN().equals(this.IBAN) && transaction.getCreationDate().getYear()==year)
                transactions.add(transaction);
        return transactions;
    }

    public void addCard(String name){
        Card newCard = cardFactory.addCard(this.IBAN, name);
        cards.add(newCard);
    }

    public int compare(Transaction transaction1, Transaction transaction2){
        return transaction1.getCreationDate().compareTo(transaction2.getCreationDate());
    }

    public String getName() {
        return name;
    }

    public int getCustomerId() {
        return customerId;
    }

    public void setAmount(double amount) {
        this.amount = amount;
    }

    public String getIBAN() {
        return IBAN;
    }

    public String getSwift() {
        return swift;
    }

    public double getAmount() {
        return amount;
    }

    public List<Card> getCards() {
        return cards;
    }

    @Override
    public String toString() {
        return "Account{" +
                "IBAN='" + IBAN + '\'' +
                ", swift='" + swift + '\'' +
                ", amount=" + amount +
                ", name='" + name + '\'' +
                ", customerId=" + customerId +
                '}';
    }

    public String toCSV() {
        return IBAN +
                "," + swift +
                "," + amount +
                "," + name +
                "," + customerId;
    }

    private String generateIBAN(int uniqueId){
        String bank = "BRD";

        return "RO06" + bank + "B" + uniqueId;
    }

    private String generateSwift(){
        String bank = "BRD";

        return "SWIFT" + bank + "B";
    }
}
