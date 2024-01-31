package com.company.entities;

import java.util.ArrayList;
import java.util.Date;
import java.util.Objects;

public class Ransomeware extends Malware {
    private double encryptionRating;
    private double hidingRating;

    public Ransomeware(){}

    public Ransomeware(int id, double rating, Date creationDate, String name, String infectionMethod, ArrayList<String> modifiedRegisters, double encryptionRating, double hidingRating) {
        super(id, rating, creationDate, name, infectionMethod, modifiedRegisters);
        this.encryptionRating = encryptionRating;
        this.hidingRating = hidingRating;
    }

    public double getEncryptionRating() {
        return encryptionRating;
    }

    public void setEncryptionRating(double encryptionRating) {
        this.encryptionRating = encryptionRating;
    }

    public double getHidingRating() {
        return hidingRating;
    }

    public void setHidingRating(double hidingRating) {
        this.hidingRating = hidingRating;
    }

    @Override
    public String toString() {
        return ("Malware name: " + this.name) + "\n" + "Malware type: Ransomeware" + '\n' + "Rating: " +
                this.rating + '\n' + "Infection Date: " + this.creationDate + '\n' + "Infection Method: " + this.infectionMethod + "\n";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Ransomeware that = (Ransomeware) o;
        return Double.compare(that.encryptionRating, encryptionRating) == 0 && Double.compare(that.hidingRating, hidingRating) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(encryptionRating, hidingRating);
    }
}
