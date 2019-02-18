package Proxy.dynamicProxy;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class TestMain {
    public static void main(String[] args) {
        DyProxy proxy = new DyProxy();
        BookFacade bookProxy = (BookFacade) proxy.bind(new BookFacadeImpl());
        bookProxy.addBook();
    }
}
