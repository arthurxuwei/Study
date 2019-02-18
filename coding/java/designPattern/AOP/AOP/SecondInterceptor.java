package AOP.AOP;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class SecondInterceptor implements Interceptor {

    @Override
    public void intercept(ActionInvocation invocation) {
        System.out.println(2);
        invocation.invoke();
        System.out.println(-2);
    }
}
