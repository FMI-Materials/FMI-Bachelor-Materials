package Laborator1;

public class ExampleTwo {
    public static void main(String[] args) {
        int[] vector = new int[5];
        for(int i=0; i < vector.length; i++) {
            vector[i] = i;
        }

        for(int a : vector) {
            System.out.println(a);
        }
    }
}
