package ioc;

/**
 * Created by arthur.xw on 2015/6/19.
 */
public class SMSServiceInjector implements MessageServiceInjector {
    @Override
    public Consumer getConsumer() {
        return new Application(new SMSServiceImpl());
    }
}
