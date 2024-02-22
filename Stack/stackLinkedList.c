#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *create(int A[], int n)
{
    if (n <= 0)
        return NULL;
    else
    {
        struct Node *top = (struct Node *)malloc(sizeof(struct Node));
        struct Node *last = (struct Node *)malloc(sizeof(struct Node));

        top->data = A[0];
        top->next = NULL;
        last = top;

        for (int i = 1; i < n; i++)
        {
            struct Node *t = (struct Node *)malloc(sizeof(struct Node));
            t->data = A[i];
            t->next = last;
            last = t;
            top = t;
        }

        return top;
    }
}

void push(struct Node **st, int x)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;
    if ((*st) == NULL)
    {
        if (t)
        {
            *st = t;
        }
    }
    else
    {
        if (t)
        {
            t->next = *st;
            *st = t;
        }
    }
}

int pop(struct Node **st)
{
    int x = -1;
    if ((*st) != NULL)
    {
        x = (*st)->data;
        if ((*st)->next != NULL)
        {
            struct Node *p = *st;
            *st = (*st)->next;
            free(p);
        }
        else
        {
            struct Node *p = *st;
            *st = NULL;
            free(p);
        }
    }
    return x;
}

int peek(struct Node *st, int pos)
{
    struct Node *p = st;
    int x = -1;
    int count = 0;

    while (p && count < pos)
    {
        p = p->next;
        count++;
    }

    if (count == pos)
        x = p->data;

    return x;
}

int stackTop(struct Node *st)
{
    int x = -1;
    if (st)
        x = st->data;
    return x;
}

int isEmpty(struct Node *st)
{
    return st == NULL ? 1 : 0;
}

int isFull(struct Node *st)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    int x = 0;
    if (t == NULL)
        x = 1;
    free(t);
    return x;
}

void display(struct Node *st)
{
    if (isEmpty(st) == 1)
        printf("Stack Empty");
    else
    {
        struct Node *p = st;
        while (p != NULL)
        {
            printf("%d\n", p->data);
            p = p->next;
        }
    }
}

int parenthesisMatching(char *expression)
{
    // Create stack
    struct Node *stack = NULL;

    // Iterate through expression, character by character
    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == '(')
        {
            printf("Pushing to stack\n");
            push(&stack, 1);
        }
        else if (expression[i] == ')')
        {
            if (isEmpty(stack) == 1)
                return 0;
            else
                printf("\nPopping from stack %d\n", pop(&stack));
        }
    }
    return isEmpty(stack) == 1 ? 1 : 0;
}

int bracketBalanced(char *expression)
{
    // Create stack
    struct Node *stack = NULL;

    // Iterate through each character
    for (int i = 0; expression[i] != '\0'; i++)
    {
        // Push opening tags/brackets to stack
        switch (expression[i])
        {
        case '{':
            push(&stack, 1);
            break;
        case '[':
            push(&stack, 2);
            break;
        case '(':
            push(&stack, 3);
            break;
        case '<':
            push(&stack, 4);
            break;
        case '}':
            if (isEmpty(stack) == 1 || pop(&stack) != 1)
                return 0;
            else
                break;
        case ']':
            if (isEmpty(stack) == 1 || pop(&stack) != 2)
                return 0;
            else
                break;
        case ')':
            if (isEmpty(stack) == 1 || pop(&stack) != 3)
                return 0;
            else
                break;
        case '>':
            if (isEmpty(stack) == 1 || pop(&stack) != 4)
                return 0;
            else
                break;
        default:
            break;
        }
    }

    return isEmpty(stack) == 1 ? 1 : 0;
}

int isOperator(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/')
        return 1;
    else
        return 0;
}

int precendence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else
        return 0;
}

char *infixToPostfix(char *expression)
{
    // Create empty stack
    struct Node *stack = NULL;
    // Create string of size equal to expression
    char *postfix = (char *)malloc(strlen(expression) + 1);
    // Create pointers for expression string and postfix string
    int i, j = 0;

    // Loop through each character in expression
    for (i = 0; expression[i] != '\0'; i++)
    {
        // Check if character is an operator
        if (isOperator(expression[i]) == 1)
        {
            // Get precedence of current operator
            int charPrecedence = precendence(expression[i]);

            // Check if stack is null
            if (stack == NULL)
            {
                // Push to stack operator
                push(&stack, expression[i]);
            }
            else
            {
                // Continue popping stack until we empty the stack or find a operator of lower precedence
                while (stack && charPrecedence <= precendence(stack->data))
                {
                    postfix[j++] = pop(&stack);
                }
                // Push operand to stack
                push(&stack, expression[i]);
            }
        }
        else
            postfix[j++] = expression[i]; // Push variable or number to postfix
    }
    while (stack)
    {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';

    return postfix;
}

int computeOperands(int y, int z, char x)
{
    if (x == '+')
        return y + z;
    else if (x == '-')
        return y - z;
    else if (x == '*')
        return y * z;
    else if (x == '/')
        return y / z;
    else
        return -1;
}

int evaluatePostfix(char *postfix)
{
    struct Node *stack = NULL;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (isOperator(postfix[i]) == 0)
        {
            push(&stack, postfix[i] - '0');
        }
        else
        {
            // Pop two operands
            int operand1, operand2;
            operand1 = pop(&stack);

            operand2 = pop(&stack);

            push(&stack, computeOperands(operand1, operand2, postfix[i]));
        }
    }
    return pop(&stack);
}

int main()
{
    int A[] = {3, 5, 1, 89, 124, 876};
    struct Node *stack = create(A, 6);
    display(stack);
    printf("Pushing 104 to stack\n\n");
    push(&stack, 104);
    display(stack);
    printf("Poping 104 from stack: ");
    printf("%d\n\n", pop(&stack));
    display(stack);
    printf("Peeking at position 7: ");
    printf("%d\n", peek(stack, 7));
    printf("Parenthesis match- - - - - -");
    if (parenthesisMatching("((((x+1) + 2 * 3 ^ 5)))") == 1)
        printf("Matching");
    else
        printf("Not matching!!");
    printf("\n\nBracket balance - - - -\n");
    if (bracketBalanced("<{Youtube}>[(Google)]>") == 1)
        printf("Balanced!");
    else
        printf("Not balanced!");

    printf("\n\nInfix to Postfix of: a+b*c-d/e is %s\n", infixToPostfix("a+b*c-d/e"));
    printf("\nEvaluate postfix expression 54+3*: %d\n", evaluatePostfix("54+3*"));
}