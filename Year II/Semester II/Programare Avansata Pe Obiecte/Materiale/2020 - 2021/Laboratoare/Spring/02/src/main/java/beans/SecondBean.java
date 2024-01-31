package beans;

import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;

@Component
public class SecondBean {

    private String text;

    @PostConstruct
    public void init() {
        this.text = "World";
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }
}
