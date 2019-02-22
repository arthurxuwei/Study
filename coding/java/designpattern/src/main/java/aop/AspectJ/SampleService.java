package aop.AspectJ;

/**
 * Created by arthur.xw on 2015/6/17.
 */
public class SampleService {
    public String doService(String in) {
        System.out.println("inside doService");
        return in;
    }
}
