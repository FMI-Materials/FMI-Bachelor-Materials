package interfaces;

public class Test {
    public static void main(String[] args) {
        Dog d = new Dog();
        d.makeSound();
        d.travel();
        d.makeSecondSound();
        System.out.println(Animal.age);
        System.out.println(Animal.noOfLegs);
    }
}
