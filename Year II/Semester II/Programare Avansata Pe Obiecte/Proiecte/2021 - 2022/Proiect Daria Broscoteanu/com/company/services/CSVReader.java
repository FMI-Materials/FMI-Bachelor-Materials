package com.company.services;

import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public interface CSVReader<T>{
    public String separator = ",";

    public String getAntet();

    public T processLine(String line) throws ParseException;

    public String getFileName();

    public String convertObjectToString(T object);

    public void initList(List<T> objects);

    default List<T> read() {
        String fileName = this.getFileName();
        File file = new File(fileName);

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            List<T> result;

            try {
                List<T> resultLines = new ArrayList<T>();
                bufferedReader.readLine(); // skip first line
                String currentLine = bufferedReader.readLine();

                while (true) {
                    if (currentLine == null) {
                        result = resultLines;
                        break;
                    }
                    T obj = this.processLine(currentLine);
                    resultLines.add(obj);
                    currentLine = bufferedReader.readLine();
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
        } catch (FileNotFoundException | ParseException e1) {
            System.out.println("File not found");
            initList(Collections.emptyList());
            return Collections.emptyList();
        } catch (IOException e2) {
            System.out.println("Cannot read from file");
            initList(Collections.emptyList());
            return Collections.emptyList();
        }
    }

//    default void write(List<T> objects){
//        String fileName = this.getFileName();
//        File file = new File(fileName);
//
//        try{
//            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
//            try{
//                String CSVline = getAntet();
//                bufferedWriter.write(CSVline);
//            } catch (Throwable anything){
//                throw anything;
//            }
//
//            if(objects != null){
//                for(T object : objects){
//                    try{
//                        String CSVline = this.convertObjectToString(object);
//                        //System.out.println(CSVline);
//                        bufferedWriter.write(CSVline);
//                    } catch (Throwable anything){
//
//                        throw anything;
//                    }
//                }
//                try {
//                    bufferedWriter.close();
//                } catch (Throwable something) {
//                    throw something;
//                }
//
//            }
//
//        } catch (IOException e1) {
//            e1.printStackTrace();
//        }
//    }

}
