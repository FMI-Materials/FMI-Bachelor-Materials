package com.company.entities;

import java.util.ArrayList;
import java.util.List;

public class Computer {
    private int id;
    private List<Malware> malwares;
    private List<User> users;
    private double totalRating;

    public Computer(){}

    public Computer(int id, List<Malware> malwares, List<User> users, double totalRating) {
        this.malwares = malwares;
        this.users = users;
        this.totalRating = totalRating;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public List<Malware> getMalwares() {
        return malwares;
    }

    public void setMalwares(ArrayList malwares) {
        this.malwares = malwares;
    }

    public List<User> getUsers() {
        return users;
    }

    public void setUsers(ArrayList users) {
        this.users = users;
    }

    public double getTotalRating() {
        return totalRating;
    }

    public void setTotalRating(double totalRating) {
        this.totalRating = totalRating;
    }

    @Override
    public String toString(){
        String result = "Computer id: " + id + "\n";
        if(malwares != null) {
            for (Malware malware : malwares) {
                result += malware.toString();
            }
        }
        if(users != null) {
            for (User user : users) {
                result += user.toString();
            }
        }
        result += "\n---------------------------------------------------------------------------------------------------------------------------\n";
        return result;
    }

}
