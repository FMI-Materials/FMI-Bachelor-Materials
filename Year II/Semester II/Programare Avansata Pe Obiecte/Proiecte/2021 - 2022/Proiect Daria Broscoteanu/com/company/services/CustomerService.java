package com.company.services;



import com.company.entities.Address;
import com.company.entities.Customer;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class CustomerService implements CustomerInterface, CSVReader<Customer>, CSVWriter<Customer>{
    private List<Customer> customers = new ArrayList<>();
    private static CustomerService instance;

    private CustomerService(){
        read();
    }

    public static CustomerService getInstance(){
        if(instance == null){
            instance = new CustomerService();
        }
        return instance;
    }

    public List<Customer> getCustomers() {
        List<Customer> customersCopy = new ArrayList<>();
        customersCopy.addAll(this.customers);
        return customersCopy;
    }

    public Customer getCustomerById(int index){
        Customer customer = new Customer();
        for(int i = 0; i < this.customers.size(); ++i){
            if(this.customers.get(i).getId() == index){
                customer = this.customers.get(i);
            }
        }
        return customer;
    }

    public void updateCustomer(int index, Customer customer){
        for(int i = 0; i < this.customers.size(); ++i){
            if(this.customers.get(i).getId() == index){
                this.customers.remove(i);
                this.customers.add(i, customer);
                break;
            }
        }
    }

    public void addCustomer(Customer customer){
        this.customers.add(customer);
    }

    public void deleteCustomerById(int index){
        for(int i = 0; i < this.customers.size(); ++i){
            if(this.customers.get(i).getId() == index){
                this.customers.remove(i);
                break;
            }
        }
    }

    public void deteleCustomer(Customer customer){
        for(int i = 0;i < this.customers.size(); ++i){
            if(this.customers.get(i).equals(customer)){
                this.customers.remove(i);
                break;
            }
        }
    }

    public Customer readCustomer(){
        Scanner scanner = new Scanner(System.in);
        AddressService addressService = AddressService.getInstance();
        Customer customer = new Customer();
//        System.out.println("Id");
//        try {
//            customer.setId(scanner.nextInt());
//        } catch (Exception e){
//            System.out.println("Provide int");
//            customer.setId(scanner.nextInt());
//        }
        int id = getMaxId() + 1;
        customer.setId(id);

        System.out.println("Name");
        customer.setName(scanner.nextLine());

        System.out.println("Email");
        customer.setEmail(scanner.nextLine());

        System.out.println("Address");
        Address address = addressService.readAddress();
        addressService.addAddress(address);
        customer.setAddress(address);

        System.out.println("Usage");
        customer.setUsage(scanner.nextLine());

        System.out.println("Taxes");
        double taxes;
        while(true){
            String line = scanner.nextLine();
            try {
                taxes = Double.parseDouble(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a double");
            }
        }
        return customer;
    }

    public int getMaxId(){
        int max = 0;
        for(int i = 0; i < customers.size(); ++i){
            if(customers.get(i).getId() > max){
                max = customers.get(i).getId();
            }
        }
        return max;
    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - Customer.csv";
        return path;
    }

    @Override
    public String getAntet(){
        return "Id,Name,Email,Usage,Taxes,Address Id\n";
    }

    @Override
    public String convertObjectToString(Customer object) {
        String line = object.getId() + CSVWriter.separator + object.getName() + CSVWriter.separator + object.getEmail() + CSVWriter.separator + object.getUsage() + CSVWriter.separator + object.getTaxes() + CSVWriter.separator + object.getAddress().getId() +  "\n";
        return line;
    }

    @Override
    public void initList(List<Customer> objects) {
        customers = new ArrayList<Customer>(objects);
    }

    @Override
    public Customer processLine(String line){
        String[] fields = line.split(CSVWriter.separator);
        int id = 0;
        try{
            id = Integer.parseInt(fields[0]);
        } catch (Exception e){
            System.out.println("The id must be an int");
        }
        String name = fields[1];
        String email = fields[2];
        String usage = fields[3];
        double taxes = 0.0;
        try{
            taxes = Double.parseDouble(fields[4]);
        } catch (Exception e){
            System.out.println("The salary must be a double");
        }
        if(fields[5].equals("null")){
            fields[5] = "-1";
        }
        int addressId = Integer.parseInt(fields[5]);
        //System.out.println(addressId);
        AddressService addressService = AddressService.getInstance();
        Address address = new Address();
        try{
            address = addressService.getAddressById(addressId);
        } catch (Exception e){
            System.out.println("The address doesnt exist");
        }
        return new Customer(id, address, name, email, usage, taxes);
    }

}
