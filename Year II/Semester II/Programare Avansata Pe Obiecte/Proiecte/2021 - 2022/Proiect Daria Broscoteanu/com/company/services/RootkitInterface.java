package com.company.services;

import com.company.entities.Rootkit;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public interface RootkitInterface {
    public List<Rootkit> getRootkits();

    public Rootkit getRootkitById(int index);

    public void updateRootkit(int index, Rootkit rootkit);

    public void addRootkit(Rootkit rootkit);

    public void deleteRootkitById(int index);

    public double findRating(Rootkit rootkit);

    public void deteleRootkit(Rootkit rootkit);

    public Rootkit readRootkit() throws ParseException;
}
