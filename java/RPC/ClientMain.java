package RPC;

import RPC.operator.Echo;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class ClientMain {
    public static void main(String[] args) {
        Echo echo = RPCService.getProxy(Echo.class, "127.0.0.1", 20382);
        System.out.println(echo.echo("hello, RPC"));
        System.out.println(echo.echo("hello, RPC"));

        System.out.println(echo.echo("Haha~"));

    }
}
