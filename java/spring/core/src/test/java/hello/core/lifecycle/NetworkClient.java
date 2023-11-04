package hello.core.lifecycle;

import org.springframework.beans.factory.DisposableBean;
import org.springframework.beans.factory.InitializingBean;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

public class NetworkClient /*implements InitializingBean, DisposableBean*/ {
    private String url;

    public NetworkClient() {
        System.out.println("생성자 호출 = " + url);
    }

    public void setUrl(String url){
        this.url= url;
    }
    public void connect(){
        System.out.println("connect = " + url);
    }

    public void call(String message){
        System.out.println("url  = " + url + " message = " + message);
    }

    // 서비스종료시 호출
    public void disconnect(){
        System.out.println("close : "+ url);
    }

    @PostConstruct
    public void init() {
        System.out.println("NetworkClient.afterPropertiesSet");
        connect();
        call("초기화 생성 메세지");
    }

    @PreDestroy
    public void close() {
        System.out.println("NetworkClient.destroy");
        disconnect();
    }
}
