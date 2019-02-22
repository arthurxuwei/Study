package ioc;

/**
 * Created by arthur.xw on 2015/6/18.
 */
public class TestMain {
    public static void main(String[] args) {
        String msg = "Hi~";
        String email = "abc@abc.com";
        String phone = "4008008800";
        MessageServiceInjector injector = null;
        Consumer app = null;

        //Send email
        injector = new EmailServiceInjector();
        app = injector.getConsumer();
        app.processMessage(msg, email);

        //Send SMS
        injector = new SMSServiceInjector();
        app = injector.getConsumer();
        app.processMessage(msg, phone);

    }
}
