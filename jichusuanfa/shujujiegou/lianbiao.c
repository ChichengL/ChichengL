#include <stdio.h>

typedef struct Link {
	int val;
	struct Link *next;
} Link;
Link *headnode;

Link Ceate() {
	headnode = (Link *)malloc(sizeof(Link));
	headnode->next = NULL;
}

void addinsert(int x) { //尾插
	Link *p = (Link *)malloc(sizeof(Link));
	Link *q = headnode->next;
	while (q != NULL)
		q = q->next;
	p = q;
	p->val = x;
	p->next = NULL;
}

void headinsert(int x) {
	Link *p = (Link *)malloc(sizeof(Link));
	p->next = headnode->next;
	p = headnode->next;
	p->val = x;
}

void remove(int x) {
	Link *p = headnode->next;
	Link *q = p;
	while (p != NULL && p->val != x) {
		q = p;
		p = p->next;
	}
	if (p == NULL) {
		printf("删除失败，没有该数");
	}
	if (q != NULL) {
		q->next = p->next;
	}
	free(p);
}

void print() {
	Link *p = headnode->next;
	for (; p != NULL; p = p->next) {
		prinf("%d ", p->val);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	Creat();
	while (n--) {
		int x;
		scanf("%d", &x);
		addinsert(x);
	}
	print();
	return 0;
}