package ioc;

/**
 * Created by arthur.xw on 2015/6/19.
 */
public class SMSServiceImpl implements MessageService {
    @Override
    public void sendMessage(String msg, String rec) {
        System.out.println("SMS sent to "+rec+" with Message="+msg);
    }
}
