package ioc;

/**
 * Created by arthur.xw on 2015/6/19.
 */
public class EmailServiceImpl implements MessageService {
    @Override
    public void sendMessage(String msg, String rec) {
        System.out.println("Email send to "+rec+ "with Message=" + msg);
    }
}
