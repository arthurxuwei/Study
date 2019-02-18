package Proxy.StaticProxy;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class CountImpl implements Count {
    @Override
    public void queryCount() {
        System.out.println("query accout method");
    }

    @Override
    public void updateCount() {
        System.out.println("update accout method");
    }
}
