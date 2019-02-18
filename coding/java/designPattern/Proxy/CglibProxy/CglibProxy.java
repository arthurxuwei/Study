package Proxy.CglibProxy;

import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;

import java.lang.reflect.Method;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class CglibProxy implements MethodInterceptor {
    private Object target;

    public Object getInstance(Object target) {
        this.target = target;
        Enhancer enhancer = new Enhancer();
        enhancer.setSuperclass(this.target.getClass());
        enhancer.setCallback(this);
        return enhancer.create();
    }

    @Override
    public Object intercept(Object obj, Method method, Object[] args,
                              MethodProxy proxy) throws Throwable {
        System.out.println("begin process");
        proxy.invokeSuper(obj, args);
        System.out.println("after process");
        return null;
    }

}
