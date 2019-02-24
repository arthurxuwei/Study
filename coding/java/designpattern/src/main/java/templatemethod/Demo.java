package templatemethod;

abstract class Generalization {
    void findSolution() {
        stepOne();
        stepTwo();
        stepThr();
        stepFor();
    }

    private void stepOne() {
        System.out.println("Generalization.stepOne");
    }

    abstract void stepTwo();

    abstract void stepThr();

    void stepFor() {
        System.out.println( "Generalization.stepFor" );
    }
}

abstract class Specialization extends Generalization {
    @Override
    protected void stepThr() {
        step3_1();
        step3_2();
        step3_3();
    }

    private void step3_1() {
        System.out.println("Specialization.step3_1");
    }

    abstract protected void step3_2();

    private void step3_3() {
        System.out.println("Specialization.step3_3");
    }
}

class Realization extends Specialization {

    @Override
    protected void stepTwo() {
        System.out.println("Realization.stepTwo");
    }

    @Override
    protected void step3_2() {
        System.out.println( "Realization.step3_2");
    }

    @Override
    protected void stepFor() {
        System.out.println("Realization.stepFor");
        super.stepFor();
    }
}

/**
 * @author arthur.xw
 */
public class Demo {
    public static void main(String[] args) {
        Generalization algorithm = new Realization();
        algorithm.findSolution();
    }
}
