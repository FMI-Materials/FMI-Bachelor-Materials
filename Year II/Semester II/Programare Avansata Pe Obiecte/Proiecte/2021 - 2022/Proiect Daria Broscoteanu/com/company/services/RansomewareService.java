package com.company.services;

import com.company.entities.Ransomeware;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class RansomewareService implements RansomewareInterface, CSVReader<Ransomeware>, CSVWriter<Ransomeware>{
    private List<Ransomeware> ransomewares = new ArrayList<>();
    private static RansomewareService instance;

    private RansomewareService(){
        read();
    }

    public static RansomewareService getInstance(){
        if(instance == null){
            instance = new RansomewareService();
        }
        return instance;
    }

    public List<Ransomeware> getRansomewares() {
        List<Ransomeware> ransomewaresCopy = new ArrayList<>();
        ransomewaresCopy.addAll(this.ransomewares);
        return ransomewaresCopy;
    }

    public Ransomeware getRansomewareById(int index){
        Ransomeware ransomeware = new Ransomeware();
        for(int i = 0; i < this.ransomewares.size(); ++i){
            if(this.ransomewares.get(i).getId() == index){
                ransomeware = this.ransomewares.get(i);
            }
        }
        return ransomeware;
    }

    public void updateRansomeware(int index, Ransomeware ransomeware){
        for(int i = 0; i < this.ransomewares.size(); ++i){
            if(this.ransomewares.get(i).getId() == index){
                this.ransomewares.remove(i);
                this.ransomewares.add(i, ransomeware);
                break;
            }
        }
    }

    public void addRansomeware(Ransomeware ransomeware){
        this.ransomewares.add(ransomeware);
    }

    public void deleteRansomewareById(int index){
        for(int i = 0; i < this.ransomewares.size(); ++i){
            if(this.ransomewares.get(i).getId() == index){
                this.ransomewares.remove(i);
                break;
            }
        }
    }

    public void deteleRansomeware(Ransomeware ransomeware){
        for(int i = 0;i < this.ransomewares.size(); ++i){
            if(this.ransomewares.get(i).equals(ransomeware)){
                this.ransomewares.remove(i);
                break;
            }
        }
    }

    public double findRating(Ransomeware ransomeware){
        double rating = 0;
        if((ransomeware.getModifiedRegisters().size() > 0) ){
            for (String element : ransomeware.getModifiedRegisters()) {
                if (element.equals("HKLM-run") || element.equals("HKCU-run"))
                    rating += 20;
            }
        }
        rating += ransomeware.getEncryptionRating() +  ransomeware.getHidingRating();
        ransomeware.setRating(rating);
        return rating;
    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - Ransomeware.csv";
        return path;
    }

    public Ransomeware readRansomeware() throws ParseException {
        Scanner scanner = new Scanner(System.in);
        Ransomeware ransomeware = new Ransomeware();
//        System.out.println("Id");
//        try {
//            ransomeware.setId(scanner.nextInt());
//        } catch (Exception e){
//            System.out.println("Provide int");
//            ransomeware.setId(scanner.nextInt());
//        }

        int id = getMaxId() + 1;
        ransomeware.setId(id);

        System.out.println("Name");
        ransomeware.setName(scanner.nextLine());

        System.out.println("Creation Date");
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
        ransomeware.setCreationDate(date1);

        System.out.println("Infection Method");
        ransomeware.setInfectionMethod(scanner.nextLine());

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
        ransomeware.setModifiedRegisters(arr);

        System.out.println("Encryption Rating");
        double rating ;
        while(true){
            String line = scanner.nextLine();
            try {
                rating = Double.parseDouble(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a double");
            }
        }
        ransomeware.setEncryptionRating(rating);

        System.out.println("Hiding Rating");
        while(true){
            String line = scanner.nextLine();
            try {
                rating = Double.parseDouble(line);
                break;
            } catch (Exception e){
                System.out.println("Enter a double");
            }
        }
        ransomeware.setHidingRating(rating);

        findRating(ransomeware);

        return ransomeware;
    }

    @Override
    public void initList(List<Ransomeware> objects) {
        ransomewares = new ArrayList<Ransomeware>(objects);
    }

    @Override
    public String convertObjectToString(Ransomeware object) {
        Date date = object.getCreationDate();
        String dateString = new SimpleDateFormat("dd/MM/yyyy").format(date);
        String line = object.getId() + CSVWriter.separator + object.getName() + CSVWriter.separator + dateString
                + CSVWriter.separator + object.getInfectionMethod() + CSVWriter.separator + object.getEncryptionRating()
                + CSVWriter.separator + object.getHidingRating()+  "\n";
        return line;
    }

    public List<Ransomeware> read() {
        String fileName = this.getFileName();
        File file = new File(fileName);
        String extraFileName = "src/com/company/resources/CSV PAO Daria - Ransomeware _Extra.csv";
        File extraFile = new File(extraFileName);

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            List<Ransomeware> result;

            try {
                List<Ransomeware> resultLines = new ArrayList<Ransomeware>();
                bufferedReader.readLine(); // skip first line
                String currentLine = bufferedReader.readLine();

                while (true) {
                    if (currentLine == null) {
                        result = resultLines;
                        break;
                    }
                    Ransomeware obj = this.processLine(currentLine);
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
                        Ransomeware ransomeware = resultLines.stream()
                                .filter(r -> r.getId() == id)
                                .findAny()
                                .orElse(null);
                        if(ransomeware != null){

                            if(ransomeware.getModifiedRegisters() == null){
                                List<String> reg = new ArrayList<String>();
                                reg.add(fields[1]);
                                ransomeware.setModifiedRegisters(reg);
                            } else {
                                List<String> reg = ransomeware.getModifiedRegisters();
                                reg.add(fields[1]);
                                ransomeware.setModifiedRegisters(reg);
                            }
                            int index = 0;
                            for(Ransomeware element : resultLines){
                                if(element.getId() == ransomeware.getId()){
                                    findRating(ransomeware);
                                    resultLines.set(index, ransomeware);
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

            bufferedReader.close();
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

    @Override
    public Ransomeware processLine(String line) throws ParseException {
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
        double encryption = 0.0;
        try{
            encryption = Double.parseDouble(fields[4]);
        } catch (Exception e){
            System.out.println("The encryption rating must be a double");
        }
        double hiding = 0.0;
        try{
            hiding = Double.parseDouble(fields[5]);
        } catch (Exception e){
            System.out.println("The hiding rating must be a double");
        }
        return new Ransomeware(id, 0.0, date, name, infection, new ArrayList<String>(), encryption, hiding);

    }

    public int getMaxId(){
        int max = 0;
        for(int i = 0; i < ransomewares.size(); ++i){
            if(ransomewares.get(i).getId() > max){
                max = ransomewares.get(i).getId();
            }
        }
        return max;
    }

    public String getAntet(){
        return "";
    }

    public void write(List<Ransomeware> objects){
        String fileName = this.getFileName();
        File file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = "Id,Name,Creation Date,Infection Method,Encryption Rating,Hiding Rating\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(Ransomeware object : objects){
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
        String fileName1 = "src/com/company/resources/CSV PAO Daria - Ransomeware _Extra.csv";
        File file1 = new File(fileName1);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file1, false));
            try{
                String CSVline = "Id,Modified Register\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(Ransomeware object : objects){
                    for(String reg : object.getModifiedRegisters()) {
                        try{
                            String CSVline = object.getId() + CSVWriter.separator + reg + "\n";
                            bufferedWriter.write(CSVline);
                        } catch (Throwable anything){
                            throw anything;
                        }
                    }
                }

            }
            bufferedWriter.close();
        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }


}
