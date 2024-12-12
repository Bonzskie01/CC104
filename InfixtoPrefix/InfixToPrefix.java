import java.util.*;

class InfixToPrefix {
    // Function to check if the character is an operand
    static boolean isalpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    // Function to check if the character is a digit
    static boolean isdigit(char c) {
        return c >= '0' && c <= '9';
    }

    // Function to check if the character is an operator
    static boolean isOperator(char c) {
        return (!isalpha(c) && !isdigit(c));
    }

    // Function to get priority of operators
    static int getPriority(char C) {
        if (C == '-' || C == '+')
            return 1;
        else if (C == '*' || C == '/')
            return 2;
        else if (C == '^')
            return 3;

        return 0;
    }

    // Reverse the letters of the word
    static String reverse(char str[], int start, int end) {
        char temp;
        while (start < end) {
            temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }
        return String.valueOf(str);
    }

    // Function to convert infix to postfix expression
    static String infixToPostfix(char[] infix1) {
        String infix = '(' + String.valueOf(infix1) + ')';
        int l = infix.length();
        Stack<Character> char_stack = new Stack<>();
        StringBuilder output = new StringBuilder();

        for (int i = 0; i < l; i++) {
            if (isalpha(infix.charAt(i)) || isdigit(infix.charAt(i)))
                output.append(infix.charAt(i));
            else if (infix.charAt(i) == '(')
                char_stack.add('(');
            else if (infix.charAt(i) == ')') {
                while (char_stack.peek() != '(') {
                    output.append(char_stack.peek());
                    char_stack.pop();
                }
                char_stack.pop();
            } else {
                if (isOperator(char_stack.peek())) {
                    while ((getPriority(infix.charAt(i)) < getPriority(char_stack.peek()))
                        || (getPriority(infix.charAt(i)) <= getPriority(char_stack.peek())
                        && infix.charAt(i) == '^')) {
                        output.append(char_stack.peek());
                        char_stack.pop();
                    }
                    char_stack.add(infix.charAt(i));
                }
            }
        }
        while (!char_stack.isEmpty()) {
            output.append(char_stack.pop());
        }
        return output.toString();
    }

    static String infixToPrefix(char[] infix) {
        int l = infix.length;

        String infix1 = reverse(infix, 0, l - 1);
        infix = infix1.toCharArray();

        for (int i = 0; i < l; i++) {
            if (infix[i] == '(') {
                infix[i] = ')';
                i++;
            } else if (infix[i] == ')') {
                infix[i] = '(';
                i++;
            }
        }

        String prefix = infixToPostfix(infix);
        prefix = reverse(prefix.toCharArray(), 0, l - 1);

        return prefix;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an infix expression:");
        String s = scanner.nextLine();
        scanner.close();

        System.out.println("Prefix Expression: " + infixToPrefix(s.toCharArray()));
    }
}
