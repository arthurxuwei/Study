package proxy.StaticProxy;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class TestMain {
    public static void  main(String[] args) {
        CountImpl countImpl = new CountImpl();
        CountProxy countProxy = new CountProxy(countImpl);
        countProxy.updateCount();
        countProxy.queryCount();

    }
}
