package Proxy;

import java.awt.*;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class FirstInterceptor implements Interceptor {

    @Override
    public void intercept(ActionInvocation invocation) {
        System.out.println(1);
        invocation.invoke();
        System.out.println(-1);
    }
}
