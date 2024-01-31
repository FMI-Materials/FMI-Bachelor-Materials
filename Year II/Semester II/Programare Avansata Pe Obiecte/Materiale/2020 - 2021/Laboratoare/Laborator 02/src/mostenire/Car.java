package mostenire;

/*
    Modificatori acces: (de la cel mai permisiv la cel mai restrictiv)
        -public (am acces la metode/fielduri din tot proiectul)
        -protected (am acces la metode/fielduri prin mostenire)
        -default (am acces doar in pachet)
        -private (am acces doar din interiorul clasei)
 */

/*
    Reguli suprascriere:
        1. metoda care suprascrie trebuie sa fie cel putin la fel de privata ca metoda suprascrisa (daca am in superclasa protected, pot suprascrie cu public/proteced)
        2. metodele finale/statice nu pot fi suprascrise
        3. tipul returnat trebuie sa respecte principiul de covarianta (regulile polimorfismului)
        4. daca metoda suprascrisa arunca o exceptie, metoda care suprascrie trebuie sa nu arunce un spectru mai larg de exceptii
*/

public class Car extends Vehicle{
    String brand;
    String combustible;

    @Override
    public String toString() {
        return "Car{" +
                "brand='" + brand + '\'' +
                ", combustible='" + combustible + '\'' +
                ", color='" + color + '\'' +
                ", noOfWheels=" + noOfWheels +
                '}';
    }

    @Override
    public void m() {
        System.out.println("Inside class Car");
    }

//    public String getBrand() {
//        return brand;
//    }
//
//    public void setBrand(String brand) {
//        this.brand = brand;
//    }
//
//    public String getCombustible() {
//        return combustible;
//    }
//
//    public void setCombustible(String combustible) {
//        this.combustible = combustible;
//    }
}
