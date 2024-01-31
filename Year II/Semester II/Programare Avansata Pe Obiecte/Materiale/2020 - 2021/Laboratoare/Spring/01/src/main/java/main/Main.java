package main;

import beans.MyFirstBean;
import config.ProjectConfig;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Main {

    public static void main(String[] args) {

        try (var context = new AnnotationConfigApplicationContext(ProjectConfig.class)) {
            //retrieve beans by type
//            MyFirstBean b1 = context.getBean(MyFirstBean.class);
//            MyFirstBean b2 = context.getBean(MyFirstBean.class);
//
//            System.out.println(b1.getText());
//            System.out.println(b2.getText());

            //retrieve beans by name
//            MyFirstBean b3 = context.getBean("myFirstBean", MyFirstBean.class);
//            MyFirstBean b4 = context.getBean("mySecondBean", MyFirstBean.class);
//            System.out.println(b3.getText());
//            System.out.println(b4.getText());


            //retrieve beans by alias
            var b5 = context.getBean("A", MyFirstBean.class);
            var b6 = context.getBean("myFirstBean", MyFirstBean.class);
            System.out.println(b5.getText());
            System.out.println(b6.getText());
        }
    }
}
