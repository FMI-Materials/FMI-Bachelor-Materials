package com.company;

import com.company.entities.Address;
import com.company.entities.Computer;
import com.company.entities.Employee;
import com.company.entities.Ransomeware;
import com.company.services.*;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

public class Main {

    public static void main(String[] args) throws ParseException, IOException {
        Service service = Service.getInstance();
        service.menu();
    }
}
