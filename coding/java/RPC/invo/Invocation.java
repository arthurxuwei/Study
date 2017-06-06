package RPC.invo;

import RPC.invo.Method;

import java.io.Serializable;
import java.util.Arrays;

/**
 * Created by arthur.xw on 2015/6/23.
 */
public class Invocation implements Serializable {
    private static final long serialVersionUID = 1L;

    private Class interfaces;
    private Method method;
    private Object[] params;
    private Object result;

    public Class getInterfaces() {
        return interfaces;
    }

    public void setInterfaces(Class interfaces) {
        this.interfaces = interfaces;
    }

    public Method getMethod() {
        return method;
    }

    public void setMethod(Method method) {
        this.method = method;
    }

    public Object[] getParams() {
        return params;
    }

    public void setParams(Object[] params) {
        this.params = params;
    }

    public void setResult(Object result) {
        this.result = result;
    }

    public Object getResult() {
        return result;
    }

    @Override
    public String toString() {
        return interfaces.getName() + "." +
                method.getMethodName() +
                "(" + Arrays.toString(params) + ")";
    }


}
