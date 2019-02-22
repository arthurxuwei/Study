package customizedannotation;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;


public class Tester {
	
	@SeperatorLine
	public static void testYes() {
		System.out.println("TestYes");
	}
	
	@SeperatorLine(value=false)
	public static void testNo() {
		System.out.println("TestNo");
	}
	
	public static void main(String[] args) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		Class<Tester> c = Tester.class;
		Method m = c.getMethod("testYes");
		if (m.isAnnotationPresent(SeperatorLine.class)) {
			SeperatorLine sLine = m.getAnnotation(SeperatorLine.class);			
			if (sLine.value()) {
				System.out.println("-----"+ m.getName() +"-----");
			}

			m.invoke(null);
		}
		
		m = c.getMethod("testNo");
		if (m.isAnnotationPresent(SeperatorLine.class)) {
			SeperatorLine sLine = m.getAnnotation(SeperatorLine.class);			
			if (sLine.value()) {
				System.out.println("-----"+ m.getName() +"-----");
			}

			m.invoke(null);
		}
		
	}

}
