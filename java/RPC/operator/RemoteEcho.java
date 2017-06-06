package RPC.operator;

import RPC.operator.Echo;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class RemoteEcho implements Echo {
    public String echo(String echo) {
        return "from remote:" + echo;
    }
}
