package exemplu1;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class Exemplu2 {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/laboratorpao";
        String user = "root";
        String password = "root";
        Connection connection = null;
        Statement statement = null;

        try {
            connection = DriverManager.getConnection(url, user, password);
            statement = connection.createStatement();
            String query = "insert into student values (null, 'Smith', 'John', 10)";
            statement.executeUpdate(query);

            //se inchid in ordine inversa declararii
//            statement.close();
//            connection.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            try {
                statement.close();
                connection.close();
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
    }
}
