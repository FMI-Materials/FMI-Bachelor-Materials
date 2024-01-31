package main;

import beans.FirstBean;
import beans.SecondBean;
import config.ProjectConfig;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Main {

    public static void main(String[] args) {

        try(var context = new AnnotationConfigApplicationContext(ProjectConfig.class)) {

            FirstBean b1 = context.getBean(FirstBean.class);
            SecondBean b2 = context.getBean(SecondBean.class);

            System.out.println(b1.getText());
            System.out.println(b2.getText());
        }
    }
}
