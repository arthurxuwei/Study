package bridge;


import java.util.Random;

interface StackImpl {
    void push(int i);
    int pop();
    int top();
    boolean isEmpty();
    boolean isFull();
}

class StackArray implements StackImpl {
    private int[] items;
    private int total = -1;

    public StackArray() {
        this.items = new int[12];
    }


    public StackArray(int cells) {
        this.items = new int[cells];
    }

    @Override
    public void push(int i) {
        if (!isFull()) {
            items[++total] = i;
        }
    }

    @Override
    public int pop() {
        if (isEmpty()) {
            return -1;
        }
        return items[total--];
    }

    @Override
    public int top() {
        if (isEmpty()) {
            return -1;
        }
        return items[total];
    }

    @Override
    public boolean isEmpty() {
        return total == -1;
    }

    @Override
    public boolean isFull() {
        return total == items.length - 1;
    }
}

class StackList implements StackImpl {
    class Node {
        int value;
        Node prev, next;

        Node(int value) {
            this.value = value;
        }
    }

    private Node last;

    @Override
    public void push(int i) {
        if (last == null) {
            last = new Node(i);
        } else {
            last.next = new Node(i);
            last.next.prev = last;
            last = last.next;
        }
    }

    @Override
    public int pop() {
        if (isEmpty()) {
            return -1;
        }
        int ret = last.value;
        last = last.prev;
        return ret;
    }

    @Override
    public int top() {
        if (isEmpty()) {
            return -1;
        }
        return last.value;
    }

    @Override
    public boolean isEmpty() {
        return last == null;
    }

    @Override
    public boolean isFull() {
        return false;
    }
}

class Stack {
    private StackImpl impl;

    public Stack(String s) {
        if ("array".equals(s)) {
            impl = new StackArray();
        } else if ("list".equals(s)) {
            impl = new StackList();
        } else {
            System.out.println("Stack: unknown parameter");
        }
    }

    public Stack() {
        this("array");
    }

    public void push(int in) {
        impl.push(in);
    }

    public int pop() {
        return impl.pop();
    }

    public int top() {
        return impl.top();
    }

    public boolean isEmpty() {
        return impl.isEmpty();
    }

    public boolean isFull() {
        return impl.isFull();
    }
}

class StackHanoi extends Stack {
    private int totalRejected = 0;

    public StackHanoi() {
        super("array");
    }

    public StackHanoi(String s) {
        super(s);
    }

    public int reportRejected() {
        return totalRejected;
    }

    @Override
    public void push(int in) {
        if (!isEmpty() && in > top()) {
            totalRejected++;
        }
        else {
            super.push(in);
        }
    }
}

class StackFIFO extends Stack {

    public StackFIFO() {
        super("array");
    }

    public StackFIFO(String s) {
        super(s);
    }

    @Override
    public int pop() {
        while (!isEmpty()) {
            push(super.pop());
        }
        int ret = super.pop();
        while (!isEmpty()) {
            push(super.pop());
        }
        return ret;
    }
}

public class Demo {
    public static void main(String[] args) {
        Stack[] stacks = {new Stack("array"), new Stack("list"), new StackFIFO(), new StackHanoi()};
        for (int i = 1, num; i < 15; i++) {
            for (int j = 0; j < 3; j++) {
                stacks[j].push(i);
            }
        }
        Random rn = new Random();
        for (int i = 1, num; i < 15; i++) {
            stacks[3].push(rn.nextInt(20));
        }
        for (int i = 0, num; i < stacks.length; i++) {
            while (!stacks[i].isEmpty()) {
                System.out.print(stacks[i].pop() + " ");
            }
            System.out.println();
        }
        System.out.println("total rejected is " + ((StackHanoi)stacks[3]).reportRejected());
    }
}
