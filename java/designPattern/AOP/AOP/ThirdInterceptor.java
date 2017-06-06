package Proxy;

/**
 * Created by arthur.xw on 3015/6/16.
 */
public class ThirdInterceptor implements Interceptor {

    @Override
    public void intercept(ActionInvocation invocation) {
        System.out.println(3);
        invocation.invoke();
        System.out.println(-3);
    }
}
