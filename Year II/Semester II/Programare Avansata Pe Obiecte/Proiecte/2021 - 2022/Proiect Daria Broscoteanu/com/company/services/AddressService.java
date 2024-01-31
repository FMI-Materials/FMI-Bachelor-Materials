package com.company.services;

import com.company.entities.Address;

import java.util.*;

public class AddressService implements AddressInterface, CSVReader<Address>, CSVWriter<Address> {
    private List<Address> addresses = new ArrayList<>();
    private static AddressService instance;

    private AddressService(){
        read();
    }

    public static AddressService getInstance(){
        if(instance == null){
            instance = new AddressService();
        }
        return instance;
    }

    public List<Address> getAddresses() {
        List<Address> addressesCopy = new ArrayList<>();
        addressesCopy.addAll(this.addresses);
        return addressesCopy;
    }

    public Address getAddressById(int index){
        Address address = new Address();
        for(int i = 0; i < this.addresses.size(); ++i){
            if(this.addresses.get(i).getId() == index){
                address = this.addresses.get(i);
            }
        }
        return address;
    }

    public void updateAddress(int index, Address address){
        for(int i = 0; i < this.addresses.size(); ++i){
            if(this.addresses.get(i).getId() == index){
                this.addresses.remove(i);
                this.addresses.add(i, address);
                break;
            }
        }
    }

    public void addAddress(Address address){
        this.addresses.add(address);
    }

    public void deleteRootkitById(int index){
        for(int i = 0; i < this.addresses.size(); ++i){
            if(this.addresses.get(i).getId() == index){
                this.addresses.remove(i);
                break;
            }
        }
    }

    public Address readAddress(){
        Scanner scanner = new Scanner(System.in);
        Address address = new Address();
        // System.out.println("Id");
        int id = getMaxId() + 1;
        address.setId(id);

        System.out.println("Address Line");
        address.setAddressLine(scanner.nextLine());

        System.out.println("Street");
        address.setStreet(scanner.nextLine());

        System.out.println("City");
        address.setCity(scanner.nextLine());

        System.out.println("Country");
        address.setCountry(scanner.nextLine());

        return address;
    }

    @Override
    public String getAntet() {
        return "Id,Street,City,Country,Address Line\n";
    }

    @Override
    public String getFileName() {
        String path = "src/com/company/resources/CSV PAO Daria - Address.csv";
        return path;
    }

    @Override
    public String convertObjectToString(Address object) {
        String line = object.getId() + CSVWriter.separator + object.getStreet() + CSVWriter.separator
                + object.getCity() + CSVWriter.separator + object.getCountry() + CSVWriter.separator + object.getAddressLine() + "\n";
        return line;
    }

    public int getMaxId(){
        int max = 0;
        for(int i = 0; i < addresses.size(); ++i){
            if(addresses.get(i).getId() > max){
                max = addresses.get(i).getId();
            }
        }
        return max;
    }

    @Override
    public Address processLine(String line){
        String[] fields = line.split(CSVWriter.separator);
        int id = 0;
        if(Objects.equals(fields[0], "null")){
            id = getMaxId();
        } else {
            try {
                id = Integer.parseInt(fields[0]);
            } catch (Exception e) {
                System.out.println("The id must be an int");
            }
        }
        String street = fields[1];
//        if(Objects.equals(street, "null")){
//            street = "";
//        }
        String city = fields[2];
//        if(Objects.equals(city, "null")){
//            city = "";
//        }
        String country = fields[3];
//        if(Objects.equals(country, "null")){
//            country = "";
//        }
        String addressLine = fields[4];
//        if(Objects.equals(addressLine, "null")){
//            addressLine = "";
//        }
        return new Address(id, street, city, country, addressLine);
    }


    public void initList(List<Address> objects){
        this.addresses = new ArrayList<Address>(objects);
    }
}
