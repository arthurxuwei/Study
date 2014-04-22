package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Collections;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class TestCollections {
	public static void main (String[] argv) {
		Arrays.asList(0, 1, 2, 3, 4, 5);

		//array list
		List<String> arrayList = new ArrayList<String>();
		arrayList.add("fdas");
		arrayList.add("mnb");
		arrayList.add("vcx");
		arrayList.add("abdasf");
		Collections.sort(arrayList);
		System.out.println(arrayList);
		
		//linked list
		List<String> linkedList = new LinkedList<String>();
		linkedList.add("fdas");
		linkedList.add("mnb");
		linkedList.add("vcx");
		linkedList.add("abdasf");
		Collections.sort(linkedList);
		System.out.println(linkedList);
		
		//hash set
		Set<String> hashSet = new HashSet<String>();
		hashSet.add("fdas");
		hashSet.add("mnb");
		hashSet.add("vcx");
		hashSet.add("abdasf");
		System.out.println(hashSet);
		
		//tree set
		Set<String> treeSet = new TreeSet<String>();
		treeSet.add("fdas");
		treeSet.add("mnb");
		treeSet.add("vcx");
		treeSet.add("abdasf");
		System.out.println(treeSet);
		
		//hash map
		Map<String, String> hashMap = new HashMap<String, String>();
		hashMap.put("test1", "fdas");
		hashMap.put("test2", "fdas");
		hashMap.put("test3", "fdas");
		System.out.println(hashMap);
		
		//tree map
		Map<String, String> treeMap = new TreeMap<String, String>();
		treeMap.put("test1", "fdas");
		treeMap.put("test2", "fdas");
		treeMap.put("test3", "fdas");
		System.out.println(treeMap);
	}
}
