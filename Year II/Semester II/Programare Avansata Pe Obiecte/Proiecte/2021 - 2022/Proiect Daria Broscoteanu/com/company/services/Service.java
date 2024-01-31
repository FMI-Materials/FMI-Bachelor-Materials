package com.company.services;

import com.company.entities.Company;
import com.company.entities.Computer;
import com.company.entities.KernelKeylogger;
import com.company.entities.Keylogger;
import com.company.entities.Ransomeware;
import com.company.entities.Rootkit;
import com.company.entities.Customer;
import com.company.entities.Employee;

import java.io.IOException;
import java.sql.Timestamp;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.Instant;
import java.time.LocalDateTime;
import java.util.*;

public class Service {
    private AddressService addressService = AddressService.getInstance();
    private RootkitService rootkitService = RootkitService.getInstance();
    private RansomewareService ransomewareService = RansomewareService.getInstance();
    private KeyloggerService keyloggerService = KeyloggerService.getInstance();
    private KernelKeyloggerService kernelKeyloggerService = KernelKeyloggerService.getInstance();

    private EmployeeService employeeService = EmployeeService.getInstance();
    private CustomerService customerService = CustomerService.getInstance();

    private ComputerService computerService = ComputerService.getInstance();

    private CompanyService companyService = CompanyService.getInstance();

    private AuditService auditService = AuditService.getInstance();

    private static Service instance;

    private Scanner scanner = new Scanner(System.in);

    private Service(){}

    public static Service getInstance(){
        if(instance == null){
            instance = new Service();
        }
        return instance;
    }

    public void writeResults(){
        addressService.write(addressService.getAddresses());

        rootkitService.write(rootkitService.getRootkits());
        ransomewareService.write(ransomewareService.getRansomewares());
        keyloggerService.write(keyloggerService.getKeyloggers());
        kernelKeyloggerService.write(kernelKeyloggerService.getKernelKeyloggers());

        employeeService.write(employeeService.getEmployees());
        customerService.write(customerService.getCustomers());

        computerService.write(computerService.getComputers());

        companyService.write(companyService.getCompanies());
    }

    public void printUserMenu(){
        System.out.println(" 0 - Employee");
        System.out.println(" 1 - customer");
        System.out.println(" 2 - Exit");
    }

