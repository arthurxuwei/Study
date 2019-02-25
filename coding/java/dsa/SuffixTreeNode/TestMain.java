package dataStructure.SuffixTreeNode;

import java.util.ArrayList;

public class TestMain {
	public static void main(String[] args) {
		String testString = "mississippi";
		String[] stringList = {"is", "sip", "hi", "sis"};
		SuffixTree tree = new SuffixTree(testString);
		for (String s : stringList) {
			ArrayList<Integer> list = tree.getIndexes(s);
			if (list != null) {
				System.out.println(s + ": " + list.toString());
			}
		}
	}
}
