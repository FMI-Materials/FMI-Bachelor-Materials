package Laborator1;

public class Test {
    public static void main(String[] args) {

        int[] array = new int[5];
        Person person1 = new Person(10, "Radu", "Nae", array);
        Person person2 = person1;
        person1.array[0] = 5;
        System.out.println(person2.age);
        System.out.println(person1.array[0]);
        System.out.println(person2.array[0]);
        person2.array[4] = 6;
        System.out.println(person1.array[4]);
        System.out.println(person2.array[4]);
    }
}
