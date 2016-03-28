package test;

public class LoadAndInit {


    /**
     * @param args
     */
    public static void main(String[] args) {
        new B(5);

        Singleton mysingleton = Singleton.GetInstence();
        System.out.println(mysingleton.a);
        System.out.println(mysingleton.b);
    }
}


class A {
    public A(){
        System.out.println("A  say before-----");
        say();
        System.out.println("A  say after-----");
    }
    public void say(){
        System.out.println("A Say:");
    }
}


class B extends A{
    private int a=1;
    public B(int b){
        a=b;
        System.out.println("B  a: "+a);
    }
    public void say(){
        System.out.println("B Say a: "+a);
    }
}


class C extends B{
    private int a = 2;
    public C(int a) {
        super(a);
        this.a = a;
    }

    public void say() {
        System.out.println("C Say a: "+a);
    }

}


class Singleton {

    public static Singleton singleton = new Singleton();
    public static int a;
    public static int b = 0;

    private Singleton() {
        super();
        a++;
        b++;
    }

    public static Singleton GetInstence() {
        return singleton;
    }

}