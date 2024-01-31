package config;

import beans.Cat;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;

@Configuration
@ComponentScan(basePackages = "beans")
public class ProjectConfig {

    @Bean
    @Qualifier("cat1")
    public Cat cat1() {
        Cat c = new Cat();
        c.setName("Tom");
        return c;
    }

    @Bean
    @Qualifier("cat2")
    public Cat cat2() {
        Cat c = new Cat();
        c.setName("Tom2");
        return c;
    }

    /*
    Ce face spring in spate in cazul asta?
        1. Mai intai verifica daca exista in context un obiect de tipul Cat. Daca nu exista, atunci apeleaza metoda cat()
                                                                             Dar daca exista, imi da instanta care se afla deja in context
     */

//    @Bean
//    public Owner owner() {
//        Owner o = new Owner();
//        o.setCat(cat());
//        return o;
//    }


    /*
    daca am un parametru care este adnotat cu @Bean, spring se uita in context si aduce valoarea de acolo
     */
//    @Bean
//    public Owner owner(Cat cat) {
//        Owner o = new Owner();
//        o.setCat(cat);
//        return o;
//    }


}
