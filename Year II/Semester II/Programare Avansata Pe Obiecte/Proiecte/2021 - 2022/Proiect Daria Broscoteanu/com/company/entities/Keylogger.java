package com.company.entities;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;
// Keylogger's infection rating is determinated like this:
// If in the "usedFunctions" field we find one of the strings: “CreateFileW”, “OpenProcess”, “ReadFile”, “WriteFile”, “RegisterHotKey”, “SetWindowsHookEx”, we add 30 to the rating
// If in the "usedFunctions" field we find one of the strings: “[Up]”, “[Num Lock]”, “[Down]”, “[Right]”, “[UP]”, “[Left]”, “[PageDown]”, we add 10 to the rating

public class Keylogger extends Malware {
    protected List<String> usedFunctions;
    protected List<String> usedKeys;

    public Keylogger(){}

    public Keylogger(int id, double rating, Date creationDate, String name, String infectionMethod, ArrayList<String> modifiedRegisters, List<String> usedFunctions, List<String> usedKeys) {
        super(id, rating, creationDate, name, infectionMethod, modifiedRegisters);
        this.usedFunctions = usedFunctions;
        this.usedKeys = usedKeys;
    }

    public List<String> getUsedFunctions() {
        return usedFunctions;
    }

    public void setUsedFunctions(List<String> usedFunctions) {
        this.usedFunctions = usedFunctions;
    }

    public List<String> getUsedKeys() {
        return usedKeys;
    }

    public void setUsedKeys(List<String> usedKeys) {
        this.usedKeys = usedKeys;
    }

    @Override
    public String toString() {
        return ("Malware name: " + this.name) + "\n" + "Malware type: Keylogger" + '\n' + "Rating: " +
                this.rating + '\n' + "Infection Date: " + this.creationDate + '\n' + "Infection Method: " + this.infectionMethod;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Keylogger keylogger = (Keylogger) o;
        return Objects.equals(usedFunctions, keylogger.usedFunctions) && Objects.equals(usedKeys, keylogger.usedKeys);
    }

    @Override
    public int hashCode() {
        return Objects.hash(usedFunctions, usedKeys);
    }
}

