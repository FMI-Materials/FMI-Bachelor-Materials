package com.company.entities;

import java.util.*;

// Rootkit's infection rating is determinated like this:
// If in the "configFiles" field we find one of the strings: "System Service Descriptor Table", "SSDT", "NtCreateFile", we add 100 to the rating
// If in the "imports" field we find "ntoskrnl.exe", we double the rating

public class Rootkit extends Malware {
    private Set<String> imports;
    private Set<String> configFiles;

    public Rootkit(){}

    public Rootkit(int id, double rating, Date creationDate, String name, String infectionMethod, ArrayList<String> modifiedRegisters, Set<String> imports, Set<String> configFiles) {
        super(id, rating, creationDate, name, infectionMethod, modifiedRegisters);
        this.imports = imports;
        this.configFiles = configFiles;
    }

    public Rootkit(Rootkit toCopy){
        super(toCopy);
        this.imports = toCopy.imports;
        this.configFiles = toCopy.configFiles;
    }

    public Set<String> getImports() {
        return imports;
    }

    public void setImports(Set<String> imports) {
        this.imports = imports;
    }

    public Set<String> getConfigFiles() {
        return configFiles;
    }

    public void setConfigFiles(Set<String> configFiles) {
        this.configFiles = configFiles;
    }

    @Override
    public String toString() {
        return ("Malware name: " + this.name) + "\n" + "Malware type: Rootkit" + '\n' + "Rating: " +
                this.rating + '\n' + "Infection Date: " + this.creationDate + '\n' + "Infection Method: " + this.infectionMethod;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Rootkit rootkit = (Rootkit) o;
        return Objects.equals(imports, rootkit.imports) && Objects.equals(configFiles, rootkit.configFiles);
    }

    @Override
    public int hashCode() {
        return Objects.hash(imports, configFiles);
    }
}
