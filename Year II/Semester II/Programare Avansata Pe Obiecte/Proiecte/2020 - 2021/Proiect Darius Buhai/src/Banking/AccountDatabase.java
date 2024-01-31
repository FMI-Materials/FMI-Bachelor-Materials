package Banking;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class AccountDatabase {
    Connection connection;

    public AccountDatabase(Connection connection) {
        this.connection = connection;
    }

    public List<Account> read(){
        List<Account> accounts = new ArrayList<>();
        try{
            Statement statement = connection.createStatement();
            ResultSet result = statement.executeQuery("SELECT * FROM Accounts");
            while(result.next()) {
                Account current = new Account(result);
                accounts.add(current);
            }
            statement.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
        return accounts;
    }

    public void update(Account newAccount){
        try{
            String query = "UPDATE Accounts SET amount = ?, name = ?, customerId = ? WHERE IBAN = ? AND swift = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setDouble(1, newAccount.getAmount());
            preparedStmt.setString(2, newAccount.getName());
            preparedStmt.setInt(3, newAccount.getCustomerId());
            preparedStmt.setString(4, newAccount.getIBAN());
            preparedStmt.setString(5, newAccount.getSwift());
            preparedStmt.executeUpdate();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void create(Account account){
        try{
            String query = "INSERT INTO Accounts (IBAN, swift, amount, name, customerId) VALUES (?, ?, ?, ?, ?)";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, account.getIBAN());
            preparedStmt.setString(2, account.getSwift());
            preparedStmt.setDouble(3, account.getAmount());
            preparedStmt.setString(4, account.getName());
            preparedStmt.setInt(5, account.getCustomerId());
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void delete(Account account){
        try{
            String query = "DELETE FROM Accounts WHERE IBAN = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, account.getIBAN());
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
}
