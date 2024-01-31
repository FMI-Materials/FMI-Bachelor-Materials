package Customer;

import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class CustomerDatabase{
    Connection connection;

    CustomerFactory customerFactory = new CustomerFactory();

    public CustomerDatabase(Connection connection) {
        this.connection = connection;
    }

    public List<Customer> read(){
        List<Customer> customers = new ArrayList<>();
        try{
            Statement statement = connection.createStatement();
            ResultSet result = statement.executeQuery("SELECT * FROM Customers");
            while(result.next()) {
                Customer current = customerFactory.createCustomer(result);
                customers.add(current);
            }
            statement.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
        return customers;
    }

    public void update(Customer newCustomer){
        try{
            String query = "UPDATE Customers SET firstName = ?, lastName = ?, CNP = ?, birthDate = ?, email = ?, phone = ?, street = ?, city = ?, county = ?, postalCode = ? WHERE customerId = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString(1, newCustomer.getFirstName());
            preparedStmt.setString(2, newCustomer.getLastName());
            preparedStmt.setString(3, newCustomer.getCNP());
            preparedStmt.setString(4, (new SimpleDateFormat("yyyy-MM-dd")).format(newCustomer.getBirthDate()));
            preparedStmt.setString(5, newCustomer.getEmail());
            preparedStmt.setString(6, newCustomer.getPhone());
            preparedStmt.setString(7, newCustomer.getAddress().getStreet());
            preparedStmt.setString(8, newCustomer.getAddress().getCity());
            preparedStmt.setString(9, newCustomer.getAddress().getCounty());
            preparedStmt.setInt(10, newCustomer.getAddress().getPostalCode());
            preparedStmt.setInt(11, newCustomer.getCustomerId());
            preparedStmt.executeUpdate();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void create(Customer customer){
        try{
            String query = "INSERT INTO Customers (customerId, firstName, lastName, CNP, birthDate, email, phone, street, city, county, postalCode) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setInt(1, customer.getCustomerId());
            preparedStmt.setString(2, customer.getFirstName());
            preparedStmt.setString(3, customer.getLastName());
            preparedStmt.setString(4, customer.getCNP());
            preparedStmt.setString(5, (new SimpleDateFormat("yyyy-MM-dd")).format(customer.getBirthDate()));
            preparedStmt.setString(6, customer.getEmail());
            preparedStmt.setString(7, customer.getPhone());
            preparedStmt.setString(8, customer.getAddress().getStreet());
            preparedStmt.setString(9, customer.getAddress().getCity());
            preparedStmt.setString(10, customer.getAddress().getCounty());
            preparedStmt.setInt(11, customer.getAddress().getPostalCode());
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public void delete(Customer customer){
        try{
            String query = "DELETE FROM Customers WHERE customerId = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setInt(1, customer.getCustomerId());
            preparedStmt.execute();
            preparedStmt.close();
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
}
