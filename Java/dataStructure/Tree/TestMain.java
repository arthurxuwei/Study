package dataStructure.Tree;

import java.util.ArrayList;
import java.util.Arrays;

public class TestMain {
    public static void main(String[] argv) {

        BinaryTree<Character> bt = new BinaryTree<Character>();
        ArrayList<Character> array = new ArrayList<Character>(Arrays.asList('a', 'b', '#', '#', 'c', 'd', '#', '#', '#'));

        bt.buildTree(array);

        System.out.println("in order recursively");
        bt.inOrderTraverse();
        System.out.println("pre order recursively");
        bt.preOrderTraverse();
        System.out.println("post order recursively");
        bt.postOrderTraverse();

        System.out.println("in order iteratively");
        bt.inOrderTraverseN();
        System.out.println("pre order iteratively");
        bt.preOrderTraverseN();
        System.out.println("post order iteratively");
        bt.postOrderTraverseN();

        System.out.println("level order");
        bt.levelTraverse();
    }
}
