#include <stdio.h>
#include <malloc.h>

typedef struct Link {
	int date;
	struct Link *next;
} link;

link *Create() {
	link *head = (link *)malloc(sizeof(link));
	head->next = NULL;
	return head;
}

void inserttail(link *head, int x) {
	if (head == NULL)
		return ;
	link *p = (link *)malloc(sizeof(link));
	link *q = head;
	while (q->next != NULL) {
		q = q->next;
	}
	p->date = x;
	p->next = NULL;
	q->next = p;
}

void inserthead(link *head, int x) {
	link *p = (link *)malloc(sizeof(link));
	p->next = head->next;
	p->date = x;
	head->next = p;
}

void print(link *head) {
	link *p = head->next;
	while (p != NULL) {
		printf("%d ", p->date);
		p = p->next;
	}
}

void remove(link *head, int x) {
	link *p = head->next;
	if (!p)
		return ;
	link *q = head;
	while (p->date != x) {
		q = p;
		p = p->next;
	}
	q->next = p->next;
	free(p);
}

int main() {
	int n;
	link *head = Create();
	scanf("%d", &n);
	while (n--) {
		int x;
		scanf("%d", &x);
		inserthead(head, x);
	}
	print(head);
	int x;
	scanf("%d", &x);
	remove(head, x);
	print(head);
	return 0;
}