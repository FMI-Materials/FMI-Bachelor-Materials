package com.company.entities;

public abstract class User {
    protected int id;
    protected Address address;
    protected String name;
    protected String email;

    public User(){}

    public User(int id, Address address, String name, String email) {
        this.id = id;
        this.address = address;
        this.name = name;
        this.email = email;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Address getAddress() {
        return address;
    }

    public void setAddress(Address address) {
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

}
