package Customer;

import Banking.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class Customer {
    private final int customerId;
    private String firstName, lastName, CNP;
    private Date birthDate;
    private String email, phone;
    private Address address;

    public Customer(int customerId, String firstName, String lastName, String CNP, Date birthDate, String email, String phone, Address address) {
        this.customerId = customerId;
        this.firstName = firstName;
        this.lastName = lastName;
        this.CNP = CNP;
        this.birthDate = birthDate;
        this.email = email;
        this.phone = phone;
        this.address = address;
    }

    public Customer(int customerId, Scanner in) throws ParseException {
        this.customerId = customerId;
        this.read(in);
    }

    public Customer(int customerId, ResultSet in) throws SQLException {
        this.customerId = customerId;
        this.read(in);
    }

    public void read(ResultSet in) throws SQLException {
        this.firstName = in.getString("firstName");
        this.lastName = in.getString("lastName");
        this.CNP = in.getString("CNP");
        this.birthDate = in.getDate("birthDate");
        this.email = in.getString("email");
        this.phone = in.getString("phone");
        this.address = new Address(in);
    }

    public void read(Scanner in) throws ParseException {
        System.out.println("First name: ");
        this.firstName = in.nextLine();
        System.out.println("Last name: ");
        this.lastName = in.nextLine();
        System.out.println("CNP: ");
        this.CNP = in.nextLine();
        System.out.println("Birth Date (yyyy-MM-dd): ");
        this.birthDate = new SimpleDateFormat("yyyy-MM-dd").parse(in.nextLine());
        System.out.println("Email: ");
        this.email = in.nextLine();
        System.out.println("Phone: ");
        this.phone = in.nextLine();
        System.out.println("Address: ");
        this.address = new Address(in);
    }

    public List<Account> filterAccounts(List<Account> allAccounts){
        var accounts = new ArrayList<Account>();
        for(var account: allAccounts)
            if(account.getCustomerId() == this.getCustomerId())
                accounts.add(account);
        return accounts;
    }

    public List<Transaction> filterTransactions(List<Account> allAccounts, List<Transaction> allTransactions){
        var transactions = new ArrayList<Transaction>();
        var accounts = this.filterAccounts(allAccounts);
        for(var account: accounts)
            transactions.addAll(account.filterTransactions(allTransactions));
        return transactions;
    }

    public List<Transaction> filterTransactions(List<Account> allAccounts, List<Transaction> allTransactions, int year){
        var transactions = new ArrayList<Transaction>();
        var accounts = this.filterAccounts(allAccounts);
        for(var account: accounts)
            transactions.addAll(account.filterTransactions(allTransactions, year));
        return transactions;
    }

    @Override
    public String toString() {
        return "{" +
                "customerId=" + customerId +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", CNP='" + CNP + '\'' +
                ", birthDate=" + (new SimpleDateFormat("yyyy-MM-dd")).format(birthDate) +
                ", email='" + email + '\'' +
                ", phone='" + phone + '\'' +
                ", address=" + address.toString() +
                '}';
    }

    public String toCSV(){
        return customerId +
                "," + firstName +
                "," + lastName +
                "," + CNP +
                "," + (new SimpleDateFormat("yyyy-MM-dd")).format(birthDate) +
                "," + email +
                "," + phone +
                "," + address.toCSV();
    }


    public int getCustomerId() {
        return customerId;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getCNP() {
        return CNP;
    }

    public void setCNP(String CNP) {
        this.CNP = CNP;
    }

    public Date getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(Date birthDate) {
        this.birthDate = birthDate;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public Address getAddress() {
        return address;
    }

    public void setAddress(Address address) {
        this.address = address;
    }
}
