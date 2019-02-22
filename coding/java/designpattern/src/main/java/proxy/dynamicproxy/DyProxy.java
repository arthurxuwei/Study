package proxy.dynamicproxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class DyProxy implements InvocationHandler {
    private Object target;

    /**
     * bind proxy object and return a proxy class
     * @param target
     * @return
     */
    public Object bind(Object target) {
        this.target = target;
        //bind interface(this is a defect, cglib make up it)
        return java.lang.reflect.Proxy.newProxyInstance(target.getClass().getClassLoader(),
                target.getClass().getInterfaces(), this);
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args)
            throws InvocationTargetException, IllegalAccessException {
        Object result = null;
        System.out.println("Before process");
        result = method.invoke(target, args);
        System.out.println("After process");
        return result;
    }
}
