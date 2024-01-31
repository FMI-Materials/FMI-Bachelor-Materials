package com.company.services;

import com.company.entities.Address;
import com.company.entities.Employee;

import java.util.*;

public class EmployeeService implements EmployeeInterface, CSVReader<Employee>, CSVWriter<Employee> {
    private List<Employee> employees = new ArrayList<>();
    private static EmployeeService instance;

    private EmployeeService(){
        employees = read();
    }

    public static EmployeeService getInstance(){
        if(instance == null){
            instance = new EmployeeService();
        }
        return instance;
    }

    public List<Employee> getEmployees() {
        List<Employee> employeesCopy = new ArrayList<>();
        employeesCopy.addAll(this.employees);
        Collections.sort(employeesCopy, new EmployeeSalaryComparator());
        return employeesCopy;
    }

    public Employee getEmployeeById(int index){
        Employee employee = new Employee();
        for(int i = 0; i < this.employees.size(); ++i){
            if(this.employees.get(i).getId() == index){
                employee = this.employees.get(i);
            }
        }
        return employee;
    }

    public void updateEmployee(int index, Employee employee){
        for(int i = 0; i < this.employees.size(); ++i){
            if(this.employees.get(i).getId() == index){
                this.employees.remove(i);
                this.employees.add(i, employee);
                break;
            }
        }
    }

    public void addEmployees(Employee employee){
        this.employees.add(employee);
    }

    public void deleteEmployeeById(int index){
        for(int i = 0; i < this.employees.size(); ++i){
            if(this.employees.get(i).getId() == index){
                this.employees.remove(i);
                break;
            }
        }
    }

    public void deteleEmployees(Employee employee){
        for(int i = 0;i < this.employees.size(); ++i){
            if(this.employees.get(i).equals(employee)){
                this.employees.remove(i);
                break;
            }
        }
    }

    public Employee readEmployee(){
        Scanner scanner = new Scanner(System.in);
        AddressService addressService = AddressService.getInstance();
        Employee employee = new Employee();
//        System.out.println("Id");
//        try {
//            employee.setId(scanner.nextInt());
//        } catch (Exception e){
//            System.out.println("Provide int");
//            employee.setId(scanner.nextInt());
//        }

        int id = getMaxId() + 1;
        employee.setId(id);

        System.out.println("Name");
        employee.setName(scanner.nextLine());

        System.out.println("Email");
        employee.setEmail(scanner.nextLine());

        System.out.println("Address");
        Address address = addressService.readAddress();
        addressService.addAddress(address);
        employee.setAddress(address);

        System.out.println("Position");
        employee.setPosition(scanner.nextLine());

        System.out.println("Salary");
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

        return employee;
    }

    public int getMaxId(){
        int max = 0;
        for(int i = 0; i < employees.size(); ++i){
            if(employees.get(i).getId() > max){
                max = employees.get(i).getId();
            }
        }
        return max;
    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - Employee.csv";
        return path;
    }

    @Override
    public String getAntet(){
        return "Id,Name,Email,Position,Salary,Address Id\n";
    }

    @Override
    public String convertObjectToString(Employee object) {
        String res;
        if(object.getAddress().getId() == -1){
            res = "null";
        } else {
            res = String.valueOf(object.getAddress().getId());
        }
        String line = object.getId() + CSVWriter.separator + object.getName()
                + CSVWriter.separator + object.getEmail() + CSVWriter.separator + object.getPosition()
                + CSVWriter.separator + object.getSalary() + CSVWriter.separator + res +  "\n";
        return line;
    }

    @Override
    public void initList(List<Employee> objects) {
        employees = new ArrayList<Employee>(objects);
    }

    @Override
    public Employee processLine(String line){
        String[] fields = line.split(CSVWriter.separator);
        int id = 0;
        try{
            id = Integer.parseInt(fields[0]);
        } catch (Exception e){
            System.out.println("The id must be an int");
        }
        String name = fields[1];
        String email = fields[2];
        String position = fields[3];
        double salary = 0.0;
        try{
            salary = Double.parseDouble(fields[4]);
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
        address.setId(-1);
        try{
            address = addressService.getAddressById(addressId);
        } catch (Exception e){
            System.out.println("The address doesnt exist");
        }
        return new Employee(id, address, name, email, position, salary);
    }


}
