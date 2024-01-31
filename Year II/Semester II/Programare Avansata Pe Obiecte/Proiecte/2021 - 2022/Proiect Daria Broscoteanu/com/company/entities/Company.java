package com.company.entities;

import java.util.List;

public class Company {
    private int id;
    private String name;
    private Address address;
    private List<Computer> computers;

    public Company(){}

    public Company(int id, String name, Address address, List<Computer> computers) {
        this.id = id;
        this.name = name;
        this.address = address;
        this.computers = computers;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Address getAddress() {
        return address;
    }

    public void setAddress(Address address) {
        this.address = address;
    }

    public List<Computer> getComputers() {
        return computers;
    }

    public void setComputers(List<Computer> computers) {
        this.computers = computers;
    }

}
