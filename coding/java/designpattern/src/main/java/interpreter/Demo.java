package interpreter;


import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

/**
 * This is an adaptation of a design that appeared in a Pascal data structures book.
 * The intent was to use stacks to convert normal "infix" syntax into "postfix" notation with operator precedence already handled.
 */

interface Operand {
    double evaluate(Map<String, Integer> context);
    void traverse(int level);
}

class Expression implements Operand {
    private char operation;
    public Operand left, right;

    public Expression(char operation) {
        this.operation = operation;
    }

    @Override
    public double evaluate(Map<String, Integer> context) {
        double result = 0;
        double a = left.evaluate(context);
        double b = right.evaluate(context);
        if (operation == '+') {
            result = a + b;
        }
        if (operation == '-') {
            result = a - b;
        }
        if (operation == '*') {
            result = a * b;
        }
        if (operation == '/') {
            result = a / b;
        }
        return result;
    }

    @Override
    public void traverse(int level) {
        left.traverse(level + 1);
        System.out.print("" + level + operation + level + " ");
        right.traverse(level + 1);
    }
}

class Variable implements Operand {
    private String name;

    public Variable(String name) {
        this.name = name;
    }

    @Override
    public double evaluate(Map<String, Integer> context) {
        return context.get(name);
    }

    @Override
    public void traverse(int level) {
        System.out.print(name + " ");
    }
}

class Number implements Operand {
    private double value;

    public Number(double value) {
        this.value = value;
    }

    @Override
    public double evaluate(Map<String, Integer> context) {
        return value;
    }

    @Override
    public void traverse(int level) {
        System.out.print(value + " ");
    }
}

/**
 * @author arthur.xw
 */
public class Demo {
    public static boolean precedence(char a, char b) {
        String high = "*/", low = "+-";
        if (a == '(') {
            return false;
        }
        if (a == ')' && b == '(') {
            System.out.println(")-(");
            return false;
        }
        if (b == '(') {
            return false;
        }
        if (b == ')') {
            return true;
        }
        if (high.indexOf(a) >  - 1 && low.indexOf(b) >  - 1) {
            return true;
        }
        if (high.indexOf(a) >  - 1 && high.indexOf(b) >  - 1) {
            return true;
        }
        //noinspection RedundantIfStatement
        if (low.indexOf(a) >  - 1 && low.indexOf(b) >  - 1) {
            return true;
        }
        return false;
    }

    public static String convertToPostfix(String expr) {
        Stack<Character> operationsStack = new Stack<>();
        StringBuilder out = new StringBuilder();
        String operations = "+-*/()";
        char topSymbol = '+';
        boolean empty;
        String[] tokens = expr.split(" ");
        for (String token : tokens) {
            if (operations.indexOf(token.charAt(0)) == -1) {
                out.append(token);
                out.append(' ');
            } else {
                while (!(empty = operationsStack.isEmpty()) && precedence(topSymbol =
                        operationsStack.pop(), token.charAt(0))) {
                    out.append(topSymbol);
                    out.append(' ');
                }
                if (!empty) {
                    operationsStack.push(topSymbol);
                }
                if (empty || token.charAt(0) != ')') {
                    operationsStack.push(token.charAt(0));
                } else {
                    topSymbol = operationsStack.pop();
                }
            }
        }
        while (!operationsStack.isEmpty()) {
            out.append(operationsStack.pop());
            out.append(' ');
        }
        return out.toString();
    }

    public static Operand buildSyntaxTree(String tree) {
        Stack <Operand> stack = new Stack<>();
        String operations = "+-*/";
        String[] tokens = tree.split(" ");
        for (String token : tokens) {
            if (operations.indexOf(token.charAt(0)) == -1) {
                Operand term;
                try {
                    term = new Number(Double.parseDouble(token));
                } catch (NumberFormatException ex) {
                    term = new Variable(token);
                }
                stack.push(term);

                // If token is an operator
            } else {
                Expression expr = new Expression(token.charAt(0));
                expr.right = stack.pop();
                expr.left = stack.pop();
                stack.push(expr);
            }
        }
        return stack.pop();
    }

    public static void main(String[] args) {
        System.out.println("celsius * 9 / 5 + thirty");
        String postfix = convertToPostfix("celsius * 9 / 5 + thirty");
        System.out.println(postfix);
        Operand expr = buildSyntaxTree(postfix);
        expr.traverse(1);
        System.out.println();
        HashMap< String, Integer > map = new HashMap<>();
        map.put("thirty", 30);
        for (int i = 0; i <= 100; i += 10) {
            map.put("celsius", i);
            System.out.println("C is " + i + ",  F is " + expr.evaluate(map));
        }
    }
}
