class DecodedImage {
    private String image;

    public DecodedImage(String image) {
        this.image = image;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return "DecodedImage{" +
                "image='" + image + '\'' +
                '}';
    }
}

interface ImageReader {
    DecodedImage getDecodeImage();
}

class GifReader implements ImageReader {
    private String image;

    public GifReader(String image) {
        this.image = image;
    }

    @java.lang.Override
    public DecodedImage getDecodeImage() {
        return new DecodedImage(image + " gif decoded");
    }
}

class JpegReader implements ImageReader {
    private String image;

    public JpegReader(String image) {
        this.image = image;
    }

    @java.lang.Override
    public DecodedImage getDecodeImage() {
        return new DecodedImage(image + " jpeg decoded");
    }
}

public class Demo {
    public static void main(String[] args) {
        String content = args[0];
        String format = content.substring(content.indexOf('.') + 1, content.length());
        ImageReader reader = null;
        if (format.equals("gif")) {
            reader = new GifReader(content);
        }
        if (format.equals("jpeg")) {
            reader = new JpegReader(content);
        }
        System.out.println(reader.getDecodeImage());
    }
}