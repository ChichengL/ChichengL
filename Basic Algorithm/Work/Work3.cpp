#include <iostream>

using namespace std;

typedef struct TreeNode {
	int val;
	struct TreeNode *lchild, *rchild;
} Tree;

void init(Tree *T) {
	T = (Tree *)malloc(sizeof(Tree));
	T = NULL;
}

Tree *CreateTree() {
	int ch;
	scanf("%d", &ch);

	if (ch == -1) {
		return NULL;
	}
	Tree *T = (Tree *)malloc(sizeof(Tree));
	T->val = ch;
	T->lchild = CreateTree();
	T->rchild = CreateTree();
	return T;
}

int Empty(Tree *T) {

	if (T == NULL) {
		return 1;
	}
	return 0;
}


int Deep(Tree *T) {

	if (T == NULL) {
		return 0;
	}
	int i, j;
	if (T->lchild) {
		i = Deep(T->lchild);
	} else
		i = 0;

	if (T->rchild) {
		j = Deep(T->rchild);
	} else
		j = 0;

	return i > j ? i + 1 : j + 1;
}

void PreOrderTraverse(Tree *T) {
	if (T == NULL)
		return;
	cout << T->val << ' ';
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

void InOrderTraverse(Tree *T) {
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	cout << T->val << ' ';
	InOrderTraverse(T->rchild);
}

void PostOrderTraverse(Tree *T) {
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	cout << T->val << ' ';
}

int main() {
	Tree *T;
//	Tree *T = (Tree *)malloc(sizeof(Tree));
//	init(T);
	T = NULL;
	T = CreateTree();
	if (!T)
		printf("NULL");
//	return 0;

	cout << "树的深度为：" << Deep(T) << '\n';

	cout << "树的前序遍历为：";
	PreOrderTraverse(T);
	puts("");
	printf("该树是否为空(1空,0非空) %d\n", Empty(T));
	cout << "树的中序遍历为";
	InOrderTraverse(T);
	puts("");
	cout << "树的后序遍历为";
	PostOrderTraverse(T);
}