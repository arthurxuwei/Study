package RPC.invo;

import java.io.Serializable;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class Method implements Serializable {
    private static final long serialVersionUID = 1L;
    private String methodName;
    private Class[] params;

    public Method(String name, Class<?>[] parameterTypes) {
        this.methodName = name;
        this.params = parameterTypes;
    }

    public String getMethodName() {
        return methodName;
    }

    public void setMethodName(String methodName) {
        this.methodName = methodName;
    }

    public Class[] getParams() {
        return params;
    }

    public void setParams(Class[] params) {
        this.params = params;
    }
}
