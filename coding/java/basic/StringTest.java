package test;

import java.util.ArrayList;

public class StringTest {
	public static void main(String[] argc) {
		String a = "abcd";
		StringBuffer b = new StringBuffer("1213435667");
		System.out.println(b);
		b.reverse();
		System.out.println(b);
		StringTest t = new StringTest();
		b = t.reverse(b);
		System.out.println(b);
		b = t.removeDuplicates(b);
		System.out.println(b);
	}
	
	private StringBuffer reverse(StringBuffer str) {
		for (int i = 0; i < str.length() / 2; ++i) {
			char c = str.charAt(i);
			str.setCharAt(i, str.charAt(str.length() - i - 1));
			str.setCharAt(str.length() - i - 1, c);	
		}
		return str;
	}
	
	private StringBuffer removeDuplicates(StringBuffer str) {
		boolean[] hits = new boolean[256];//ASCII Charset
		for (int i = 0; i < 256; ++i) {
			hits[i] = false;
		}
		int tail = 1;
		hits[str.charAt(0)] = true;
		for (int i = 0; i < str.length(); ++i) {
			if(!hits[str.charAt(i)]) {
				str.setCharAt(tail, str.charAt(i));
				++tail;
				hits[str.charAt(i)] = true;
			}
		}
		str.delete(tail, str.length());
		return str;
	}
	
	private ArrayList<Integer> subString(StringBuffer str) {
		ArrayList<Integer> array = new ArrayList<Integer>();
		
		return array;
	}
}
