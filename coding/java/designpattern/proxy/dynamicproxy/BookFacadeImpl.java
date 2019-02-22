package proxy.dynamicProxy;

/**
 * Created by arthur.xw on 2015/6/16.
 */
public class BookFacadeImpl implements BookFacade {
    @Override
    public void addBook() {
        System.out.println("add book method.");
    }
}
