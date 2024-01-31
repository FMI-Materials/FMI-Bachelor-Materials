package com.company.services;


import com.company.entities.*;

import java.io.*;
import java.text.ParseException;
import java.util.*;
import java.util.stream.Collectors;

public class ComputerService implements ComputerInterface, CSVReader<Computer>, CSVWriter<Computer> {
    private List<Computer> computers = new ArrayList<>();
    private static ComputerService instance;

    private ComputerService(){
        read();
    }

    public static ComputerService getInstance(){
        if(instance == null){
            instance = new ComputerService();
        }
        return instance;
    }

    public List<Computer> getComputers() {
        List<Computer> computersCopy = new ArrayList<>();
        computersCopy.addAll(this.computers);
        return computersCopy;
    }

    public Computer getComputerById(int index){
        Computer computer = new Computer();
        for(int i = 0; i < this.computers.size(); ++i){
            if(this.computers.get(i).getId() == index){
                computer = this.computers.get(i);
            }
        }
        return computer;
    }

    public void updateComputer(int index, Computer computer){
        for(int i = 0; i < this.computers.size(); ++i){
            if(this.computers.get(i).getId() == index){
                this.computers.remove(i);
                this.computers.add(i, computer);
                break;
            }
        }
    }

    public void addComputer(Computer computer){
        this.computers.add(computer);
    }

    public void deleteComputerById(int index){
        for(int i = 0; i < this.computers.size(); ++i){
            if(this.computers.get(i).getId() == index){
                this.computers.remove(i);
                break;
            }
        }
    }

    public void deteleComputers(Computer computer){
        for(int i = 0;i < this.computers.size(); ++i){
            if(this.computers.get(i).equals(computer)){
                this.computers.remove(i);
                break;
            }
        }
    }

    public double calculateTotalRating(Computer computer){
        final double[] totalRating = {0};
        computer.getMalwares().forEach(malware -> {
            if(malware instanceof Rootkit){
                Rootkit rootkit = ((Rootkit) malware);
                totalRating[0] += rootkit.getRating();
            }
            else if(malware instanceof Ransomeware){
                totalRating[0] += ((Ransomeware) malware).getRating();
            }
            else if(malware instanceof Keylogger){
                totalRating[0] += ((Keylogger) malware).getRating();
            }
            else if(malware instanceof KernelKeylogger){
                totalRating[0] += ((KernelKeylogger) malware).getRating();
            }
        });
        computer.setTotalRating(totalRating[0]);
        return totalRating[0];
    }

    public int getMaxId(){
        int max = 0;
        for(int i = 0; i < computers.size(); ++i){
            if(computers.get(i).getId() > max){
                max = computers.get(i).getId();
            }
        }
        return max;
    }

