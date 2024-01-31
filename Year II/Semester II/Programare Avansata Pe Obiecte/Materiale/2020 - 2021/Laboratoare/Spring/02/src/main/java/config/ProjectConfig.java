package config;

import beans.FirstBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan(basePackages = "beans")
public class ProjectConfig {

    @Bean
    public FirstBean firstBean() {
        var bean = new FirstBean();
        bean.setText("Hello");
        return bean;
    }
}
