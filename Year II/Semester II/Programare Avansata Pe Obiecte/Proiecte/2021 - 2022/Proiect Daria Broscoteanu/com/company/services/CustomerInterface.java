package com.company.services;

import com.company.entities.Address;
import com.company.entities.Customer;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public interface CustomerInterface {
    public List<Customer> getCustomers();

    public Customer getCustomerById(int index);

    public void updateCustomer(int index, Customer customer);

    public void addCustomer(Customer customer);

    public void deleteCustomerById(int index);

    public void deteleCustomer(Customer customer);

    public Customer readCustomer();
}
