package com.company.services;

import com.company.entities.Address;
import com.company.entities.Employee;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public interface EmployeeInterface {
    public List<Employee> getEmployees();

    public Employee getEmployeeById(int index);

    public void updateEmployee(int index, Employee employee);

    public void addEmployees(Employee employee);

    public void deleteEmployeeById(int index);

    public void deteleEmployees(Employee employee);

    public Employee readEmployee();
}
