package exemplu1;


/*
       Deadline2: 7 mai
       Deadline3: 30 mai (nu e batut in cuie)
 */

//JDBC Template: java database connection
//conexiune normala (fara dependinte)
//o sa facem si conexiune folosind dependinte (o sa cream un proiect maven)
// mysql workbench: https://dev.mysql.com/downloads/workbench/ -> Microsoft Windows
// xampp: https://www.apachefriends.org/ro/index.html
// mysql connector: https://dev.mysql.com/downloads/connector/j/ -> platform independent -> descarcat cel cu .zip

//XAMPP => este folosit pentru a crea un server de mysql
//workbench => pentru conexiune + creare baza de date


//Workbench -> + -> dati un nume conexiunii, setati user (default root), parola (default "" sau root) sau puteti seta parola din Store In Vault
//ca sa vedeti daca serverul este running -> Server -> Server Status
//crearea unei scheme: Create a new schema in the connected server
//click pe numele schemei, click dreapte pe tables -> Create Table

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

/*
        Pentru a lucra cu JDBC avem nevoie de:
            1)Driver obiect care ne ajuta pe noi sa obtinem conexiunea
            2)Connection
            3)Statement obiect care ne ajuta pe noi sa executam query-urile
            4)ResultSet obiect care ne ajuta sa obtinem rezultatul selecturilor din baza

            Pentru aducerea jarului -> File -> Project Structure -> Modules -> + -ul din dreapta -> JARs and directories
 */
public class Exemplu1 {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/laboratorpao";
        // url = 3 bucati: protocol + vendorul + adresa
        String user = "root";
        String password = ""; //ori e "" ori e "root" ori e ce puneti voi in store vault

        try (Connection connection = DriverManager.getConnection(url, user, password);
             Statement statement = connection.createStatement()) {

            //indicat este executeUpdate pentru insert, update, delete
            //indicat este executeQuery pentru select
            String query = "insert into student values (null, 'Smith', 'John', 10)";
            statement.executeUpdate(query);

            //se inchid in ordine inversa declararii
//            statement.close();
//            connection.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

}
