package interfaces;

public class Dog implements Animal {

    @Override
    public void makeSound() {
        System.out.println("ham");
    }

    @Override
    public void travel() {
        System.out.println("by foot");
    }
}
