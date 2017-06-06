package dataStructure.Tree;

import java.awt.*;
import java.net.BindException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Queue;
import java.util.Stack;
import java.util.concurrent.LinkedBlockingQueue;

public class BinaryTree<T> {

    BinaryTreeNode<T> root;

    public BinaryTree() {
        root = new BinaryTreeNode<T>();
    }

    public BinaryTree(BinaryTreeNode<T> t){
        root = t;
    }

    //build tree
    public void buildTree(ArrayList<Character> list){
        Iterator<Character> itor = list.listIterator();
        root = createTree(root, itor);
    }

    //create Tree
    private BinaryTreeNode<T> createTree(BinaryTreeNode<T> node, Iterator<Character> itor) {
        if (itor.hasNext()) {
            Character temp = itor.next();
            if (temp.equals('#')) return null;
            else {
                node = new BinaryTreeNode<T>((T)temp);
                node.setLeft(createTree(node.getLeft(), itor));
                node.setRight(createTree(node.getRight(), itor));
                return node;
            }
        } else {
            return null;
        }
    }

    //in-order (recursively)
    public void inOrderTraverse() {
        inOrderTraverse(root);
    }

    public void inOrderTraverse(BinaryTreeNode<T> node) {
        if (node != null) {
            inOrderTraverse(node.getLeft());
            System.out.println(node.getValue());
            inOrderTraverse(node.getRight());
        }
    }

    //pre-order (recursively)
    public void preOrderTraverse() {
        preOrderTraverse(root);
    }

    public void preOrderTraverse(BinaryTreeNode<T> node) {
        if (node != null) {
            System.out.println(node.getValue());
            preOrderTraverse(node.getLeft());
            preOrderTraverse(node.getRight());
        }
    }

    //post-order (recursively)
    public void postOrderTraverse() {
        postOrderTraverse(root);
    }

    public void postOrderTraverse(BinaryTreeNode<T> node) {
        if (node != null) {
            postOrderTraverse(node.getLeft());
            postOrderTraverse(node.getRight());
            System.out.println(node.getValue());
        }
    }

    //in-order (iteratively)
    public void inOrderTraverseN() {
        inOrderTraverseN(root);
    }

    public void inOrderTraverseN(BinaryTreeNode<T> node) {
        Stack<BinaryTreeNode<T>> stack = new Stack<BinaryTreeNode<T>>();
        while (node != null || !stack.isEmpty()) {
            while (node != null) {
                stack.push(node);
                node = node.getLeft();
            }
            node = stack.pop();
            System.out.println(node.getValue());
            node = node.getRight();
        }

    }

    //pre-order (iteratively)
    public void preOrderTraverseN() {
        preOrderTraverseN(root);
    }

    public void preOrderTraverseN(BinaryTreeNode<T> node) {
        Stack<BinaryTreeNode<T>> stack = new Stack<BinaryTreeNode<T>>();
        while (node != null || !stack.isEmpty()) {
            while (node != null) {
                System.out.println(node.getValue());
                stack.push(node);
                node = node.getLeft();
            }
            node = stack.pop();
            node = node.getRight();
        }

    }

    //post-order (iteratively)
    public void postOrderTraverseN() {
        postOrderTraverseN(root);
    }

    public void postOrderTraverseN(BinaryTreeNode<T> node) {
        Stack<BinaryTreeNode<T>> stack = new Stack<BinaryTreeNode<T>>();
        BinaryTreeNode<T> preNode = null;

        while (node != null || !stack.isEmpty()) {
            while (node != null) {
                stack.push(node);
                node = node.getLeft();
            }
            node = stack.peek();

            if (node.getRight() == null || node.getRight() == preNode) {
                System.out.println(node.getValue());
                node = stack.pop();
                preNode = node;
                node = null;
            } else {
                node = node.getRight();
            }
        }
    }

    //level-order
    public void levelTraverse() {
        levelTraverse(root);
    }

    public void levelTraverse(BinaryTreeNode<T> node) {
        Queue<BinaryTreeNode<T>> queue = new LinkedBlockingQueue<BinaryTreeNode<T>>();
        queue.add(node);
        while (!queue.isEmpty()) {
            BinaryTreeNode<T> temp = queue.poll();
            System.out.println(temp.getValue());
            if (temp.getLeft() != null) {
                queue.add(temp.getLeft());
            }
            if (temp.getRight() != null) {
                queue.add(temp.getRight());
            }
        }
    }

}
