package com.company.services;

import com.company.entities.KernelKeylogger;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class KernelKeyloggerService implements KernelKeyloggerInterface, CSVReader<KernelKeylogger>, CSVWriter<KernelKeylogger> {
    private List<KernelKeylogger> kernelKeyloggers = new ArrayList<>();
    private static KernelKeyloggerService instance;

    private KernelKeyloggerService(){
        read();
    }

    public static KernelKeyloggerService getInstance(){
        if(instance == null){
            instance = new KernelKeyloggerService();
        }
        return instance;
    }

    public List<KernelKeylogger> getKernelKeyloggers() {
        List<KernelKeylogger> kernelKeyloggersCopy = new ArrayList<>();
        kernelKeyloggersCopy.addAll(this.kernelKeyloggers);
        return kernelKeyloggersCopy;
    }

    public KernelKeylogger getKernelKeyloggerById(int index){
        KernelKeylogger kernelKeylogger = new KernelKeylogger();
        for(int i = 0; i < this.kernelKeyloggers.size(); ++i){
            if(this.kernelKeyloggers.get(i).getId() == index){
                kernelKeylogger = this.kernelKeyloggers.get(i);
            }
        }
        return kernelKeylogger;
    }

    public void updateKernelKeylogger(int index, KernelKeylogger kernelKeylogger){
        for(int i = 0; i < this.kernelKeyloggers.size(); ++i){
            if(this.kernelKeyloggers.get(i).getId() == index){
                this.kernelKeyloggers.remove(i);
                this.kernelKeyloggers.add(i, kernelKeylogger);
                break;
            }
        }
    }

    public void addKernelKeylogger(KernelKeylogger kernelKeylogger){
        this.kernelKeyloggers.add(kernelKeylogger);
    }

    public void deleteKernelKeyloggerById(int index){
        for(int i = 0; i < this.kernelKeyloggers.size(); ++i){
            if(this.kernelKeyloggers.get(i).getId() == index){
                this.kernelKeyloggers.remove(i);
                break;
            }
        }
    }

    public void deteleKernelKeylogger(KernelKeylogger kernelKeylogger){
        for(int i = 0;i < this.kernelKeyloggers.size(); ++i){
            if(this.kernelKeyloggers.get(i).equals(kernelKeylogger)){
                this.kernelKeyloggers.remove(i);
                break;
            }
        }
    }

    public double findRating(KernelKeylogger kernelKeylogger){
        double rating = 0;
        if((kernelKeylogger.getModifiedRegisters().size() > 0) ){
            for (String element : kernelKeylogger.getModifiedRegisters()) {
                if (element.equals("HKLM-run") || element.equals("HKCU-run"))
                    rating += 20;
            }
        }
        if(kernelKeylogger.getUsedFunctions().size() > 0) {
            for (String element : kernelKeylogger.getUsedFunctions()) {
                if (element.equals("CreateFileW") || element.equals("OpenProcess") || element.equals("ReadFile") || element.equals("WriteFile") || element.equals("RegisterHotKey") || element.equals("SetWindowsHookEx"))
                    rating += 30;
            }
        }
        if(kernelKeylogger.getUsedKeys().size() > 0){
            for (String element : kernelKeylogger.getUsedKeys()) {
                if (element.equals("[Up]") || element.equals("[Num Lock]") || element.equals("[Down]") || element.equals("[Right]") || element.equals("[UP]") || element.equals("[Left]") || element.equals("[PageDown]"))
                    rating += 10;
            }
        }
        if(kernelKeylogger.isHidingRecords()){
            rating += 30;
        }
        if(kernelKeylogger.isHidingFiles()){
            rating += 20;
        }
        kernelKeylogger.setRating(rating);
        return rating;
    }

    public KernelKeylogger readKernelkeylogger() throws ParseException {
        Scanner scanner = new Scanner(System.in);
        KernelKeylogger kernelKeylogger = new KernelKeylogger();
//        System.out.println("Id");
//        try {
//            kernelKeylogger.setId(scanner.nextInt());
//        } catch (Exception e){
//            System.out.println("Provide int");
//            kernelKeylogger.setId(scanner.nextInt());
//        }

        int id = getMaxId() + 1;
        kernelKeylogger.setId(id);

        System.out.println("Name");
        kernelKeylogger.setName(scanner.nextLine());

        System.out.println("Creation Date - dd/mm/yyyy");
        //String date;
        Date date1;
        while(true){
            String line = scanner.nextLine();
            try {
                date1 = new SimpleDateFormat("dd/MM/yyyy").parse(line);
                break;
            } catch (Exception e){
                System.out.println("Provide date in format - dd/mm/yyyy");
            }
        }
//        try {
//            date = scanner.nextLine();
//        } catch (Exception e){
//            System.out.println("Provide date in format - dd/mm/yyyy");
//            date = scanner.nextLine();
//        }
//        Date;
        kernelKeylogger.setCreationDate(date1);

        System.out.println("Infection Method");
        kernelKeylogger.setInfectionMethod(scanner.nextLine());

        System.out.println("Number of modified registers");
        int nr ;
        while(true){
            String line = scanner.nextLine();
            try {
                nr = Integer.parseInt(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }
        //scanner.nextLine();
        System.out.println("Modified registers");
        List<String> arr = new ArrayList<>();
        for(int i = 0; i < nr; ++i){
            String str = scanner.nextLine();
            arr.add(str);
        }
        kernelKeylogger.setModifiedRegisters(arr);

        System.out.println("Number of used functions");
//        int nr ;
        while(true){
            String line = scanner.nextLine();
            try {
                nr = Integer.parseInt(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }
        //scanner.nextLine();
        System.out.println("Used Functions");
        List<String> arr1 = new ArrayList<>();
        for(int i = 0; i < nr; ++i){
            String str = scanner.nextLine();
            arr1.add(str);
        }
        kernelKeylogger.setUsedFunctions(arr1);

        System.out.println("Number of used keys");
//        int nr ;
        while(true){
            String line = scanner.nextLine();
            try {
                nr = Integer.parseInt(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }
        //scanner.nextLine();
        System.out.println("Used keys");
        List<String> arr2 = new ArrayList<>();
        for(int i = 0; i < nr; ++i){
            String str = scanner.nextLine();
            arr2.add(str);
        }
        kernelKeylogger.setUsedKeys(arr2);
        System.out.println("Is hiding files?");
        boolean  ok;
        while(true){
            String line = scanner.nextLine();
            try {
                ok = Boolean.parseBoolean(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }
        kernelKeylogger.setHidingFiles(ok);
        System.out.println("Is hiding records?");
        while(true){
            String line = scanner.nextLine();
            try {
                ok = Boolean.parseBoolean(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a number");
            }
        }kernelKeylogger.setHidingRecords(ok);

//        try {
//            kernelKeylogger.setHidingRecords(scanner.nextBoolean());
//        } catch (Exception e){
//            System.out.println("Enter a boolean");
//            kernelKeylogger.setHidingRecords(scanner.nextBoolean());
//        }

        findRating(kernelKeylogger);
        return kernelKeylogger;
    }


    @Override
    public String getAntet() {
        return "";
    }

    @Override
    public KernelKeylogger processLine(String line) throws ParseException {
        String[] fields = line.split(CSVWriter.separator);
        int id = 0;
        try{
            id = Integer.parseInt(fields[0]);
        } catch (Exception e){
            System.out.println("The id must be an int");
        }
        String name = fields[1];
        Date date = new SimpleDateFormat("dd/MM/yyyy").parse(fields[2]);
        String infection = fields[3];

        String records = fields[4];
        boolean ok1 = false;
        if(Objects.equals(records, "TRUE")){
            ok1 = true;
        }

        boolean ok2 = false;
        String files = fields[5];
        if(Objects.equals(files, "TRUE")){
            ok2 = true;
        }
        return new KernelKeylogger(id, 0.0, date, name, infection, new ArrayList<>(), new ArrayList<>(), new ArrayList<>(), ok1, ok2);

    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - KernelKeylogger.csv";
        return path;
    }

    @Override
    public String convertObjectToString(KernelKeylogger object) {
        String ok1 = "FALSE", ok2 = "FALSE";
        if(object.isHidingRecords()){
            ok1 = "TRUE";
        }
        if(object.isHidingFiles()){
            ok2 = "TRUE";
        }
        Date date = object.getCreationDate();
        String dateString = new SimpleDateFormat("dd/MM/yyyy").format(date);
        String line = object.getId() + CSVWriter.separator + object.getName() + CSVWriter.separator + dateString
                + CSVWriter.separator + object.getInfectionMethod() + CSVWriter.separator + ok1 + CSVWriter.separator + ok2+  "\n";
        return line;
    }

    @Override
    public void initList(List<KernelKeylogger> objects) {
        kernelKeyloggers = new ArrayList<KernelKeylogger>(objects);
    }

    public List<KernelKeylogger> read() {
        String fileName = this.getFileName();
        File file = new File(fileName);
        String extraFileName = "src/com/company/resources/CSV PAO Daria - KernelKeylogger_Extra.csv";
        File extraFile = new File(extraFileName);

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            List<KernelKeylogger> result;

            try {
                List<KernelKeylogger> resultLines = new ArrayList<KernelKeylogger>();
                bufferedReader.readLine(); // skip first line
                String currentLine = bufferedReader.readLine();

                while (true) {
                    if (currentLine == null) {
                        result = resultLines;
                        break;
                    }
                    KernelKeylogger obj = this.processLine(currentLine);
                    resultLines.add(obj);
                    currentLine = bufferedReader.readLine();
                }
                BufferedReader extra = new BufferedReader(new FileReader(extraFile));
                try{
                    extra.readLine();
                    String line = extra.readLine();
                    while (true) {
                        if (line == null) {
                            break;
                        }
                        String[] fields = line.split(CSVWriter.separator);
                        int id = Integer.parseInt(fields[0]);
                        KernelKeylogger kernelKeylogger = resultLines.stream()
                                .filter(r -> r.getId() == id)
                                .findAny()
                                .orElse(null);
                        if(kernelKeylogger != null){
                            if(kernelKeylogger.getModifiedRegisters().size() == 0){
                                List<String> reg = new ArrayList<String>();
                                reg.add(fields[1]);
                                kernelKeylogger.setModifiedRegisters(reg);
                            } else {
                                List<String> reg = kernelKeylogger.getModifiedRegisters();
                                reg.add(fields[1]);
                                kernelKeylogger.setModifiedRegisters(reg);
                            }
                            if(kernelKeylogger.getUsedFunctions().size() == 0){
                                List<String> func = new ArrayList<String>();
                                func.add(fields[2]);
                                kernelKeylogger.setUsedFunctions(func);
                            } else {
                                List<String> func = kernelKeylogger.getUsedFunctions();
                                func.add(fields[2]);
                                kernelKeylogger.setUsedFunctions(func);
                            }
                            if(kernelKeylogger.getUsedKeys().size() == 0){
                                List<String> keys = new ArrayList<String>();
                                keys.add(fields[3]);
                                kernelKeylogger.setUsedKeys(keys);
                            } else {
                                List<String> keys = kernelKeylogger.getUsedFunctions();
                                keys.add(fields[3]);
                                kernelKeylogger.setUsedKeys(keys);
                            }
                            int index = 0;
                            for(KernelKeylogger element : resultLines){
                                if(element.getId() == kernelKeylogger.getId()){
                                    findRating(kernelKeylogger);
                                    resultLines.set(index, kernelKeylogger);
                                    break;
                                }
                                index += 1;
                            }
                        }

                        line = extra.readLine();
                    }
                } catch (Throwable t){
                    try {
                        extra.close();
                    } catch (Throwable s) {
                        t.addSuppressed(s);
                    }
                    throw t;
                }
                result = resultLines;

            } catch (Throwable anything) {
                try {
                    bufferedReader.close();
                } catch (Throwable something) {
                    anything.addSuppressed(something);
                }
                throw anything;
            }

            //bufferedReader.close();
            initList(result);
            return result;
        } catch (FileNotFoundException e1) {
            System.out.println("File not found");
            initList(Collections.emptyList());
            return Collections.emptyList();
        } catch (IOException | ParseException e2) {
            System.out.println("Cannot read from file");
            initList(Collections.emptyList());
            return Collections.emptyList();
        }
    }

    public int getMaxId(){
        int max = 0;
        for(int i = 0; i < kernelKeyloggers.size(); ++i){
            if(kernelKeyloggers.get(i).getId() > max){
                max = kernelKeyloggers.get(i).getId();
            }
        }
        return max;
    }

    public void write(List<KernelKeylogger> objects){
        String fileName = this.getFileName();
        File file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = "Id,Name,Creation Date,Infection Method,Is Hiding Records,Is Hiding Files\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(KernelKeylogger object : objects){
                    try{
                        String CSVline = this.convertObjectToString(object);
                        bufferedWriter.write(CSVline);
                    } catch (Throwable anything){
                        throw anything;
                    }
                }

            }
            bufferedWriter.close();
        } catch (IOException e1) {
            e1.printStackTrace();
        }
        fileName = "src/com/company/resources/CSV PAO Daria - KernelKeylogger_Extra.csv";
        file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = "Id,Modified Register,Used Function,Used Key\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(KernelKeylogger object : objects){
                    List<String> reg = object.getModifiedRegisters();
                    List<String> func = object.getUsedFunctions();
                    List<String> keys = object.getUsedKeys();
                    int nr = Integer.max(reg.size(), func.size());
                    nr = Integer.max(nr, keys.size());
                    while(nr > 0){
                        String CSVline = object.getId() + CSVWriter.separator;
                        if(reg.size() > 0){
                            CSVline += reg.get(0) + CSVWriter.separator;
                            reg.remove(0);
                        } else {
                            CSVline += "null" + CSVWriter.separator;
                        }

                        if(func.size() > 0){
                            CSVline += func.get(0) + CSVWriter.separator;
                            func.remove(0);
                        } else {
                            CSVline += "null" + CSVWriter.separator;
                        }

                        if(keys.size() > 0){
                            CSVline += keys.get(0);
                            keys.remove(0);
                        } else {
                            CSVline += "null";
                        }
                        try{
                            CSVline +=  "\n";
                            bufferedWriter.write(CSVline);
                        } catch (Throwable anything){
                            throw anything;
                        }
                        nr -= 1;
                    }
                }

            }
            bufferedWriter.close();
        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }

}
