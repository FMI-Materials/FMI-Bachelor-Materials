package exemplu1;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class Exemplu3 {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/laboratorpao";
        String user = "root";
        String password = "";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             Statement statement = connection.createStatement()) {
            String query = "insert into student values (null, 'Smith', 'John', 10)";
            statement.executeUpdate(query);
            insertStudent(statement, "da", "da", 10);

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    static void insertStudent(Statement statement, String nume, String prenume, int nota) {

        String sql = "insert into student values(null, '" + nume + "', '" + prenume + "', " + nota + ")";

        try {
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
