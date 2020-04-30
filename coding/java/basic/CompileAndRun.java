import javax.tools.*;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.lang.reflect.InvocationTargetException;
import java.net.URI;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Arrays;
import java.util.Collections;
import javax.tools.JavaCompiler.CompilationTask;

public class CompileAndRun {
    public static void main(String[] args) throws IOException {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        DiagnosticCollector<JavaFileObject> diagnostics = new DiagnosticCollector<JavaFileObject>();

        StringWriter writer =  new StringWriter();
        PrintWriter out = new PrintWriter(writer);
        out.println("package com.arthur;");
        out.println("public class HelloWorld {");
        out.println("  public static void main(String args[]) {");
        out.println("    System.out.println(\"This is in another java file\");");
        out.println("  }");
        out.println("}");
        out.close();

        JavaFileObject file = new JavaSourceFromString("HelloWorld", writer.toString());

        File distDir = new File("target/self");
        if (!distDir.exists()) {
            assert distDir.mkdirs();
        }

        Iterable<? extends JavaFileObject> compilationUnits = Collections.singletonList(file);
        CompilationTask task = compiler.getTask(null, null, diagnostics,
                Arrays.asList("-d", distDir.getAbsolutePath()), null, compilationUnits);

        boolean success = task.call();
        for (Diagnostic diagnostic : diagnostics.getDiagnostics()) {
            System.out.println(diagnostic.getCode());
            System.out.println(diagnostic.getKind());
            System.out.println(diagnostic.getPosition());
            System.out.println(diagnostic.getStartPosition());
            System.out.println(diagnostic.getEndPosition());
            System.out.println(diagnostic.getSource());
            System.out.println(diagnostic.getMessage(null));
        }
        System.out.println("Success: " + success);

        if(success) {
            try {
                URL[] urls = new URL[] {new File(distDir.getAbsolutePath()).toURI().toURL()};
                URLClassLoader urlcl = new URLClassLoader(urls);
                Class clazz = urlcl.loadClass("com.arthur.HelloWorld");
                clazz.getDeclaredMethod("main", new Class[]{String[].class}).invoke(null, new Object[]{null});
            } catch (ClassNotFoundException e) {
                System.err.println("Class not found: " + e);
            } catch (NoSuchMethodException e) {
                System.err.println("No such method: " + e);
            } catch (IllegalAccessException e) {
                System.err.println("Illegal access: " + e);
            } catch (InvocationTargetException e) {
                System.err.println("Invocation target: " + e);
            }
        }
    }
}

class JavaSourceFromString extends SimpleJavaFileObject {
    final String code;

    JavaSourceFromString(String name, String code) {
        super(URI.create(name.replaceAll("\\.", "/") + Kind.SOURCE.extension), Kind.SOURCE);
        this.code = code;
    }

    @Override
    public CharSequence getCharContent(boolean ignoreEncodingErrors) {
        return code;
    }
}