    public Computer readComputer() throws ParseException {
        Scanner scanner = new Scanner(System.in);
        RootkitService rootkitService = RootkitService.getInstance();
        RansomewareService ransomewareService = RansomewareService.getInstance();
        KeyloggerService keyloggerService = KeyloggerService.getInstance();
        KernelKeyloggerService kernelKeyloggerService = KernelKeyloggerService.getInstance();
        EmployeeService employeeService = EmployeeService.getInstance();
        CustomerService customerService = CustomerService.getInstance();
        //System.out.println("Id");
        Computer computer = new Computer();
        int id = getMaxId() + 1;
        computer.setId(id);

        System.out.println("Number of Malwares");
        int nr;
        while(true){
            String line = scanner.nextLine();
            try {
                nr = Integer.parseInt(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }
        System.out.println("Malwares");
        List<Malware> arr = new ArrayList<>();
        for(int i = 0; i < nr; ++i){
            System.out.println(" 0 - Rootkit");
            System.out.println(" 1 - Ransomeware");
            System.out.println(" 2 - Keylogger");
            System.out.println(" 3 - Kernel Keylogger");
            int opt;
            while(true){
                String line = scanner.nextLine();
                try {
                    opt = Integer.parseInt(line);
                    if(opt >= 0 && opt <=3) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 3");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 3");
                }
            }
            if(opt == 0) {
                Rootkit rootkit = rootkitService.readRootkit();
                rootkitService.addRootkit(rootkit);
                arr.add(rootkit);
            }
            else if(opt == 1){
                Ransomeware  ransomeware = ransomewareService.readRansomeware();
                ransomewareService.addRansomeware(ransomeware);
                arr.add(ransomeware);
            }
            else if(opt == 2){
                Keylogger keylogger = keyloggerService.readKeylogger();
                keyloggerService.addKeylogger(keylogger);
                arr.add(keylogger);
            }
            else if(opt == 3){
                KernelKeylogger kernelKeylogger = kernelKeyloggerService.readKernelkeylogger();
                kernelKeyloggerService.addKernelKeylogger(kernelKeylogger);
                arr.add(kernelKeylogger);
            }
        }
        // TreeSet t = new TreeSet(arr);
        computer.setMalwares((ArrayList) arr);

        System.out.println("Number of Users");
        List<User> arr1 = new ArrayList<>();
        while(true){
            String line = scanner.nextLine();
            try {
                nr = Integer.parseInt(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }
        System.out.println("Users");
        for(int i = 0; i < nr; ++i){
            System.out.println("0 - Costumer");
            System.out.println("1 - Employee");
            int opt;
            while(true){
                String line = scanner.nextLine();
                try {
                    opt = Integer.parseInt(line);
                    if(opt >= 0 && opt <=1) {
                        break;
                    } else {
                        System.out.println("Enter a number between 0 and 1");
                    }
                } catch (Exception e){
                    System.out.println("Enter a number between 0 and 1");
                }
            }
            if(opt == 0){
                Customer customer = customerService.readCustomer();
                customerService.addCustomer(customer);
                arr1.add(customer);
            } else if (opt == 1) {
                Employee employee = employeeService.readEmployee();
                employeeService.addEmployees(employee);
                arr1.add(employee);
            }
        }
//        TreeSet t1 = new TreeSet(arr);
        computer.setUsers((ArrayList) arr1);

        return computer;
    }

    public void calculateTotalTaxesById(int index){
        Computer computer = computers.stream()
                .filter(r -> r.getId() == index)
                .findAny()
                .orElse(null);
        double taxes = 0.0;
        if(computer != null){
            if(computer.getUsers() != null){
                for(User user: computer.getUsers()){
                    if(user instanceof Customer){
                        Customer customer = (Customer) user;
                        taxes += customer.getTaxes();
                    }
                }
                System.out.println("Computer id: " + index + " -> taxes: " + taxes);
            } else {
                System.out.println("0 Users");
            }
        } else {
            System.out.println("Computer not found");
        }


    }

    @Override
    public String getAntet(){
        return "";
    }

    @Override
    public Computer processLine(String line) throws ParseException{
        return null;
    }

    @Override
    public String getFileName(){
        return "";
    }

    @Override
    public String convertObjectToString(Computer object) {
        String line = "";
        return line;
    }

    public void initList(List<Computer> objects){
        this.computers = new ArrayList<>(objects);
    }


    public List<Computer> read() {
        String fileNameUser = "src/com/company/resources/CSV PAO Daria - Computer_User.csv";
        String fileNameMalware = "src/com/company/resources/CSV PAO Daria - Computer_Malware.csv";
        File file1 = new File(fileNameUser);
        File file2 = new File(fileNameMalware);
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file1));
            BufferedReader bufferedReader1 = new BufferedReader(new FileReader(file2));
            List<Computer> result;

            try {
                List<Computer> resultLines = new ArrayList<Computer>();
                bufferedReader.readLine(); // skip first line
                bufferedReader1.readLine(); // skip first line
                String currentLine = bufferedReader.readLine();
                String currentLine1 = bufferedReader1.readLine();

                while (true) {
                    if (currentLine == null) {
                        result = resultLines;
                        break;
                    }
                    List<String> fields = List.of(currentLine.split(CSVWriter.separator));
                    fields = fields.stream()
                            .map(o -> Objects.equals(o, "null") ? "-1" : o)
                            .collect(Collectors.toList());
                    int computerId = Integer.parseInt(fields.get(0));
                    int employeeId = Integer.parseInt(fields.get(1));
                    int customerId = Integer.parseInt(fields.get(2));
                    CustomerService customerService = CustomerService.getInstance();
                    EmployeeService employeeService = EmployeeService.getInstance();

                    Computer computer = resultLines.stream()
                            .filter(r -> r.getId() == computerId)
                            .findAny()
                            .orElse(null);
                    if(computer != null){
                        resultLines.add(computer);
                        List<User> users;
                        if(computer.getUsers() != null) {
                             users = computer.getUsers();
                        } else {
                            users = new ArrayList<>();
                        }
                        customerService.getCustomers().stream()
                                .filter(r -> r.getId() == customerId)
                                .findAny().ifPresent(users::add);
                        employeeService.getEmployees().stream()
                                .filter(r -> r.getId() == employeeId)
                                .findAny().ifPresent(users::add);
                        computer.setUsers(new ArrayList(users));
                        int index = 0;
                        for(Computer element : resultLines){
                            if(element.getId() == computer.getId()){
                                resultLines.set(index, computer);
                                break;
                            }
                            index += 1;
                        }
                    } else {
                        computer = new Computer();
                        computer.setId(computerId);
                        List<User> users = new ArrayList<>();

                        customerService.getCustomers().stream()
                                .filter(r -> r.getId() == customerId)
                                .findAny().ifPresent(users::add);
                        employeeService.getEmployees().stream()
                                .filter(r -> r.getId() == employeeId)
                                .findAny().ifPresent(users::add);
                        computer.setUsers(new ArrayList(users));
                        resultLines.add(computer);
                    }
                    currentLine = bufferedReader.readLine();
                }


                while (true) {
                    if (currentLine1 == null) {
                        result = resultLines;
                        break;
                    }
                    List<String> fields = List.of(currentLine1.split(CSVWriter.separator));
                    //System.out.println(currentLine1);
                    fields = fields.stream()
                            .map(o -> Objects.equals(o, "null") ? "-1" : o)
                            .collect(Collectors.toList());
                    int computerId = Integer.parseInt(fields.get(0));
                    int rootkitId = Integer.parseInt(fields.get(1));
                    int keyloggerId = Integer.parseInt(fields.get(2));
                    int kernelKeyloggerId = Integer.parseInt(fields.get(3));
                    int ransomewareId = Integer.parseInt(fields.get(4));
                    RootkitService rootkitService = RootkitService.getInstance();
                    KeyloggerService keyloggerService = KeyloggerService.getInstance();
                    RansomewareService ransomewareService = RansomewareService.getInstance();
                    KernelKeyloggerService kernelKeyloggerService = KernelKeyloggerService.getInstance();
                    Computer computer = resultLines.stream()
                            .filter(r -> r.getId() == computerId)
                            .findAny()
                            .orElse(null);
                    if(computer != null){
                        //resultLines.add(computer);
                        List<Malware> malwares;
                        if(computer.getMalwares() != null) {
                            malwares = computer.getMalwares();
                        } else {
                            malwares = new ArrayList<>();
                        }
                        rootkitService.getRootkits().stream()
                                .filter(r -> r.getId() == rootkitId)
                                .findAny().ifPresent(malwares::add);
                        keyloggerService.getKeyloggers().stream()
                                .filter(r -> r.getId() == keyloggerId)
                                .findAny().ifPresent(malwares::add);
                        ransomewareService.getRansomewares().stream()
                                .filter(r -> r.getId() == ransomewareId)
                                .findAny().ifPresent(malwares::add);
                        kernelKeyloggerService.getKernelKeyloggers().stream()
                                .filter(r -> r.getId() == kernelKeyloggerId)
                                .findAny().ifPresent(malwares::add);
                        computer.setMalwares(new ArrayList(malwares));
                        int index = 0;
                        for(Computer element : resultLines){
                            if(element.getId() == computer.getId()){
                                resultLines.set(index, computer);
                                resultLines.set(index, computer);
                                break;
                            }
                            index += 1;
                        }
                    } else {
                        computer = new Computer();
                        computer.setId(computerId);
                        List<Malware> malwares = new ArrayList<>();
                        rootkitService.getRootkits().stream()
                                .filter(r -> r.getId() == rootkitId)
                                .findAny().ifPresent(malwares::add);
                        keyloggerService.getKeyloggers().stream()
                                .filter(r -> r.getId() == keyloggerId)
                                .findAny().ifPresent(malwares::add);
                        ransomewareService.getRansomewares().stream()
                                .filter(r -> r.getId() == ransomewareId)
                                .findAny().ifPresent(malwares::add);
                        kernelKeyloggerService.getKernelKeyloggers().stream()
                                .filter(r -> r.getId() == kernelKeyloggerId)
                                .findAny().ifPresent(malwares::add);
                        computer.setMalwares(new ArrayList(malwares));
                        resultLines.add(computer);
                    }
                    currentLine1 = bufferedReader1.readLine();
                }
            } catch (Throwable anything) {
                try {
                    bufferedReader.close();
                } catch (Throwable something) {
                    anything.addSuppressed(something);
                }
                throw anything;
            }

            bufferedReader.close();
            initList(result);
            return result;
        } catch (FileNotFoundException e1) {
            System.out.println("File not found");
            initList(Collections.emptyList());
            return Collections.emptyList();
        } catch (IOException e2) {
            System.out.println("Cannot read from file");
            initList(Collections.emptyList());
            return Collections.emptyList();
        }
    }

