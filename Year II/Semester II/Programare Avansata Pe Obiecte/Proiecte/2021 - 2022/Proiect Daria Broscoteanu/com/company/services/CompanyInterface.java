package com.company.services;

import com.company.entities.Company;

import java.text.ParseException;
import java.util.List;

public interface CompanyInterface {
    public List<Company> getCompanies();

    public Company getCompanyById(int index);

    public void updateCompany(int index, Company company);

    public void addCompanies(Company company);

    public void deleteCompanyById(int index);

    public void deteleCompany(Company company);

    public Company readCompany() throws ParseException;

}
