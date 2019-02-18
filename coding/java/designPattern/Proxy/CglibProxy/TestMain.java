package Proxy.CglibProxy;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class TestMain {
    public static void main(String[] args) {
        CglibProxy cglib = new CglibProxy();
        BookFacadeImpl1 bookCglib = (BookFacadeImpl1) cglib.getInstance(new BookFacadeImpl1());
        bookCglib.addBook();
    }
}
