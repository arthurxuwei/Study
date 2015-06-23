package RPC;

import RPC.invo.Invocation;
import RPC.util.Client;
import RPC.util.Listener;
import RPC.util.Server;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;
import java.util.HashMap;
import java.util.Map;
import java.lang.reflect.Method;
/**
 * Created by arthur.xw on 2015/6/23.
 */
public class RPCService {
    public static <T> T getProxy(final Class<T> clazz, String host, int port) {
        final Client client = new Client(host, port);
        InvocationHandler handler = new InvocationHandler() {
            @Override
            public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                Invocation invocation = new Invocation();
                invocation.setInterfaces(clazz);
                invocation.setMethod(new RPC.invo.Method(method.getName(), method.getParameterTypes()));
                invocation.setParams(args);
                client.invoke(invocation);
                return invocation.getResult();
            }
        };
        T t = (T) Proxy.newProxyInstance(RPCService.class.getClassLoader(), new Class[]{clazz}, handler);
        return t;
    }
    public static class RPCServer implements Server {
        private int port = 20382;
        private Listener listener;
        private boolean isRuning = true;

        public void setRuning(boolean isRuning) {
            this.isRuning = isRuning;
        }

        public void setPort(int port) {
            this.port = port;
        }

        @Override
        public int getPort() {
            return port;
        }

        private Map<String, Object> serviceEngine = new HashMap<String, Object>();

        @Override
        public void call(Invocation invocation) {
            System.out.println(invocation.getClass().getName());
            Object obj = serviceEngine.get(invocation.getInterfaces().getName());
            if (obj != null) {
                try {
                    Method m = obj.getClass().getMethod(
                            invocation.getMethod().getMethodName(), invocation.getMethod().getParams());
                    Object result = m.invoke(obj, invocation.getParams());
                    invocation.setResult(result);
                } catch (Throwable throwable) {
                    throwable.printStackTrace();
                }
            } else {
                throw new IllegalArgumentException("has no these class");
            }
        }

        @Override
        public void register(Class interfaceDefiner, Class impl) {
            try {
                this.serviceEngine.put(interfaceDefiner.getName(), impl.newInstance());
                System.out.println(serviceEngine);
            } catch (Throwable throwable) {
                throwable.printStackTrace();
            }
        }

        @Override
        public void start() {
            System.out.println("Start Server");
            listener = new Listener(this);
            this.isRuning = true;
            listener.start();
        }

        @Override
        public void stop() {
            this.setRuning(false);
        }

        @Override
        public boolean isRunning() {
            return isRuning;
        }
    }
}