package com.company.entities;

public class Customer extends User {
    private String usage;
    private double taxes;

    public Customer(){}

    public Customer(int id, Address address, String name, String email, String usage, double taxes) {
        super(id, address, name, email);
        this.usage = usage;
        this.taxes = taxes;
    }

    public String getUsage() {
        return usage;
    }

    public void setUsage(String usage) {
        this.usage = usage;
    }

    public double getTaxes() {
        return taxes;
    }

    public void setTaxes(double taxes) {
        this.taxes = taxes;
    }

    @Override
    public String toString() {
        return "Customer's name: " + this.name + '\n' + "Email: " + this.email + '\n' + "Address: " +
                    this.address.toString() + '\n' + "Usage: " + this.usage + '\n' +  "Taxes: " + this.taxes;
    }
}
