package com.company.services;

import com.company.entities.Keylogger;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

public interface KeyloggerInterface {
    public List<Keylogger> getKeyloggers();

    public Keylogger getKeyloggerById(int index);

    public void updateKeylogger(int index, Keylogger keylogger);

    public void addKeylogger(Keylogger keylogger);

    public void deleteKeyloggerById(int index);

    public void deteleKeylogger(Keylogger keylogger);

    public double findRating(Keylogger keylogger);

    public Keylogger readKeylogger() throws ParseException;
}
