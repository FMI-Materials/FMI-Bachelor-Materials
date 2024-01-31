package Customer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class CustomerSingleton {

    private static CustomerSingleton single_instance = null;

    final private CustomerFactory customerFactory = new CustomerFactory();
    private List<Customer> customers = new ArrayList<Customer>();

    public static CustomerSingleton getInstance()
    {
        if (single_instance == null)
            single_instance = new CustomerSingleton();
        return single_instance;
    }

    public void setCustomers(List<Customer> customers) {
        this.customers = customers;
    }

    public List<Customer> getCustomers() {
        return customers;
    }

    private static List<String[]> getCSVColumns(String fileName){

        List<String[]> columns = new ArrayList<>();

        try(var in = new BufferedReader(new FileReader(fileName))) {

            String line;

            while((line = in.readLine()) != null ) {
                String[] fields = line.replaceAll(" ", "").split(",");
                columns.add(fields);
            }
        } catch (IOException e) {
            System.out.println("No saved customers!");
        }

        return columns;
    }

    public void loadFromCSV() {
        try{
            var columns = CustomerSingleton.getCSVColumns("data/customers.csv");
            for(var fields : columns){
                var newCustomer = new Customer(
                        Integer.parseInt(fields[0]),
                        fields[1],
                        fields[2],
                        fields[3],
                        new SimpleDateFormat("yyyy-MM-dd").parse(fields[4]),
                        fields[5],
                        fields[6],
                        new Address(fields[7], fields[8], fields[9], Integer.parseInt(fields[10]))
                );
                customers.add(newCustomer);
            }
            CustomerFactory.incrementUniqueId(columns.size());
        }catch (ParseException e){
            System.out.println(e.toString());
        }

    }

    public void dumpToCSV(){
        try{
            var writer = new FileWriter("data/customers.csv");
            for(var customer : this.customers){
                writer.write(customer.toCSV());
                writer.write("\n");
            }
            writer.close();
        }catch (IOException e){
            System.out.println(e.toString());
        }
    }


}
