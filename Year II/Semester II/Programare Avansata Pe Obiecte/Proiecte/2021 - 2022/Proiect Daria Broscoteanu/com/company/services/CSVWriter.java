package com.company.services;

import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public interface CSVWriter<T> {
    public String separator = ",";

    public String getAntet();

    public T processLine(String line) throws ParseException;

    public String getFileName();

    public String convertObjectToString(T object);

    public void initList(List<T> objects);


    default void write(List<T> objects){
        String fileName = this.getFileName();
        File file = new File(fileName);

        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));
            try{
                String CSVline = getAntet();
                bufferedWriter.write(CSVline);
            } catch (Throwable anything){
                throw anything;
            }

            if(objects != null){
                for(T object : objects){
                    try{
                        String CSVline = this.convertObjectToString(object);
                        //System.out.println(CSVline);
                        bufferedWriter.write(CSVline);
                    } catch (Throwable anything){

                        throw anything;
                    }
                }
                try {
                    bufferedWriter.close();
                } catch (Throwable something) {
                    throw something;
                }

            }

        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }
}
