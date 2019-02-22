package proxy.StaticProxy;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class CountProxy implements Count {
    private CountImpl countImpl;

    public CountProxy(CountImpl countImpl) {
        this.countImpl = countImpl;
    }

    @Override
    public void queryCount() {
        System.out.println("before process");
        countImpl.queryCount();
        System.out.println("after process");
    }

    @Override
    public void updateCount() {
        System.out.println("before process");
        countImpl.updateCount();
        System.out.println("after process");
    }
}
