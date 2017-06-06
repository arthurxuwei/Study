package RPC.util;

import RPC.invo.Invocation;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public interface Server {
    void stop();

    void start();

    void register(Class interfaceDefiner, Class impl);

    void call(Invocation invocation);

    boolean isRunning();

    int getPort();
}