    public void userMenu() throws IOException {
        while(true){
            printUserMenu();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=2) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 2");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 2");
                }
            }
            if (option == 0) {
                employeeMenu();
            } else if (option == 1) {
                customerMenu();
            } else if (option == 2) {
                break;
            }
        }
    }


    public void customerMenu() throws IOException {
        while(true) {
            printOptions();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=5) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 5");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 5");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Customers" , timeStamp);
                if(customerService.getCustomers().size() == 0){
                    System.out.println("No customers");
                }
                for (int i = 0; i < customerService.getCustomers().size(); ++i) {
                    System.out.println(customerService.getCustomers().get(i).toString());
                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Get Customer By Id" , timeStamp);

                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(customerService.getCustomers().size() == 0){
                    System.out.println("No customers");
                }
                boolean ok = false;
                for (int i = 0; i < customerService.getCustomers().size(); ++i){
                    if(customerService.getCustomers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok) {
                    System.out.println(customerService.getCustomerById(index).toString());
                } else {
                    System.out.println("This customer doesn't exist");
                }
            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Customer" , timeStamp);
                Customer customer = customerService.readCustomer();
                customerService.addCustomer(customer);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Customer" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }

                if(customerService.getCustomers().size() == 0){
                    System.out.println("No customers");
                }
                boolean ok = false;
                for (int i = 0; i < customerService.getCustomers().size(); ++i){
                    if(customerService.getCustomers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Customer customer = customerService.readCustomer();
                    customer.setId(index);
                    customerService.updateCustomer(index, customer);
                } else {
                    System.out.println("No customer with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Customer" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(customerService.getCustomers().size() == 0){
                    System.out.println("No customers");
                }
                boolean ok = false;
                for (int i = 0; i < customerService.getCustomers().size(); ++i){
                    if(customerService.getCustomers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    customerService.deleteCustomerById(index);
                } else {
                    System.out.println("No customer with this id");
                }

            } else if (option == 5) {
                break;
            }
        }
    }


    public void employeeMenu() {
        while(true) {
            printOptions();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=5) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 5");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 5");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Employees" , timeStamp);
                if(employeeService.getEmployees().size() == 0){
                    System.out.println("No employees");
                }
                for (int i = 0; i < employeeService.getEmployees().size(); ++i) {
                    System.out.println(employeeService.getEmployees().get(i).toString());
                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Get Employee by Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(employeeService.getEmployees().size() == 0){
                    System.out.println("No employees");
                }
                boolean ok = false;
                for (int i = 0; i < employeeService.getEmployees().size(); ++i) {
                    if(employeeService.getEmployees().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    System.out.println(employeeService.getEmployeeById(index).toString());
                } else {
                    System.out.println("No employee with this id");
                }

            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Employee" , timeStamp);
                Employee employee = employeeService.readEmployee();
                employeeService.addEmployees(employee);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Employee" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(employeeService.getEmployees().size() == 0){
                    System.out.println("No employees");
                }
                boolean ok = false;
                for (int i = 0; i < employeeService.getEmployees().size(); ++i) {
                    if(employeeService.getEmployees().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Employee employee = employeeService.readEmployee();
                    employee.setId(index);
                    employeeService.updateEmployee(index, employee);
                } else {
                    System.out.println("No employee with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Employee" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(employeeService.getEmployees().size() == 0){
                    System.out.println("No employees");
                }
                boolean ok = false;
                for (int i = 0; i < employeeService.getEmployees().size(); ++i) {
                    if(employeeService.getEmployees().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    employeeService.deleteEmployeeById(index);
                } else {
                    System.out.println("No employee with this id");
                }
            } else if (option == 5) {
                break;
            }
        }
    }

    public void printMalwareMenu(){
        System.out.println(" 0 - Rootkit");
        System.out.println(" 1 - Ransomeware");
        System.out.println(" 2 - Keylogger");
        System.out.println(" 3 - Kernel Keylogger");
        System.out.println(" 4 - Exit");
    }

    public void malwareMenu() throws ParseException {
        while(true){
            printMalwareMenu();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=4) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 4");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 4");
                }
            }
            if (option == 0) {
                rootkitMenu();
            } else if (option == 1) {
                ransomewareMenu();
            } else if (option == 2) {
                keyloggerMenu();
            } else if (option == 3) {
                kernelKeyloggerMenu();
            } else if (option == 4) {
                break;
            }
        }
    }

    public void keyloggerMenu() throws ParseException {
        while(true) {
            printOptions();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=5) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 5");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 5");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Keyloggers" , timeStamp);
                if(keyloggerService.getKeyloggers().size() == 0){
                    System.out.println("No keyloggers");
                }
                for (int i = 0; i < keyloggerService.getKeyloggers().size(); ++i) {
                    System.out.println(keyloggerService.getKeyloggers().get(i).toString());
                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Keylogger By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(keyloggerService.getKeyloggers().size() == 0){
                    System.out.println("No keyloggers");
                }
                boolean ok = false;
                for (int i = 0; i < keyloggerService.getKeyloggers().size(); ++i) {
                    if(keyloggerService.getKeyloggers().get(i).getId() == index){
                        ok = true;
                    }
                }
                if(ok){
                    System.out.println(keyloggerService.getKeyloggerById(index).toString());
                }

            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Keylogger" , timeStamp);
                Keylogger keylogger = keyloggerService.readKeylogger();
                keyloggerService.addKeylogger(keylogger);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Keylogger By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(keyloggerService.getKeyloggers().size() == 0){
                    System.out.println("No keyloggers");
                }
                boolean ok = false;
                for (int i = 0; i < keyloggerService.getKeyloggers().size(); ++i) {
                    if(keyloggerService.getKeyloggers().get(i).getId() == index){
                        ok = true;
                    }
                }
                if(ok){
                    Keylogger keylogger = keyloggerService.readKeylogger();
                    keylogger.setId(index);
                    keyloggerService.updateKeylogger(index, keylogger);
                }
            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Keylogger By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(keyloggerService.getKeyloggers().size() == 0){
                    System.out.println("No keyloggers");
                }
                boolean ok = false;
                for (int i = 0; i < keyloggerService.getKeyloggers().size(); ++i) {
                    if(keyloggerService.getKeyloggers().get(i).getId() == index){
                        ok = true;
                    }
                }
                if(ok){
                    keyloggerService.deleteKeyloggerById(index);
                }

            } else if (option == 5) {
                break;
            }
        }
    }

    public void kernelKeyloggerMenu() throws ParseException {
        while(true) {
            printOptions();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=5) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 5");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 5");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Kernel-Keyloggers" , timeStamp);
                if(kernelKeyloggerService.getKernelKeyloggers().size() == 0){
                    System.out.println("No kernelkeyloggers");
                }
                for (int i = 0; i < kernelKeyloggerService.getKernelKeyloggers().size(); ++i) {
                    System.out.println(kernelKeyloggerService.getKernelKeyloggers().get(i).toString());
                }
            } else if (option == 1) {SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Kernel-Keylogger By Id" , timeStamp);

                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(kernelKeyloggerService.getKernelKeyloggers().size() == 0){
                    System.out.println("No kernelkeyloggers");
                }
                boolean ok = false;
                for (int i = 0; i < kernelKeyloggerService.getKernelKeyloggers().size(); ++i) {
                    if(kernelKeyloggerService.getKernelKeyloggers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    System.out.println(kernelKeyloggerService.getKernelKeyloggerById(index).toString());
                } else {
                    System.out.println("No kernel keylogger with this id");
                }
            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Kernel-Keylogger" , timeStamp);
                KernelKeylogger kernelKeylogger = kernelKeyloggerService.readKernelkeylogger();
                kernelKeyloggerService.addKernelKeylogger(kernelKeylogger);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Kernel-Keylogger" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(kernelKeyloggerService.getKernelKeyloggers().size() == 0){
                    System.out.println("No kernelkeyloggers");
                }
                boolean ok = false;
                for (int i = 0; i < kernelKeyloggerService.getKernelKeyloggers().size(); ++i) {
                    if(kernelKeyloggerService.getKernelKeyloggers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    KernelKeylogger kernelKeylogger = kernelKeyloggerService.readKernelkeylogger();
                    kernelKeylogger.setId(index);
                    kernelKeyloggerService.updateKernelKeylogger(index, kernelKeylogger);
                } else {
                    System.out.println("No kernel keylogger with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Kernel-Keylogger" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(kernelKeyloggerService.getKernelKeyloggers().size() == 0){
                    System.out.println("No kernelkeyloggers");
                }
                boolean ok = false;
                for (int i = 0; i < kernelKeyloggerService.getKernelKeyloggers().size(); ++i) {
                    if(kernelKeyloggerService.getKernelKeyloggers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    kernelKeyloggerService.deleteKernelKeyloggerById(index);
                } else {
                    System.out.println("No kernel keylogger with this id");
                }

            } else if (option == 5) {
                break;
            }
        }
    }

    public void ransomewareMenu() throws ParseException {
        while(true) {
            printOptions();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=5) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 5");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 5");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Ransomewares" , timeStamp);
                if(ransomewareService.getRansomewares().size() == 0){
                    System.out.println("No ransomewares");
                }
                for (int i = 0; i < ransomewareService.getRansomewares().size(); ++i) {
                    System.out.println(ransomewareService.getRansomewares().get(i).toString());
                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Ransomeware By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(ransomewareService.getRansomewares().size() == 0){
                    System.out.println("No ransomewares");
                }
                boolean ok = false;
                for (int i = 0; i < ransomewareService.getRansomewares().size(); ++i) {
                    if (ransomewareService.getRansomewares().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    System.out.println(ransomewareService.getRansomewareById(index).toString());
                } else {
                    System.out.println("No ransomeware with this id");
                }
            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Ransomeware" , timeStamp);
                Ransomeware ransomeware = ransomewareService.readRansomeware();
                ransomewareService.addRansomeware(ransomeware);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Ransomeware" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(ransomewareService.getRansomewares().size() == 0){
                    System.out.println("No ransomewares");
                }
                boolean ok = false;
                for (int i = 0; i < ransomewareService.getRansomewares().size(); ++i) {
                    if (ransomewareService.getRansomewares().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Ransomeware ransomeware = ransomewareService.readRansomeware();
                    ransomeware.setId(index);
                    ransomewareService.updateRansomeware(index, ransomeware);
                } else {
                    System.out.println("No ransomeware with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Ransomeware" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(ransomewareService.getRansomewares().size() == 0){
                    System.out.println("No ransomewares");
                }
                boolean ok = false;
                for (int i = 0; i < ransomewareService.getRansomewares().size(); ++i) {
                    if (ransomewareService.getRansomewares().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    ransomewareService.deleteRansomewareById(index);
                } else {
                    System.out.println("No ransomeware with this id");
                }

            } else if (option == 5) {
                break;
            }
        }
    }

    public void rootkitMenu() throws ParseException {
        while(true) {
            printOptions();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=5) {
                        break;
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 5");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Rootkits" , timeStamp);
                if(rootkitService.getRootkits().size() == 0){
                    System.out.println("No rootkits");
                }
                for (int i = 0; i < rootkitService.getRootkits().size(); ++i) {
                    System.out.println(rootkitService.getRootkits().get(i).toString());
                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Rootkit By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(rootkitService.getRootkits().size() == 0){
                    System.out.println("No rootkits");
                }
                boolean ok = false;
                for (int i = 0; i < rootkitService.getRootkits().size(); ++i) {
                    if(rootkitService.getRootkits().get(i).getId() == index){
                        ok = true;
                    }
                }
                if(ok){
                    System.out.println(rootkitService.getRootkitById(index).toString());
                } else {
                    System.out.println("No rootkit with this id");
                }

            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Rootkit" , timeStamp);
                Rootkit rootkit = rootkitService.readRootkit();
                rootkitService.addRootkit(rootkit);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Rootkit" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(rootkitService.getRootkits().size() == 0){
                    System.out.println("No rootkits");
                }
                boolean ok = false;
                for (int i = 0; i < rootkitService.getRootkits().size(); ++i) {
                    if(rootkitService.getRootkits().get(i).getId() == index){
                        ok = true;
                    }
                }
                if(ok){
                    Rootkit rootkit = rootkitService.readRootkit();
                    rootkit.setId(index);
                    rootkitService.updateRootkit(index, rootkit);
                } else {
                    System.out.println("No rootkit with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Rootkit" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(rootkitService.getRootkits().size() == 0){
                    System.out.println("No rootkits");
                }
                boolean ok = false;
                for (int i = 0; i < rootkitService.getRootkits().size(); ++i) {
                    if(rootkitService.getRootkits().get(i).getId() == index){
                        ok = true;
                    }
                }
                if(ok){
                    rootkitService.deleteRootkitById(index);
                } else {
                    System.out.println("No rootkit with this id");
                }
            } else if (option == 5) {
                break;
            }
        }
    }

    public void computerMenu() throws ParseException {
        while(true) {
            printOptions();
            System.out.println(" 6 - Calculate total infection rating by id");
            System.out.println(" 7 - Calculate total Taxes for customer by id");
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <=7) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 7");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 7");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Computers" , timeStamp);
                if(computerService.getComputers().size() == 0){
                    System.out.println("No computers");
                }
                for (int i = 0; i < computerService.getComputers().size(); ++i) {
                    if (computerService.getComputers().get(i).getMalwares().size() > 0 ){
                        computerService.getComputers().get(i).getMalwares().forEach(malware -> {
                            if(malware instanceof Rootkit){
                                Rootkit rootkit = (Rootkit) malware;
                                System.out.println(rootkit.toString());
                            }
                            else if(malware instanceof Ransomeware){
                                Ransomeware ransomeware = (Ransomeware) malware;
                                System.out.println(ransomeware.toString());
                            }
                            else if(malware instanceof Keylogger){
                                if( malware instanceof KernelKeylogger){
                                    KernelKeylogger kernelKeylogger = (KernelKeylogger) malware;
                                    System.out.println(kernelKeylogger.toString());
                                }
                                else {
                                    Keylogger keylogger = (Keylogger) malware;
                                    System.out.println(keylogger.toString());
                                }
                            }
                        });
                    }

                    if (computerService.getComputers().get(i).getUsers().size() > 0 ) {
                        computerService.getComputers().get(i).getUsers().forEach(user -> {
                            if(user instanceof Customer){
                                Customer customer = (Customer) user;
                                System.out.println(customer.toString());
                            }
                            else if(user instanceof Employee){
                                Employee employee = (Employee) user;
                                System.out.println(employee.toString());
                            }
                        });
                    }
                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Computer By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                boolean ok = false;
                for (int i = 0; i < computerService.getComputers().size(); ++i){
                    if(computerService.getComputers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Computer computer = computerService.getComputerById(index);
                    if(computer.getMalwares().size() > 0){
                        computer.getMalwares().forEach(malware -> {
                            if(malware instanceof Rootkit){
                                Rootkit rootkit = (Rootkit) malware;
                                System.out.println(rootkit.toString());
                            }
                            else if(malware instanceof Ransomeware){
                                Ransomeware ransomeware = (Ransomeware) malware;
                                System.out.println(ransomeware.toString());
                            }
                            else if(malware instanceof Keylogger){
                                if( malware instanceof KernelKeylogger){
                                    KernelKeylogger kernelKeylogger = (KernelKeylogger) malware;
                                    System.out.println(kernelKeylogger.toString());
                                }
                                else {
                                    Keylogger keylogger = (Keylogger) malware;
                                    System.out.println(keylogger.toString());
                                }
                            }
                        });
                    }
                    if(computer.getUsers().size() > 0){
                        for(int j = 0; j < computer.getUsers().size(); ++j){
                            computer.getUsers().forEach(user -> {
                                if(user instanceof Customer){
                                    Customer customer = (Customer) user;
                                    System.out.println(customer.toString());
                                }
                                else if(user instanceof Employee){
                                    Employee employee = (Employee) user;
                                    System.out.println(employee.toString());
                                }
                            });
                        }
                    }
                } else {
                    System.out.println("No computer with this id");
                }

            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Computer" , timeStamp);
                Computer computer = computerService.readComputer();
                computerService.addComputer(computer);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Computer" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(computerService.getComputers().size() == 0){
                    System.out.println("No computers");
                }
                boolean ok = false;
                for (int i = 0; i < computerService.getComputers().size(); ++i){
                    if(computerService.getComputers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Computer computer = computerService.readComputer();
                    computer.setId(index);
                    computerService.updateComputer(index, computer);
                } else {
                    System.out.println("No computer with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Computer By Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(computerService.getComputers().size() == 0){
                    System.out.println("No computers");
                }
                boolean ok = false;
                for (int i = 0; i < computerService.getComputers().size(); ++i){
                    if(computerService.getComputers().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    computerService.deleteComputerById(index);
                } else {
                    System.out.println("No computer with this id");
                }
            } else if (option == 5) {
                break;
            } else if(option == 6){
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Total Infection Rating for a Computer by Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(computerService.getComputers().size() == 0){
                    System.out.println("No computers");
                }
                boolean ok = false;
                Computer computer = null;
                for (int i = 0; i < computerService.getComputers().size(); ++i){
                    if(computerService.getComputers().get(i).getId() == index){
                        computer = computerService.getComputers().get(i);
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    double rating = computerService.calculateTotalRating(computer);
                    System.out.println("Total infection rating for this computer is: " + rating);
                } else {
                    System.out.println("No computer with this id");
                }
            } else if(option == 7){
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print total Taxes for customers b by id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(computerService.getComputers().size() == 0){
                    System.out.println("No computers");
                }
                boolean ok = false;
                Computer computer = null;
                for (int i = 0; i < computerService.getComputers().size(); ++i){
                    if(computerService.getComputers().get(i).getId() == index){
                        computer = computerService.getComputers().get(i);
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    computerService.calculateTotalTaxesById(index);
                } else {
                    System.out.println("No computer with this id");
                }


            }
        }
    }
    public void printOptions(){
        System.out.println(" 0 - Get All");
        System.out.println(" 1 - Get By Id");
        System.out.println(" 2 - Add");
        System.out.println(" 3 - Update");
        System.out.println(" 4 - Delete");
        System.out.println(" 5 - Exit");
    }

    public void printMenu(){
        System.out.println(" 1 - Malwares");
        System.out.println(" 2 - Users");
        System.out.println(" 3 - Computers");
        System.out.println(" 4 - Companies");
        System.out.println(" 5 - Exit");

    }

    public void companyMenu() throws ParseException {
        while(true) {
            printOptions();
            System.out.println(" 6 - Print top 3 most infected computers for a specific company");
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 0 && option <= 6) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 6");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 6");
                }
            }
            if (option == 0) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Companies by Id" , timeStamp);
                if(companyService.getCompanies().size() ==  0){
                    System.out.println("No companies");
                }
                for (int i = 0; i < companyService.getCompanies().size(); ++i) {
                    System.out.println("Name: " + companyService.getCompanies().get(i).getName());
                    System.out.println("Address: " + companyService.getCompanies().get(i).getAddress().toString());
                    for(int j = 0; j < companyService.getCompanies().get(i).getComputers().size(); ++j){
                        companyService.getCompanies().get(i).getComputers().get(j).getMalwares().forEach(malware -> {
                            if(malware instanceof Rootkit){
                                Rootkit rootkit = (Rootkit) malware;
                                System.out.println(rootkit.toString());
                            }
                            else if(malware instanceof Ransomeware){
                                Ransomeware ransomeware = (Ransomeware) malware;
                                System.out.println(ransomeware.toString());
                            }
                            else if(malware instanceof Keylogger){
                                if( malware instanceof KernelKeylogger){
                                    KernelKeylogger kernelKeylogger = (KernelKeylogger) malware;
                                    System.out.println(kernelKeylogger.toString());
                                }
                                else {
                                    Keylogger keylogger = (Keylogger) malware;
                                    System.out.println(keylogger.toString());
                                }
                            }
                        });


                    if( companyService.getCompanies().get(i).getComputers().get(j).getUsers().size() > 0){
                        companyService.getCompanies().get(i).getComputers().get(j).getUsers().forEach(user -> {
                            if(user instanceof Customer){
                                Customer customer = (Customer) user;
                                System.out.println(customer.toString());
                            }
                            else if(user instanceof Employee){
                                Employee employee = (Employee) user;
                                System.out.println(employee.toString());
                            }
                        });
                    }
                    }

                }
            } else if (option == 1) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Company by Id" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(companyService.getCompanies().size() ==  0){
                    System.out.println("No companies");
                }
                boolean ok = false;
                for (int i = 0; i < companyService.getCompanies().size(); ++i){
                    if(companyService.getCompanies().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Company company = companyService.getCompanyById(index);
                    System.out.println("Name: " + company.getName());
                    System.out.println("Address: " + company.getAddress().toString());
                    for(int i = 0; i < company.getComputers().size(); ++i) {
                        if (company.getComputers().get(i).getMalwares().size() > 0) {
                            company.getComputers().get(i).getMalwares().forEach(malware -> {
                                if (malware instanceof Rootkit) {
                                    Rootkit rootkit = (Rootkit) malware;
                                    System.out.println(rootkit.toString());
                                } else if (malware instanceof Ransomeware) {
                                    Ransomeware ransomeware = (Ransomeware) malware;
                                    System.out.println(ransomeware.toString());
                                } else if (malware instanceof Keylogger) {
                                    if (malware instanceof KernelKeylogger) {
                                        KernelKeylogger kernelKeylogger = (KernelKeylogger) malware;
                                        System.out.println(kernelKeylogger.toString());
                                    } else {
                                        Keylogger keylogger = (Keylogger) malware;
                                        System.out.println(keylogger.toString());
                                    }
                                }
                            });
                        }
                        if(company.getComputers().get(i).getUsers().size() > 0){
                                company.getComputers().get(i).getUsers().forEach(user -> {
                                    if(user instanceof Customer){
                                        Customer customer = (Customer) user;
                                        System.out.println(customer.toString());
                                    }
                                    else if(user instanceof Employee){
                                        Employee employee = (Employee) user;
                                        System.out.println(employee.toString());
                                    }
                                });
                        }
                    }
                } else {
                    System.out.println("No company with this id");
                }

            } else if (option == 2) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Add Company" , timeStamp);
                Company company = companyService.readCompany();
                companyService.addCompanies(company);
            } else if (option == 3) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Update Company" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(companyService.getCompanies().size() ==  0){
                    System.out.println("No companies");
                }
                boolean ok = false;
                for (int i = 0; i < companyService.getCompanies().size(); ++i){
                    if(companyService.getCompanies().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    Company company = companyService.readCompany();
                    company.setId(index);
                    companyService.updateCompany(index, company);
                } else {
                    System.out.println("No company with this id");
                }

            } else if (option == 4) {
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Delete Company" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(companyService.getCompanies().size() ==  0){
                    System.out.println("No companies");
                }
                boolean ok = false;
                for (int i = 0; i < companyService.getCompanies().size(); ++i){
                    if(companyService.getCompanies().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    companyService.deleteCompanyById(index);
                } else {
                    System.out.println("No company with this id");
                }
            } else if (option == 5) {
                break;
            } else if(option == 6){
                SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                String timeStamp = date.format(new Date());
                auditService.audit("Print Top 3 Most Infected Computers" , timeStamp);
                int index;
                while(true){
                    String line = scanner.nextLine();
                    try {
                        index = Integer.parseInt(line);
                        break;
                    } catch (Exception e){
                        System.out.println("Enter a number");
                    }
                }
                if(companyService.getCompanies().size() ==  0){
                    System.out.println("No companies");
                }
                boolean ok = false;
                for (int i = 0; i < companyService.getCompanies().size(); ++i){
                    if(companyService.getCompanies().get(i).getId() == index){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    companyService.printTop3MostInfectedComputers(index);
                } else {
                    System.out.println("No company with this id");
                }

            }
        }
    }

    public void menu() throws ParseException, IOException {
        while(true){
            printMenu();
            int option;
            while(true){
                String line = scanner.nextLine();
                try {
                    option = Integer.parseInt(line);
                    if(option >= 1 && option <=5) {
                        break;
                    } else {
                        System.out.println("Enter a number between 1 and 5");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 1 and 5");
                }
            }
            if(option == 1){
                malwareMenu();
            }
            else if(option == 2){
                userMenu();
            }
            else if(option == 3){
                computerMenu();
            }
            else if(option == 4){
                companyMenu();
            }
            else if(option == 5){
                break;
            }
        }
        writeResults();
    }
}
