package abstractfactory;

abstract class CPU {}

class EmberCPU extends CPU {}

class EnginolaCPU extends CPU {}

class DefaultCPU extends CPU {}

abstract class MMU {}

class EmberMMU extends MMU {}

class EnginolaMMU extends MMU {}

class DefaultMMU extends MMU {}

enum Architecture {
    ENGINOLA, EMBER, DEFAULT
}

abstract class AbstractFactory {
    private static final EmberToolkit EMBER_TOOLKIT = new EmberToolkit();
    private static final EnginolaToolkit ENGINOLA_TOOLKIT = new EnginolaToolkit();
    private static final DefaultToolkit DEFAULT_TOOLKIT = new DefaultToolkit();

    // Returns a concrete factory object that is an instance of the
    // concrete factory class appropriate for the given architecture
    static AbstractFactory getFactory(Architecture architecture) {
        AbstractFactory abstractFactory;
        switch (architecture) {
            case ENGINOLA:
                abstractFactory = ENGINOLA_TOOLKIT;
                break;
            case EMBER:
                abstractFactory = EMBER_TOOLKIT;
                break;
            default:
                abstractFactory = DEFAULT_TOOLKIT;
        }
        return abstractFactory;
    }

    public abstract CPU createCPU();

    public abstract MMU createMMU();
}

class EmberToolkit extends AbstractFactory {
    @Override
    public CPU createCPU() {
        return new EmberCPU();
    }

    @Override
    public MMU createMMU() {
        return new EmberMMU();
    }
}

class EnginolaToolkit extends AbstractFactory {
    @Override
    public CPU createCPU() {
        return new EnginolaCPU();
    }

    @Override
    public MMU createMMU() {
        return new EnginolaMMU();
    }
}

class DefaultToolkit extends AbstractFactory {
    @Override
    public CPU createCPU() {
        return new DefaultCPU();
    }

    @Override
    public MMU createMMU() {
        return new DefaultMMU();
    }
}

public class Demo{
    public static void main(String[] args) {
        AbstractFactory abstractFactory1 = AbstractFactory.getFactory(Architecture.EMBER);
        assert abstractFactory1.createCPU() instanceof EmberCPU;
        assert abstractFactory1.createMMU() instanceof EmberMMU;
        AbstractFactory abstractFactory2 = AbstractFactory.getFactory(Architecture.ENGINOLA);
        assert abstractFactory2.createCPU() instanceof EnginolaCPU;
        assert abstractFactory2.createMMU() instanceof EnginolaMMU;
    }
}