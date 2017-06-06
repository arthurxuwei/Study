package RPC.util;

import RPC.invo.Invocation;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class Client {
    private String host;
    private int port;
    private Socket socket;
    private ObjectOutputStream oos;
    private ObjectInputStream ois;

    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public Client(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public void init() throws UnknownHostException, IOException {
        socket = new Socket(host, port);
        oos = new ObjectOutputStream(socket.getOutputStream());
    }

    public void invoke(Invocation invocation) throws IOException, ClassNotFoundException {
        init();
        System.out.println("write data.");
        oos.writeObject(invocation);
        oos.flush();
        ois = new ObjectInputStream(socket.getInputStream());
        Invocation result = (Invocation) ois.readObject();
        invocation.setResult(result.getResult());
    }
}
