package Laborator1;

import java.util.Scanner;

public class ExampleOne {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Hello user");
        System.out.println("Please insert a number");
        int firstNumber = scanner.nextInt();
        System.out.println(firstNumber);
        System.out.println("Please insert second number");
        int secondNumber = scanner.nextInt();
        int sum = sum(firstNumber, secondNumber);
        System.out.println(sum + " is the sum of the numbers");
    }

    public static int sum(int a, int b) {
        return a + b;
    }
}