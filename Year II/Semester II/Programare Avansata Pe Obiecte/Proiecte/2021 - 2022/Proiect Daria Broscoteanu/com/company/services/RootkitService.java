package com.company.services;

import com.company.entities.Rootkit;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class RootkitService implements RootkitInterface, CSVReader<Rootkit>, CSVWriter<Rootkit>{
    private List<Rootkit> rootkits = new ArrayList<>();
    private static RootkitService instance;

    private RootkitService(){
        read();
    }

    public static RootkitService getInstance(){
        if(instance == null){
            instance = new RootkitService();
        }
        return instance;
    }

    public List<Rootkit> getRootkits() {
        List<Rootkit> rootkitsCopy = new ArrayList<>();
        rootkitsCopy.addAll(this.rootkits);
        return rootkitsCopy;
    }

    public Rootkit getRootkitById(int index){
        Rootkit rootkit = new Rootkit();
        for(int i = 0; i < this.rootkits.size(); ++i){
            if(this.rootkits.get(i).getId() == index){
                rootkit = this.rootkits.get(i);
            }
        }
        return rootkit;
    }

    public void updateRootkit(int index, Rootkit rootkit){
        for(int i = 0; i < this.rootkits.size(); ++i){
            if(this.rootkits.get(i).getId() == index){
                this.rootkits.remove(i);
                this.rootkits.add(i, rootkit);
                break;
            }
        }
    }

    public void addRootkit(Rootkit rootkit){
        this.rootkits.add(rootkit);
    }

    public void deleteRootkitById(int index){
        for(int i = 0; i < this.rootkits.size(); ++i){
            if(this.rootkits.get(i).getId() == index){
                this.rootkits.remove(i);
                break;
            }
        }
    }

    public double findRating(Rootkit rootkit){
        double rating = 0;
        if((rootkit.getModifiedRegisters().size() > 0) ){
            for (String element : rootkit.getModifiedRegisters()) {
                if (element.equals("HKLM-run") || element.equals("HKCU-run"))
                    rating += 20;
            }
        }
        List<String> specialImports = Arrays.asList("System Service Descriptor Table", "SSDT", "NtCreateFile");
        if(rootkit.getImports().size() > 0) {
            for (String element : rootkit.getImports()) {
                if (specialImports.contains(element))
                    rating += 100;
            }
        }

        if(rootkit.getConfigFiles().size() > 0) {
            for (String element : rootkit.getConfigFiles()) {
                if (element.equals("ntoskrnl.exe")) {
                    rating *= 2;
                    break;
                }
            }
        }
        rootkit.setRating(rating);
        return rating;
    }

    public void deteleRootkit(Rootkit rootkit){
        for(int i = 0;i < this.rootkits.size(); ++i){
            if(this.rootkits.get(i).equals(rootkit)){
                this.rootkits.remove(i);
                break;
            }
        }
    }

    public Rootkit readRootkit() throws ParseException {
        Scanner scanner = new Scanner(System.in);
        Rootkit rootkit = new Rootkit();
//        System.out.println("Id");
//
//        try {
//            rootkit.setId(scanner.nextInt());
//        } catch (Exception e){
//            System.out.println("Provide int");
//            rootkit.setId(scanner.nextInt());
//        }

        int id = getMaxId() + 1;
        rootkit.setId(id);

        System.out.println("Name");
        rootkit.setName(scanner.nextLine());

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
        rootkit.setCreationDate(date1);

        System.out.println("Infection Method");
        rootkit.setInfectionMethod(scanner.nextLine());

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
        rootkit.setModifiedRegisters(arr);

        System.out.println("Number of imports");
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
        System.out.println("Imports");
        Set<String> arr1 = new HashSet<>();
        for(int i = 0; i < nr; ++i){
            String str = scanner.nextLine();
            arr1.add(str);
        }
        rootkit.setImports(arr1);

        System.out.println("Number of Config Files");
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
        System.out.println("Config Files");
        Set<String> arr2 = new HashSet<>();
        for(int i = 0; i < nr; ++i){
            String str = scanner.nextLine();
            arr2.add(str);
        }
        rootkit.setConfigFiles(arr2);
        findRating(rootkit);
        return rootkit;
    }


    @Override
    public String getAntet() {
        return "";
    }

    @Override
    public Rootkit processLine(String line) throws ParseException {
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

        return new Rootkit(id, 0.0, date, name, infection, new ArrayList<>(), new HashSet<>(), new HashSet<>());

    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - Rootkit.csv";
        return path;
    }

    @Override
    public String convertObjectToString(Rootkit object) {
        Date date = object.getCreationDate();
        String dateString = new SimpleDateFormat("dd/MM/yyyy").format(date);
        String line = object.getId() + CSVWriter.separator + object.getName() + CSVWriter.separator + dateString + CSVWriter.separator + object.getInfectionMethod() + "\n";
        return line;
    }

    @Override
    public void initList(List<Rootkit> objects) {
        rootkits = new ArrayList<Rootkit>(objects);
    }

    public List<Rootkit> read() {
        String fileName = this.getFileName();
        File file = new File(fileName);
        String extraFileName = "src/com/company/resources/CSV PAO Daria - Rootkit_Extra.csv";
        File extraFile = new File(extraFileName);

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            List<Rootkit> result;

            try {
                List<Rootkit> resultLines = new ArrayList<Rootkit>();
                bufferedReader.readLine(); // skip first line
                String currentLine = bufferedReader.readLine();

                while (true) {
                    if (currentLine == null) {
                        result = resultLines;
                        break;
                    }
                    Rootkit obj = this.processLine(currentLine);
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
                        Rootkit rootkit = resultLines.stream()
                                .filter(r -> r.getId() == id)
                                .findAny()
                                .orElse(null);
                        if(rootkit != null){
                            if(rootkit.getModifiedRegisters().size() == 0){
                                List<String> reg = new ArrayList<String>();
                                reg.add(fields[1]);
                                rootkit.setModifiedRegisters(reg);
                            } else {
                                List<String> reg = rootkit.getModifiedRegisters();
                                reg.add(fields[1]);
                                rootkit.setModifiedRegisters(reg);
                            }
                            if(rootkit.getImports().size() == 0){
                                Set<String> func = new HashSet<>();
                                func.add(fields[2]);
                                rootkit.setImports(func);
                            } else {
                                Set<String> func = rootkit.getImports();
                                func.add(fields[2]);
                                rootkit.setImports(func);
                            }
                            if(rootkit.getConfigFiles().size() == 0){
                                Set<String> keys = new HashSet<>();
                                keys.add(fields[3]);
                                rootkit.setConfigFiles(keys);
                            } else {
                                Set<String> keys = rootkit.getConfigFiles();
                                keys.add(fields[3]);
                                rootkit.setConfigFiles(keys);
                            }
                            int index = 0;
                            for(Rootkit element : resultLines){
                                if(element.getId() == rootkit.getId()){
                                    findRating(rootkit);
                                    resultLines.set(index, rootkit);
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
        for(int i = 0; i < rootkits.size(); ++i){
            if(rootkits.get(i).getId() > max){
                max = rootkits.get(i).getId();
            }
        }
        return max;
    }

    public void write(List<Rootkit> objects){
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
                for(Rootkit object : objects){
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
        fileName = "src/com/company/resources/CSV PAO Daria - Rootkit_Extra.csv";
        file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = "Id,Modified Register,Import,Config Files\n";
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }
            if(objects != null){
                for(Rootkit object : objects){
                    List<String> reg = object.getModifiedRegisters();
                    List<String> func = new ArrayList<>(object.getImports());
                    List<String> keys  = new ArrayList<>(object.getConfigFiles());
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

                        if(func.size() > 0){;
                            CSVline += func.get(0)  + CSVWriter.separator;
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
