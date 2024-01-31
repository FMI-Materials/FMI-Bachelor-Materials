package colectiiDeDate;

import java.util.*;

/*
    List = interfata care implementeaza Collection. Ca si implementari: ArrayList, LinkedList, Vector(nu se foloseste), Stack(nu se foloseste);

    Set = interfata care implementeaza Collection.

    Map = perechi (key,value). Nu accepta key duplicate.

 */
public class CollectiDeDate {

    public static void main(String[] args) {

//        var mySecondList = new ArrayList<Integer>();
//        mySecondList.add(1);
//
//        List<String> myFirstList = new ArrayList<>();
//        myFirstList.add("unu");
//        myFirstList.add("unu");
//        myFirstList.add("unu");
//        myFirstList.add("unu");
//        myFirstList.add("unu");
//        myFirstList.add("doi");
//
////        for(var x : myFirstList) {
////            System.out.println(x);
////        }
//
//        System.out.println(myFirstList.toString());
//
//        Set<String> set1 = new HashSet<>();
//        set1.add("ceva");
//        set1.add("ceva");
//        set1.add("ceva");
//        set1.add("ceva");
//        set1.add("ceva");
//        set1.add("ceva");
//        set1.add("altceva");
//
//        for(String s : set1) {
//            System.out.println(s);
//        }
//
//        Iterator<String> iterator = set1.iterator();
//        while(iterator.hasNext()) {
//            System.out.println(iterator.next());
//        }
//
//        System.out.println(set1.contains("ceva"));
//
//        System.out.println(set1.toString());

        Map<Integer, String> map1 = new HashMap<>();
        map1.put(1, "Vasile");
        map1.put(1, "Marius");
        map1.put(2, "ceva");

        for (int i : map1.keySet()) {
            System.out.println(map1.get(i));
        }
    }




}
