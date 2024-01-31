package com.company.services;

import com.company.entities.KernelKeylogger;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

public interface KernelKeyloggerInterface {
    public List<KernelKeylogger> getKernelKeyloggers();

    public KernelKeylogger getKernelKeyloggerById(int index);

    public void updateKernelKeylogger(int index, KernelKeylogger kernelKeylogger);

    public void addKernelKeylogger(KernelKeylogger kernelKeylogger);

    public void deleteKernelKeyloggerById(int index);

    public void deteleKernelKeylogger(KernelKeylogger kernelKeylogger);

    public double findRating(KernelKeylogger kernelKeylogger);

    public KernelKeylogger readKernelkeylogger() throws ParseException;
}
