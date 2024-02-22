#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int size;
    int top;
    int *s;
};

struct Stack *create(int A[], int n)
{
    struct Stack *st = (struct Stack *)malloc(sizeof(struct Stack));
    st->size = n;
    st->top = -1;
    st->s = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        st->s[i] = A[i];
        st->top++;
    }

    return st;
}

void push(struct Stack *st, int x)
{
    if (st->top == st->size - 1)
        printf("Stack overflow");
    else
    {
        st->top++;
        st->s[st->top] = x;
    }
}

int pop(struct Stack *st)
{
    int x = -1;
    if (st->top == -1)
        printf("Stack underflow");
    else
    {
        x = st->s[st->top];
        st->top--;
    }
    return x;
}

int peek(struct Stack st, int pos)
{
    int x = -1;
    if (st.top - pos + 1 < 0)
        printf("Invalid position");
    else
        x = st.s[st.top - pos + 1];
    return x;
}

int stackTop(struct Stack st)
{
    int x = -1;
    if (st.top == -1)
        printf("No elements");
    else
        x = st.s[st.top];
    return x;
}

void display(struct Stack st)
{
    for (int i = st.top; i >= 0; i--)
    {
        printf("%d\n", st.s[i]);
    }
}

int main()
{
    int A[] = {3, 5, 6, 7, 8, 9};

    struct Stack *stack = create(A, 6);

    display(*stack);
    printf("\nTop is %d, Element is %d", stack->top, stack->s[stack->top]);

    return 0;
}