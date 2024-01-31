package Banking;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class SavingsAccountDatabase {
    Connection connection;

    public SavingsAccountDatabase(Connection connection) {
        this.connection = connection;
    }

    public List<SavingsAccount> read(){
        List<SavingsAccount> savingsAccounts = new ArrayList<>();
        try{
            Statement statement = connection.createStatement();
            ResultSet result = statement.executeQuery("SELECT * FROM SavingsAccounts");
            while(result.next()) {
                SavingsAccount current = new SavingsAccount(result);
                savingsAccounts.add(current);
            }
            statement.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
        return savingsAccounts;
    }

    public void update(SavingsAccount newSavingsAccount){
        try{
            String query = "UPDATE SavingsAccounts SET amount = ?, name = ?, customerId = ?, startDate = ?, endDate = ?, interest = ? WHERE IBAN = ? AND swift = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setDouble(1, newSavingsAccount.getAmount());
            preparedStmt.setString(2, newSavingsAccount.getName());
            preparedStmt.setInt(3, newSavingsAccount.getCustomerId());
            preparedStmt.setString(4, (new SimpleDateFormat("yyyy-MM-dd")).format(newSavingsAccount.getStartDate()));
            preparedStmt.setString(5, (new SimpleDateFormat("yyyy-MM-dd")).format(newSavingsAccount.getEndDate()));
            preparedStmt.setInt(6, newSavingsAccount.getInterest());
            preparedStmt.setString(7, newSavingsAccount.getIBAN());
            preparedStmt.setString(8, newSavingsAccount.getSwift());
            preparedStmt.executeUpdate();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void create(SavingsAccount savingsAccount){
        try{
            String query = "INSERT INTO SavingsAccounts (IBAN, swift, amount, name, customerId, startDate, endDate, interest) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, savingsAccount.getIBAN());
            preparedStmt.setString(2, savingsAccount.getSwift());
            preparedStmt.setDouble(3, savingsAccount.getAmount());
            preparedStmt.setString(4, savingsAccount.getName());
            preparedStmt.setInt(5, savingsAccount.getCustomerId());
            preparedStmt.setString(6, (new SimpleDateFormat("yyyy-MM-dd")).format(savingsAccount.getStartDate()));
            preparedStmt.setString(7, (new SimpleDateFormat("yyyy-MM-dd")).format(savingsAccount.getEndDate()));
            preparedStmt.setInt(8, savingsAccount.getInterest());
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void delete(SavingsAccount savingsAccount){
        try{
            String query = "DELETE FROM SavingsAccounts WHERE IBAN = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, savingsAccount.getIBAN());
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
}
