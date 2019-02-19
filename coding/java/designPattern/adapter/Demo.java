package adapter;

interface Shape {
    void draw(int x, int y, int z, int j);
}

class Line {
    public void draw(int x1, int y1, int x2, int y2) {
        System.out.println(String.format("Line from point A(%s, %s), to point B(%s, %s)", x1, y1, x2, y2));
    }
}

class Rectangle {
    public void draw(int x, int y, int width, int height) {
        System.out.println(String.format("Rectangle with coordinate left-down point (%s, %s), width: %s, height: %s", x, y, width, height));
    }
}

class LineAdapter implements Shape {
    private Line line;

    public LineAdapter(Line line) {
        this.line = line;
    }

    @Override
    public void draw(int x1, int y1, int x2, int y2) {
        line.draw(x1, y1, x2, y2);
    }

}

class RectangleAdapter implements Shape {
    private Rectangle rectangle;

    public RectangleAdapter(Rectangle rectangle) {
        this.rectangle = rectangle;
    }

    @Override
    public void draw(int x1, int y1, int x2, int y2) {
        int x = Math.min(x1, x2);
        int y = Math.min(y1, y2);
        int width = Math.abs(x2 - x1);
        int height = Math.abs(y2 - y1);
        rectangle.draw(x, y, width, height);
    }
}

public class Demo {
    public static void main(String[] args) {
        Shape[] shapes = {new RectangleAdapter(new Rectangle()), new LineAdapter(new Line())};
        int x1 = 10, y1 = 20;
        int x2 = 30, y2 = 60;
        for (Shape shape : shapes) {
            shape.draw(x1, y1, x2, y2);
        }
    }
}
