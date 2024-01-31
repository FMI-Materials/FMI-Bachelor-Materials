package config;

import beans.MyFirstBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;

@Configuration
public class  ProjectConfig {

    @Bean("A")
    public MyFirstBean myFirstBean() {
        MyFirstBean bean = new MyFirstBean();
        bean.setText("Hello");
        return bean;
    }

    @Bean("myFirstBean")
    public MyFirstBean mySecondBean() {
        MyFirstBean bean = new MyFirstBean();
        bean.setText("World");
        return bean;
    }
}
