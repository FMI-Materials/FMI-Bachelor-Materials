package polimorfism;

public class TestForAnimal {

    public static void main(String[] args) {

        Animal animal = new Animal();
        animal.makeSound();
        Animal animal2 = new Dog();
        animal2.makeSound();

        Cat cat = new Cat();
        cat.makeSound();
        Animal cat2 = new Cat();
        cat2.makeSound();

        Dog d1 = new Dog();

        Animal animal3 = (Animal) cat2;
        d1 = (Dog) animal3;
    }
}
