package exemplu1;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Exemplu5 {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/laboratorpao";
        String user = "root";
        String password = "";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {

            ResultSet result = selectStudent(connection);
            while(result.next()) {
                System.out.println("id: " + result.getInt(1)); //" nume: " + result.getString(2) +
                       // " prenume: " + result.getString("prenume") + " nota: " + result.getInt(4));
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    public static ResultSet selectStudent(Connection connection) throws SQLException{
        String query = "select id from student where nota>5";
        return connection.prepareStatement(query).executeQuery();

    }
}
