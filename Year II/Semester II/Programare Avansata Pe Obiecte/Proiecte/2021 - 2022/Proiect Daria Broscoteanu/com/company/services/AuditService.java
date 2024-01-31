package com.company.services;

import java.sql.Timestamp;

public class AuditService implements AuditServiceInterface{
    private static AuditService instance;

    private AuditService(){}

    public static AuditService getInstance(){
        if(instance == null){
            instance = new AuditService();
        }
        return instance;
    }
}
