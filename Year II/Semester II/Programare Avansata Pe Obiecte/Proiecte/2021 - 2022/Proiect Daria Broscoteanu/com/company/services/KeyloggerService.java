package com.company.services;

import com.company.entities.Keylogger;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class KeyloggerService implements KeyloggerInterface, CSVReader<Keylogger>, CSVWriter<Keylogger> {
    private List<Keylogger> keyloggers = new ArrayList<>();
    private static KeyloggerService instance;

    private KeyloggerService(){
        read();
    }

    public static KeyloggerService getInstance(){
        if(instance == null){
            instance = new KeyloggerService();
        }
        return instance;
    }

    public List<Keylogger> getKeyloggers() {
        List<Keylogger> keyloggersCopy = new ArrayList<>();
        keyloggersCopy.addAll(this.keyloggers);
        return keyloggersCopy;
    }

    public Keylogger getKeyloggerById(int index){
        Keylogger keylogger = new Keylogger();
        for(int i = 0; i < this.keyloggers.size(); ++i){
            if(this.keyloggers.get(i).getId() == index){
                keylogger = this.keyloggers.get(i);
            }
        }
        return keylogger;
    }

    public void updateKeylogger(int index, Keylogger keylogger){
        for(int i = 0; i < this.keyloggers.size(); ++i){
            if(this.keyloggers.get(i).getId() == index){
                this.keyloggers.remove(i);
                this.keyloggers.add(i, keylogger);
                break;
            }
        }
    }

    public void addKeylogger(Keylogger keylogger){
        this.keyloggers.add(keylogger);
    }

    public void deleteKeyloggerById(int index){
        for(int i = 0; i < this.keyloggers.size(); ++i){
            if(this.keyloggers.get(i).getId() == index){
                this.keyloggers.remove(i);
                break;
            }
        }
    }

    public void deteleKeylogger(Keylogger keylogger){
        for(int i = 0;i < this.keyloggers.size(); ++i){
            if(this.keyloggers.get(i).equals(keylogger)){
                this.keyloggers.remove(i);
                break;
            }
        }
    }

    public double findRating(Keylogger keylogger){
        double rating = 0;
        if((keylogger.getModifiedRegisters().size() > 0) ){
            for (String element : keylogger.getModifiedRegisters()) {
                if (element.equals("HKLM-run") || element.equals("HKCU-run"))
                    rating += 20;
            }
        }
        if(keylogger.getUsedFunctions().size() > 0) {
            for (String element : keylogger.getUsedFunctions()) {
                if (element.equals("CreateFileW") || element.equals("OpenProcess") || element.equals("OpenProcess") || element.equals("WriteFile") || element.equals("RegisterHotKey") || element.equals("SetWindowsHookEx"))
                    rating += 30;
            }
        }
        if(keylogger.getUsedKeys().size() > 0){
            for (String element : keylogger.getUsedKeys()) {
                if (element.equals("[Up]") || element.equals("[Num Lock]") || element.equals("[Down]") || element.equals("[Right]") || element.equals("[UP]") || element.equals("[Left]") || element.equals("[PageDown]"))
                    rating += 10;
            }
        }
        keylogger.setRating(rating);
        return rating;
    }

    public Keylogger readKeylogger() throws ParseException {
        Scanner scanner = new Scanner(System.in);
        Keylogger keylogger = new Keylogger();
//        System.out.println("Id");
//        try {
//            keylogger.setId(scanner.nextInt());
//        } catch (Exception e){
//            System.out.println("Provide int");
//            keylogger.setId(scanner.nextInt());
//        }

        int id = getMaxId() + 1;
        keylogger.setId(id);

        System.out.println("Name");
        keylogger.setName(scanner.nextLine());

        System.out.println("Creation Date - dd/mm/yyyy");
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
        keylogger.setCreationDate(date1);

        System.out.println("Infection Method");
        keylogger.setInfectionMethod(scanner.nextLine());

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
        keylogger.setModifiedRegisters(arr);

        System.out.println("Number of used functions");
        //int nr ;
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
        keylogger.setUsedFunctions(arr1);

        System.out.println("Number of used keys");
        //int nr ;
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
        keylogger.setUsedKeys(arr2);
        findRating(keylogger);
        return keylogger;
    }

    @Override
    public String getAntet() {
        return "";
    }

    @Override
    public Keylogger processLine(String line) throws ParseException {
        String[] fields = line.split(CSVWriter.separator);
        //System.out.println(line);
        int id = 0;
        try{
            id = Integer.parseInt(fields[0]);
        } catch (Exception e){
            System.out.println("The id must be an int");
        }
        String name = fields[1];
        Date date = new SimpleDateFormat("dd/MM/yyyy").parse(fields[2]);
        String infection = fields[3];

        return new Keylogger(id, 0.0, date, name, infection, new ArrayList<>(), new ArrayList<>(), new ArrayList<>());

    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - Keylogger.csv";
        return path;
    }

    @Override
    public String convertObjectToString(Keylogger object) {
        Date date = object.getCreationDate();
        String dateString = new SimpleDateFormat("dd/MM/yyyy").format(date);
        String line = object.getId() + CSVWriter.separator + object.getName() + CSVWriter.separator + dateString + CSVWriter.separator + object.getInfectionMethod() + "\n";
        return line;
    }

    @Override
    public void initList(List<Keylogger> objects) {
        keyloggers = new ArrayList<Keylogger>(objects);
    }

    public List<Keylogger> read() {
        String fileName = this.getFileName();
        File file = new File(fileName);
        String extraFileName = "src/com/company/resources/CSV PAO Daria - Keylogger_Extra.csv";
        File extraFile = new File(extraFileName);

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            List<Keylogger> result;

            try {
                List<Keylogger> resultLines = new ArrayList<Keylogger>();
                bufferedReader.readLine(); // skip first line
                String currentLine = bufferedReader.readLine();

                while (true) {
                    if (currentLine == null) {
                        result = resultLines;
                        break;
                    }
                    Keylogger obj = this.processLine(currentLine);
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
                        Keylogger keylogger = resultLines.stream()
                                .filter(r -> r.getId() == id)
                                .findAny()
                                .orElse(null);
                        if(keylogger != null){
                            if(keylogger.getModifiedRegisters().size() == 0){
                                List<String> reg = new ArrayList<String>();
                                reg.add(fields[1]);
                                keylogger.setModifiedRegisters(reg);
                            } else {
                                List<String> reg = keylogger.getModifiedRegisters();
                                reg.add(fields[1]);
                                keylogger.setModifiedRegisters(reg);
                            }
                            if(keylogger.getUsedFunctions().size() == 0){
                                List<String> func = new ArrayList<String>();
                                func.add(fields[2]);
                                keylogger.setUsedFunctions(func);
                            } else {
                                List<String> func = keylogger.getUsedFunctions();
                                func.add(fields[2]);
                                keylogger.setUsedFunctions(func);
                            }
                            if(keylogger.getUsedKeys().size() == 0){
                                List<String> keys = new ArrayList<String>();
                                keys.add(fields[3]);
                                keylogger.setUsedKeys(keys);
                            } else {
                                List<String> keys = keylogger.getUsedFunctions();
                                keys.add(fields[3]);
                                keylogger.setUsedKeys(keys);
                            }
                            int index = 0;
                            for(Keylogger element : resultLines){
                                if(element.getId() == keylogger.getId()){
                                    findRating(keylogger);
                                    resultLines.set(index, keylogger);
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
        for(int i = 0; i < keyloggers.size(); ++i){
            if(keyloggers.get(i).getId() > max){
                max = keyloggers.get(i).getId();
            }
        }
        return max;
    }

    public void write(List<Keylogger> objects){
        String fileName = this.getFileName();
        File file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = "Id,Name,Creation Date,Infection Method\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(Keylogger object : objects){
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
        fileName = "src/com/company/resources/CSV PAO Daria - Keylogger_Extra.csv";
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
                for(Keylogger object : objects){
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
