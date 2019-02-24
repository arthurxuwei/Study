package state;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class CeilingFanPullChain {
    private State currentState;

    public CeilingFanPullChain() {
        this.currentState = new Off();
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

    public void pull() {
        currentState.pull(this);
    }
}

interface State {
    void pull(CeilingFanPullChain wrapper);
}

class Off implements State {
    @Override
    public void pull(CeilingFanPullChain wrapper) {
        wrapper.setCurrentState(new Low());
        System.out.println("low speed");
    }
}

class Low implements State {
    @Override
    public void pull(CeilingFanPullChain wrapper) {
        wrapper.setCurrentState(new Medium());
        System.out.println("medium speed");
    }
}

class Medium implements State {
    @Override
    public void pull(CeilingFanPullChain wrapper) {
        wrapper.setCurrentState(new High());
        System.out.println("high speed");
    }
}

class High implements State {
    @Override
    public void pull(CeilingFanPullChain wrapper) {
        wrapper.setCurrentState(new Off());
        System.out.println("turning off");
    }
}

/**
 * @author arthur.xw
 */
public class Demo {
    static String getLine() {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line = null;
        try {
            line = in.readLine();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return line;
    }
    public static void main(String[] args) {
        CeilingFanPullChain chain = new CeilingFanPullChain();
        while (true) {
            System.out.print("Press ENTER");
            getLine();
            chain.pull();
        }
    }
}
