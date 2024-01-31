package streams.Example1;

import java.util.List;
/*
        Streams API: a aparut din java 8
                    - nu aduce nicio performanta dar face codul mai citibil

        Streamurile au 2 parti: sursa (de unde vin valorile)
                                operatiile (intermediare si finale)
                      Pot avea oricate operatii intermediare dar, doar una singura finala deoarece cea finala inchide streamul


         Sursa ---> Operatie intermediara1 ---> Operatie intermediara2 ---> Operatie intermediara3 ---> .... ---> Operatie intermediara n ->
         Operatie finala

         Predicate = interfata functionala care primeste o valoare si returneaza true sau false
         Consumer = interfata functionala care consuma o valoare si nu returneaza nimic
         Function = interfata functionala care primeste tipul de intrare si tipul de iesire


 */
public class Example1 {

    public static void main(String[] args) {

        List<Integer> list = List.of(1,2,3,4,5,6,7,8,9);

//        for(int i : list) {
//            if (i % 2 == 0) {
//                System.out.println(i);
//            }
//        }

       list.stream()    // 1 2 3 4 5 6 7 8 9
           .filter(x -> x % 2 == 0) //2 4 6 8
           .forEach(x -> System.out.println(x));
    }



}
