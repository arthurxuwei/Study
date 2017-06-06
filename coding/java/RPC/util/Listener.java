package RPC.util;

import RPC.invo.Invocation;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class Listener extends Thread {
    private ServerSocket socket;
    private Server server;

    public Listener(Server server) {
        this.server = server;
    }

    @Override
    public void run() {
        System.out.println("Starting...on port " + server.getPort());

        try {
            socket = new ServerSocket(server.getPort());
        } catch (IOException e1) {
            e1.printStackTrace();
            return;
        }
        while (server.isRunning()) {
            try {
                Socket client = socket.accept();
                ObjectInputStream ois = new ObjectInputStream(client.getInputStream());
                Invocation invo = (Invocation) ois.readObject();
                server.call(invo);
                ObjectOutputStream oos = new ObjectOutputStream(client.getOutputStream());
                oos.writeObject(invo);
                oos.flush();
                oos.close();
                ois.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        try {
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
