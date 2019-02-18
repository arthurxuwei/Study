package Prototype;

import java.util.ArrayList;
import java.util.List;

interface Prototype {
    Prototype clone();

    String getName();

    void execute();
}

class PrototypeModule {
    private static List<Prototype> prototypes = new ArrayList<>();

    public static void addPrototype(Prototype prototype) {
        prototypes.add(prototype);
    }

    public static Prototype createPrototype(String name) {
        for (Prototype p : prototypes) {
            if (p.getName().equals(name)) {
                return p.clone();
            }
        }
        return null;
    }
}

class PrototypeAlpha implements Prototype {
    private String name = "AlphaVersion";

    @Override
    public Prototype clone() {
        return new PrototypeAlpha();
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void execute() {
        System.out.println(name + " does something");
    }
}

class PrototypeBeta implements Prototype {
    private String name = "BetaVersion";

    @Override
    public Prototype clone() {
        return new PrototypeBeta();
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void execute() {
        System.out.println(name + " does something");
    }
}

class ReleasePrototype implements Prototype {
    private String name = "ReleaseCandidate";

    @Override
    public Prototype clone() {
        return new ReleasePrototype();
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void execute() {
        System.out.println(name + " does real work");
    }
}

public class Demo {
    public static void initializePrototype() {
        PrototypeModule.addPrototype(new PrototypeAlpha());
        PrototypeModule.addPrototype(new PrototypeBeta());
        PrototypeModule.addPrototype(new ReleasePrototype());
    }

    public static void main(String[] args) {
        initializePrototype();
        List<Prototype> prototypes = new ArrayList<>();
        for (String protoName : args) {
            Prototype prototype = PrototypeModule.createPrototype(protoName);
            if (prototype != null) {
                prototypes.add(prototype);
            }
        }
        for (Prototype p : prototypes) {
            p.execute();
        }
    }
}

