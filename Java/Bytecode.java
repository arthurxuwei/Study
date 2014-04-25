package test;

public class Bytecode {
	public static void main (String[] args) {
		if (args.length < 2) {
			System.out.println("Must enter any two args.");
			return;
		}
		
		System.out.println(args[0] + args[1]);
	}

}

/*
Compiled from "Bytecode.java"
public class test.Bytecode {
  public test.Bytecode();
    Code:
       0: aload_0
       1: invokespecial #1                  // Method java/lang/Object."<init>":()V
       4: return

  public static void main(java.lang.String[]);
    Code:
       0: aload_0
       1: arraylength
       2: iconst_2
       3: if_icmpge     15
       6: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
       9: ldc           #3                  // String Must enter any two args.
      11: invokevirtual #4                  // Method java/io/PrintStream.println:(Ljava/lang/String;)V
      14: return
      15: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
      18: new           #5                  // class java/lang/StringBuilder
      21: dup
      22: invokespecial #6                  // Method java/lang/StringBuilder."<init>":()V
      25: aload_0
      26: iconst_0
      27: aaload
      28: invokevirtual #7                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      31: aload_0
      32: iconst_1
      33: aaload
      34: invokevirtual #7                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      37: invokevirtual #8                  // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
      40: invokevirtual #4                  // Method java/io/PrintStream.println:(Ljava/lang/String;)V
      43: return
}
*/