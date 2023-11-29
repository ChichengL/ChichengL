#include <iostream>
#include <algorithm>
using namespace std;

typedef struct StackNum {
    int x;
    struct StackNum *next;
} NumStack;

typedef struct {
    NumStack *top;
    int size;
} LinkNum;

typedef struct StackChar {
    char x;
    struct StackChar *next;
} CharStack;

typedef struct {
    CharStack *top;
    int size;
} LinkChar;

LinkNum num;
LinkChar op;

void InitNum(LinkNum *s) {
//    s->top = (NumStack *)malloc(sizeof(NumStack));
    s->size = 0;
    s->top = NULL;
}

void InitChar(LinkChar *s) {
//    s->top = (CharStack *)malloc(sizeof(CharStack));
    s->size = 0;
    s->top = NULL;
}

void pushNum(LinkNum *s, int e) {
    NumStack *p = (NumStack *)malloc(sizeof(NumStack));
    p->x = e;
    p->next = s->top;
    s->top = p;
    s->size++;
    cout << e << endl;
}

void pushChar(LinkChar *s, char e) {
    CharStack *p = (CharStack *)malloc(sizeof(CharStack));
    p->x = e;
    p->next = s->top;
    s->top = p;
    s->size++;
}

void popNum(LinkNum *s, int &e) {
    NumStack *p = s->top;
    e = p->x;
    s->top = s->top->next;
    free(p);
    s->size--;
//    cout << e << endl;
}

void popChar(LinkChar *s, char &e) {
    CharStack *p = s->top;
    e = p->x;
    s->top = s->top->next;
    free(p);
    s->size--;
}

int compare(char x) {
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else if (x == '^')
        return 3;
    return 0;
}

void eval() {
    int a, b, k;
    popNum(&num, a);
    popNum(&num, b);
    char ch;
    popChar(&op, ch);
    if (ch == '+')
        k = b + a;
    else if (ch == '-')
        k = b - a;
    else if (ch == '*')
        k = b * a;
    else if (ch == '/')
        k = b / a;
    else {
        k = 1;
        while (a--)
            k = k * b;
    }
    pushNum(&num, k);
}

int main() {
    InitNum(&num);
    InitChar(&op);
    string expression;
    cin >> expression;
    cout << "操作数栈栈顶元素变化：" << endl;
    for (int i = 0; i < (int)expression.size(); i ++) {
        if (isdigit(expression[i])) {
            int j = i, k = 0;
            while (j < (int)expression.size() && isdigit(expression[j])) {
                k = k * 10 + expression[j] - '0';
                j++;
            }
            pushNum(&num, k);
            i = j - 1;
        } else if (expression[i] == '(') {
            pushChar(&op, expression[i]);
        } else if (expression[i] == ')') {
            while (op.size > 0 && op.top->x != '(')
                eval();
            char ch;
            popChar(&op, ch);
        } else {
            while (op.size > 0 && compare(op.top->x) >= compare(expression[i]))
                eval();
            pushChar(&op, expression[i]);
        }
    }
    while (op.size > 0)
        eval();
    printf("表达式值：%d", num.top->x);
}

