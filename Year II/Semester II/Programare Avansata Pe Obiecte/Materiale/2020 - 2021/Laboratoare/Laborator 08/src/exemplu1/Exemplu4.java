package exemplu1;

import java.sql.*;

public class Exemplu4 {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/laboratorpao";
        String user = "root";
        String password = "";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {

            insertStudent(connection, "un nume", "un prenume", 5);
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    static void insertStudent(Connection connection, String nume, String prenume, int nota) {
        String query = "insert into student values (null,?, ?, ?)";

        try {
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, nume);
            preparedStatement.setString(2, prenume);
            preparedStatement.setInt(3, nota);
            preparedStatement.executeUpdate();
            preparedStatement.close();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

    }
}
