package decorator;

interface Widget {
    void draw();
}

class TextField implements Widget {
    private int width, height;

    public TextField(int width, int height) {
        this.width = width;
        this.height = height;
    }

    @Override
    public void draw() {
        System.out.println("TextField: " + width + ", " + height);
    }
}

abstract class Decorator implements Widget {
    private Widget widget;

    public Decorator(Widget widget) {
        this.widget = widget;
    }

    @Override
    public void draw() {
        widget.draw();
    }
}

class BorderDecorator extends Decorator {
    public BorderDecorator(Widget widget) {
        super(widget);
    }

    @Override
    public void draw() {
        super.draw();
        System.out.println("\tBorderDecorator");
    }
}

class ScrollDecorator extends Decorator {
    public ScrollDecorator(Widget widget) {
        super(widget);
    }

    @Override
    public void draw() {
        super.draw();
        System.out.println("\tScrollDecorator");
    }
}

public class Demo {
    public static void main(String[] args) {
        new BorderDecorator(new ScrollDecorator(new TextField(80, 24))).draw();
    }
}
