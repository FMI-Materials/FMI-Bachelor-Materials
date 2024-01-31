package Customer;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.Date;
import java.util.Scanner;

public class CustomerFactory {
    private static int uniqueId = 0;

    public static void incrementUniqueId(int inc) {
        CustomerFactory.uniqueId += inc;
    }

    public Customer createCustomer(Scanner in) throws ParseException {
        return new Customer(uniqueId++, in);
    }

    public Customer createCustomer(ResultSet in) throws SQLException {
        return new Customer(uniqueId++, in);
    }
}
