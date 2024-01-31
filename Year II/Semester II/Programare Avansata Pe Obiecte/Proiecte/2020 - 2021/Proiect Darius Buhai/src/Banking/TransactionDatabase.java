package Banking;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class TransactionDatabase {
    Connection connection;

    public TransactionDatabase(Connection connection) {
        this.connection = connection;
    }

    public List<Transaction> read(){
        List<Transaction> transactions = new ArrayList<>();
        try{
            Statement statement = connection.createStatement();
            ResultSet result = statement.executeQuery("SELECT * FROM Transactions");
            while(result.next()) {
                Transaction current = new Transaction(result);
                transactions.add(current);
            }
            statement.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
        return transactions;
    }

    public void update(Transaction newTransaction){
        try{
            String query = "UPDATE Transactions SET description = ? WHERE fromIBAN = ? AND toIBAN = ? AND creationDate = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, newTransaction.getDescription());
            preparedStmt.setString(2, newTransaction.getFromIBAN());
            preparedStmt.setString(3, newTransaction.getToIBAN());
            preparedStmt.setString(4, (new SimpleDateFormat("yyyy-MM-dd h:m:s")).format(newTransaction.getCreationDate()));
            preparedStmt.executeUpdate();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void create(Transaction transaction){
        try{
            String query = "INSERT INTO Transactions (fromIBAN, toIBAN, amount, description, creationDate) VALUES (?, ?, ?, ?, ?)";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, transaction.getFromIBAN());
            preparedStmt.setString(2, transaction.getToIBAN());
            preparedStmt.setDouble(3, transaction.getAmount());
            preparedStmt.setString(4, transaction.getDescription());
            preparedStmt.setString(5, (new SimpleDateFormat("yyyy-MM-dd h:m:s")).format(transaction.getCreationDate()));
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void delete(Transaction transaction){
        try{
            String query = "DELETE FROM Transactions WHERE fromIBAN = ?, toIBAN = ?, creationDate = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, transaction.getFromIBAN());
            preparedStmt.setString(2, transaction.getToIBAN());
            preparedStmt.setString(3, (new SimpleDateFormat("yyyy-MM-dd h:m:s")).format(transaction.getCreationDate()));
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
}
