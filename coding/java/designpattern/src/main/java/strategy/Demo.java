package strategy;

interface Strategy {
    void solve();
}

abstract class StrategySolution implements Strategy {
    @Override
    public void solve() {
        start();
        while (nextTry() && !isSolution()) {
        }
        stop();
    }

    abstract void start();
    abstract boolean nextTry();
    abstract boolean isSolution();
    abstract void stop();
}

class FOO extends StrategySolution {
    private int state = 0;
    @Override
    void start() {
        System.out.print("Start  ");
    }

    @Override
    boolean nextTry() {
        System.out.print("NextTry-" + state++ + "  ");
        return true;
    }

    @Override
    boolean isSolution() {
        System.out.print("IsSolution-" + (state == 3) + "  ");
        return (state == 3);
    }

    @Override
    void stop() {
        System.out.println("Stop");
    }
}

abstract class StrategySearch implements Strategy {
    @Override
    public void solve() {
        while (true) {
            preProcess();
            if (search()) {
                break;
            }
            postProcess();
        }
    }

    abstract void preProcess();
    abstract boolean search();
    abstract void postProcess();
}

class BAR extends StrategySearch {
    private int state = 0;

    @Override
    protected void preProcess()  {
        System.out.print("PreProcess  ");
    }

    @Override
    protected void postProcess() {
        System.out.print("PostProcess  ");
    }

    @Override
    protected boolean search() {
        System.out.print("Search-" + state++ + "  ");
        return state == 3;
    }
}
/**
 * @author arthur.xw
 */
public class Demo {
    private static void execute(Strategy strategy) {
        strategy.solve();
    }

    public static void main( String[] args ) {
        Strategy[] algorithms = {new FOO(), new BAR()};
        for (Strategy algorithm : algorithms) {
            execute(algorithm);
        }
    }
}
