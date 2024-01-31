package com.company.services;

import com.company.entities.Ransomeware;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

public interface RansomewareInterface {
    public List<Ransomeware> getRansomewares();

    public Ransomeware getRansomewareById(int index);

    public void updateRansomeware(int index, Ransomeware ransomeware);

    public void addRansomeware(Ransomeware ransomeware);

    public void deleteRansomewareById(int index);

    public void deteleRansomeware(Ransomeware ransomeware);

    public double findRating(Ransomeware ransomeware);

    public Ransomeware readRansomeware() throws ParseException;
}
