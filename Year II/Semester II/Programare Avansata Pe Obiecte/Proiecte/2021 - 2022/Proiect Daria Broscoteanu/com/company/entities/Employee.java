package com.company.entities;

public class Employee extends User {
    private String position;
    private double salary;

    public Employee(){}

    public Employee(int id, Address address, String name, String email, String position, double salary) {
        super(id, address, name, email);
        this.position = position;
        this.salary = salary;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    @Override
    public String toString() {
        return "Employees's name: " + this.name + '\n' + "Email: " + this.email + '\n' + "Address: " +
                this.address.toString() + '\n' + "Position: " + this.position + '\n' +  "Salary: " + this.salary;
    }
}
