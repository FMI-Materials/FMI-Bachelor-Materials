package exemplu3;

/*
    lazy = imi incarca datele atunci cand am nevoie de ele
 */

public class LazySingleton {

    private LazySingleton() {}

    private static LazySingleton instance = null;

    public static LazySingleton getInstance() {
        if(instance == null) {
            instance = new LazySingleton();
        }
        return instance;
    }

}
