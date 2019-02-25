package dataStructure.Tree;


public class BinaryTreeNode<T> {
    private T value;
    private BinaryTreeNode<T> left;
    private BinaryTreeNode<T> right;

    public BinaryTreeNode() {
        left = null;
        right = null;
    }

    public BinaryTreeNode(BinaryTreeNode<T> l, BinaryTreeNode<T> r, T v) {
        this.value = v;
        this.left = l;
        this.right = r;
    }

    public BinaryTreeNode(T t) {
        this(null, null, t);
    }

    public void setValue(T t) {
        value = t;
    }

    public T getValue() {
        return value;
    }

    public void setLeft(BinaryTreeNode<T> left) {
        this.left = left;
    }

    public BinaryTreeNode<T> getLeft() {
        return this.left;
    }

    public void setRight(BinaryTreeNode<T> right) {
        this.right = right;
    }

    public BinaryTreeNode<T> getRight() {
        return this.right;
    }
}
