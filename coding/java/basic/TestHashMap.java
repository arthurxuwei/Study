package test;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.TreeMap;

import data.ExampleOne;

public class TestHashMap {

	public static void main(String argc[]) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException
	{
///hashmap
		HashMap<String, String> hm = new HashMap<String, String>();
		hm.put("a", "b");
		if (hm.containsKey("a")) {
			System.out.println(hm.get("a"));
		} else {
			System.out.println("Hash map do not contain Key");
		}
		ExampleOne one = new ExampleOne(1, "arthur");
		HashMap<ExampleOne, String> hm2 = new HashMap<ExampleOne, String>();
		hm2.put(one, "One");
		if (hm2.containsKey(one)) {
			System.out.println(hm2.get(one));
		} else {
			System.out.println("Hash map do not contain Key");
		}
		ExampleOne two = new ExampleOne(1, "arthur");
		hm2.put(two, "Two");
		if (hm2.containsKey(two)) {
			System.out.println(hm2.get(two));
		} else {
			System.out.println("Hash map do not contain Key");
		}

//hashmap return reference
		
		HashMap<String, ExampleOne> l = new HashMap<>();
		ExampleOne e3 = new ExampleOne(3, "3");
		l.put("first", e3);
		ExampleOne temp = l.get("first");
		temp.set(3, "3x");
		System.out.println(l.get("first"));
/// HashMap function		
		HashMap<String, Method> hf = new HashMap<String, Method>();
		
		TestHashMap test = new TestHashMap();
		Method[] declaredMethods = TestHashMap.class.getDeclaredMethods();
		for (Method method : declaredMethods) {
			System.out.println("Method name: " + method.getName());
			System.out.println("Parameters Type: ");
			Class[] parameterTypes = method.getParameterTypes();
			for (int i = 0; i < parameterTypes.length; ++i) {
				System.out.println("Parameter:"+i+" Type: " +parameterTypes[i]);
			}
			System.out.println("Return Type："+ method.getReturnType()); 
			
//			if (method.getName() != "main"){
//				try {
//					System.out.println("Run Result："+ method.invoke(test));
//				} catch (IllegalAccessException e) {
//					// TODO Auto-generated catch block
//					e.printStackTrace();
//				} catch (IllegalArgumentException e) {
//					// TODO Auto-generated catch block
//					e.printStackTrace();
//				} catch (InvocationTargetException e) {
//					// TODO Auto-generated catch block
//					e.printStackTrace();
//				} 
//			}
			hf.put(method.getName(), method);
		}
		
		hf.get("methodA").invoke(test);
		hf.get("methodB").invoke(test);	
		
		
		//Linked Hashmap
		System.out.println("-----linkedHashMap-----");
		HashMap<String, String> linkedHashMap = new LinkedHashMap<String, String>();
		linkedHashMap.put("a", "abc");
		linkedHashMap.put("c", "abc");
		linkedHashMap.put("b", "abc");
		
		System.out.println(linkedHashMap);
		
		//Treemap
		System.out.println("-----treeHashMap-----");
		TreeMap<String, String> treeMap = new TreeMap<String, String>();
		treeMap.put("a", "abc");
		treeMap.put("c", "abc");
		treeMap.put("b", "abc");
		
		System.out.println(treeMap);
		
	}
	
	public int methodA() {
		System.out.println("method a");
		return 0;
	}
	
	public static int methodB() {
		System.out.println("method b");
		return 0;
	}
	
}
