package IoC;

/**
 * Created by arthur.xw on 2015/6/19.
 */
public class Application implements Consumer {
    private MessageService service;

    public Application(MessageService service) {
        this.service = service;
    }

    @Override
    public void processMessage(String msg, String rec) {
        this.service.sendMessage(msg, rec);
    }
}
