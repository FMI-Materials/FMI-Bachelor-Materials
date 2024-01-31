package interfaces;

public interface Animal {

    public static final int age = 5;
    int noOfLegs = 4;

    public void makeSound();
    void travel();

    default void makeSecondSound() {
        System.out.println("SOUND");
    }
}
