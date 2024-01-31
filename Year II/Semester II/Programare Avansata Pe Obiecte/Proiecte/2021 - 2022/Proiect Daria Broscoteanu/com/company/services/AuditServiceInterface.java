package com.company.services;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Timestamp;

public interface AuditServiceInterface {
    String separator = ",";

    default void audit(String action, String timestamp) {
        String pathCSV = "src/com/company/resources/audit.csv";
        try{
            File csvFile = new File(pathCSV);
            FileWriter writer = new FileWriter(pathCSV, true);
            if(csvFile.isFile()){
                if(csvFile.length() == 0L){
                    writer.append("Action,Timestamp\n");
                }
                String line = action + separator + timestamp + "\n";
                writer.append(line);
            }
            writer.close();
        } catch (IOException e){
            System.out.println("IOException");
        }

    }

}
