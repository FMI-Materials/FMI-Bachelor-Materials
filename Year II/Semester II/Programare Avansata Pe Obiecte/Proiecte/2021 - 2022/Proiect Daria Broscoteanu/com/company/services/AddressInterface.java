package com.company.services;

import com.company.entities.Address;

import java.util.List;

public interface AddressInterface {
    public List<Address> getAddresses();

    public Address getAddressById(int index);

    public void updateAddress(int index, Address address);

    public void addAddress(Address address);

    public void deleteRootkitById(int index);

    public Address readAddress();
}
