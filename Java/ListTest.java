package test;

import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;

public class ListTest {
	public static void main(String[] argc) {
		ListTest t = new ListTest();
		LinkedList<Integer> l = new LinkedList<Integer>(Arrays.asList(1, 2, 3, 4, 5));
		t.nToLast(l, 2);
	}
	
	private void nToLast(LinkedList<Integer> list, int n) {
		Iterator<Integer> p1 = list.listIterator(n-1);
		
		while (p1.hasNext()) {
			System.out.println(p1.next());
		}
	}
}
