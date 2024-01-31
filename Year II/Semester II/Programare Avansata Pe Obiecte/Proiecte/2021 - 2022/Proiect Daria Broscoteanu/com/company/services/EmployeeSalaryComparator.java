package com.company.services;

import com.company.entities.Employee;

import java.util.Comparator;

public class EmployeeSalaryComparator implements Comparator<Employee> {
    @Override
    public int compare(Employee emp1, Employee emp2) {
        if (emp1.getSalary() - emp2.getSalary() > 0){
            return 1;
        }
        return 0;
    }
}
