package main;

import beans.Cat;
import beans.Owner;
import config.ProjectConfig;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Main {

    public static void main(String[] args) {
        /*
        Framework = solutie pentru a extrage codul duplicat
                    putem refolosi cod. spre exemplu pentru: logare, tranzactionabilitate, security etc.

        Context = cand vorbim de context, ne referim la managementul obiectelor care se afla in context, practic
                  se ocupa framework-ul de administrarea obiectelor.

        IOC = inversion of control = framework-ul administreaza clasele pe care i le dam, nu se mai ocupa aplicatia in sine de acest lucru,
                                     noi spunand modul in care se administreaza aceste obiecte
                 - Dependency injection: punerea in context a unor obiecte si a le cere cand avem nevoie de ele.
         */

//        try (var context = new AnnotationConfigApplicationContext(ProjectConfig.class)) {
//
//            //by type
////            var cat = context.getBean(Cat.class);
//            var owner = context.getBean(Owner.class);
////            System.out.println(cat);
//            System.out.println(owner);
//        }
        int i = 0;
        System.out.println(i++);
        

    }
}
