package com.company.services;

import com.company.entities.Computer;

import java.text.ParseException;
import java.util.List;

public interface ComputerInterface {
    public List<Computer> getComputers();

    public Computer getComputerById(int index);

    public void updateComputer(int index, Computer computer);

    public void addComputer(Computer computer);

    public void deleteComputerById(int index);

    public void deteleComputers(Computer computer);

    public double calculateTotalRating(Computer computer);

    public Computer readComputer() throws ParseException;

}
