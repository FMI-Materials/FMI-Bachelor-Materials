package mostenire;

public class TestCar {

    public static void main(String[] args) {
        Car car = new Car();
        car.brand="BMW";
        car.combustible="diesel";
        car.color="black";
        car.noOfWheels = 4;

        car.honk();
        System.out.println(car.toString());

    }
}
