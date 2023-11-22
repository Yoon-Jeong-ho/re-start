package hello.servlet.basic;

import lombok.Getter;
import lombok.Setter;

@Getter @Setter    // 롬복이 해준다.
public class HelloData {
    private String username;
    private int age;


}
