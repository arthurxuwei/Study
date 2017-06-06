package RPC;

import RPC.operator.Echo;
import RPC.operator.RemoteEcho;
import RPC.util.Server;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class ServerMain {
    public static void main(String[] args) {
        Server server = new RPCService.RPCServer();
        server.register(Echo.class, RemoteEcho.class);
        server.start();

    }
}
