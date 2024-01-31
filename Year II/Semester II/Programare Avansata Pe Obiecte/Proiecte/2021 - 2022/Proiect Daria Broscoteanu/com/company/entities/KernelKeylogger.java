package com.company.entities;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;

// KernelKeylogger's infection rating is determinated like this:
// If is hiding records, we add 30;
// If is hiding files, we add 20.
public class KernelKeylogger extends Keylogger {
    private boolean isHidingRecords;
    private boolean isHidingFiles;

    public KernelKeylogger(){}

    public KernelKeylogger(int id, double rating, Date creationDate, String name, String infectionMethod, ArrayList<String> modifiedRegisters, List<String> usedFunctions, List<String> usedKeys, boolean isHidingRecords, boolean isHidingFiles) {
        super(id, rating, creationDate, name, infectionMethod, modifiedRegisters, usedFunctions, usedKeys);
        this.isHidingRecords = isHidingRecords;
        this.isHidingFiles = isHidingFiles;
    }

    public boolean isHidingRecords() {
        return isHidingRecords;
    }

    public void setHidingRecords(boolean hidingRecords) {
        isHidingRecords = hidingRecords;
    }

    public boolean isHidingFiles() {
        return isHidingFiles;
    }

    public void setHidingFiles(boolean hidingFiles) {
        isHidingFiles = hidingFiles;
    }

    @Override
    public String toString() {
            return ("Malware name: " + this.name) + "\n" + "Malware type: Kernel-Keylogger" + '\n' + "Rating: " +
                    this.rating + '\n' + "Infection Date: " + this.creationDate + '\n' + "Infection Method: " + this.infectionMethod;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        KernelKeylogger that = (KernelKeylogger) o;
        return isHidingRecords == that.isHidingRecords && isHidingFiles == that.isHidingFiles;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), isHidingRecords, isHidingFiles);
    }
}
