package visitor;



interface Element {
    void accept(Visitor v);
}

class FOO implements Element {

    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }

    public String getFOO() {
        return "FOO";
    }
}

class BAR implements Element {
    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }

    public String getBAR() {
        return "BAR";
    }
}

class BAZ implements Element {

    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }

    public String getBAZ() {
        return "BAZ";
    }
}

interface Visitor {
    void visit(FOO foo);

    void visit(BAR bar);

    void visit(BAZ baz);
}

class UpVisitor implements Visitor {
    @Override
    public void visit(FOO foo) {
        System.out.println("do Up on " + foo.getFOO());
    }

    @Override
    public void visit(BAR bar) {
        System.out.println("do Up on " + bar.getBAR());
    }

    @Override
    public void visit(BAZ baz) {
        System.out.println( "do Up on " + baz.getBAZ() );
    }
}

class DownVisitor implements Visitor {
    @Override
    public void visit(FOO foo) {
        System.out.println("do Down on " + foo.getFOO());
    }

    @Override
    public void visit(BAR bar) {
        System.out.println("do Down on " + bar.getBAR());
    }

    @Override
    public void visit(BAZ baz ) {
        System.out.println("do Down on " + baz.getBAZ());
    }
}


/**
 * @author arthur.xw
 */
public class Demo {
    public static void main( String[] args ) {
        Element[] list = {new FOO(), new BAR(), new BAZ()};
        UpVisitor up = new UpVisitor();
        DownVisitor down = new DownVisitor();
        for (Element element : list) {
            element.accept(up);
        }
        for (Element element : list) {
            element.accept(down);
        }
    }
}