    public void write(List<Computer> objects){
        String fileNameMalware = "src/com/company/resources/CSV PAO Daria - Computer_Malware.csv";
        File fileMalware = new File(fileNameMalware);
        String fileName = "src/com/company/resources/CSV PAO Daria - Computer_User.csv";
        File file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(fileMalware, false));
            try{
                String CSVline = "Id,Id Rootkit,Id Keylogger,Id KernelKeylogger,Id Ransomeware\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(Computer object : objects){
                    if(object.getMalwares() != null){
                        int id = object.getId();
                        String line = "";
                        List<Integer> rootkits = new ArrayList<>();
                        List<Integer> ransomewares = new ArrayList<>();
                        List<Integer> keyloggers = new ArrayList<>();
                        List<Integer> kernelKeyloggers = new ArrayList<>();
                        for(Malware malware: object.getMalwares()){
                            if(malware instanceof Rootkit){
                                Rootkit rootkit = (Rootkit) malware;
                                rootkits.add(rootkit.getId());
                            }
                            else if(malware instanceof Ransomeware){
                                Ransomeware ransomeware = (Ransomeware) malware;
                                ransomewares.add(ransomeware.getId());
                            }
                            else if(malware instanceof Keylogger){
                                if( malware instanceof KernelKeylogger){
                                    KernelKeylogger kernelKeylogger = (KernelKeylogger) malware;
                                    kernelKeyloggers.add(kernelKeylogger.getId());
                                }
                                else {
                                    Keylogger keylogger = (Keylogger) malware;
                                    keyloggers.add(keylogger.getId());
                                }
                            }
                        }
                        int nr = Integer.max(Integer.max(rootkits.size(), ransomewares.size()), Integer.max(kernelKeyloggers.size(), keyloggers.size()));
                        while(nr > 0){
                            line = id + CSVWriter.separator;
                            if(rootkits.size() > 0){
                                line += rootkits.get(0) + CSVWriter.separator;
                                rootkits.remove(0);
                            } else {
                                line += "null" + CSVWriter.separator;
                            }

                            if(keyloggers.size() > 0){
                                line += keyloggers.get(0) + CSVWriter.separator;
                                keyloggers.remove(0);
                            } else {
                                line += "null" + CSVWriter.separator;
                            }

                            if(kernelKeyloggers.size() > 0){
                                line += kernelKeyloggers.get(0) + CSVWriter.separator;
                                kernelKeyloggers.remove(0);
                            } else {
                                line += "null" + CSVWriter.separator;
                            }

                            if(ransomewares.size() > 0){
                                line += ransomewares.get(0);
                                ransomewares.remove(0);
                            } else {
                                line += "null";
                            }
                            line += "\n";
                            nr -= 1;
                            try{
                                bufferedWriter.write(line);
                            } catch (Throwable anything){
//                                try {
//                                    bufferedWriter.close();
//                                } catch (Throwable something) {
//                                    anything.addSuppressed(something);
//                                }
                                throw anything;
                            }
                        }

                    }
                }

            }
            try {
                bufferedWriter.close();
            } catch (Throwable something) {
                throw something;
            }
        } catch (IOException e1) {
            e1.printStackTrace();
        }

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = "Id,Id Employee,Id Customer\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(Computer object : objects){
                    if(object.getUsers() != null){
                        int id = object.getId();
                        String line = "";
                        List<Integer> customers = new ArrayList<>();
                        List<Integer> employees = new ArrayList<>();
                        for(User user: object.getUsers()){
                            if(user instanceof Customer){
                                Customer customer = (Customer) user;
                                customers.add(customer.getId());
                            }
                            else if(user instanceof Employee){
                                Employee employee = (Employee) user;
                                employees.add(employee.getId());
                            }
                        }
                        int nr = Integer.max(employees.size(), customers.size());
                        while(nr > 0){
                            line = id + CSVWriter.separator;
                            if(employees.size() > 0){
                                line += employees.get(0) + CSVWriter.separator;
                                employees.remove(0);
                            } else {
                                line += "null" + CSVWriter.separator;
                            }

                            if(customers.size() > 0){
                                line += customers.get(0);
                                customers.remove(0);
                            } else {
                                line += "null";
                            }

                            line += "\n";
                            nr -= 1;
                            try{
                                bufferedWriter.write(line);
                            } catch (Throwable anything){

                                throw anything;
                            }

                        }

                    }
                }

            }
            try {
                bufferedWriter.close();
            } catch (Throwable something) {
                throw something;
            }
        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }

}
