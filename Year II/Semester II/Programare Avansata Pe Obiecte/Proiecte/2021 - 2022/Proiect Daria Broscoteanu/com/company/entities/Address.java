package com.company.entities;

public class Address {
    private int id;
    private String street;
    private String city;
    private String country;
    private String addressLine;

    public Address() {}

    public Address(int id, String street, String city, String country, String addressLine) {
        this.id = id;
        this.street = street;
        this.city = city;
        this.country = country;
        this.addressLine = addressLine;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getAddressLine() {
        return addressLine;
    }

    public void setAddressLine(String addressLine) {
        this.addressLine = addressLine;
    }

    @Override
    public String toString(){
        return "Address{id=" + this.id + ", country=" + this.country + ", city=" + this.city + ", street=" + this.street + ", addressLine=" + this.addressLine + "}";
    }
}
