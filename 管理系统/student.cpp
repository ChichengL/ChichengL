#include "student.h"
Node *head;
FILE *fp;
char filename[127];
GL *head1;

void xuanze(int &x) {
	while (1) {
		Create();
		menu1();
		int s;
		cin >> s;
		int flag = 0;
		switch (s) {
			case 1:
				denglu(flag);
				break;
			case 2:
				zhuce();
				break;
			case 3:
				exit(0);
				break;
			default:
				break;
		}
		if (flag) {
			x = 1;
			break;
		}
	}
}

void Create() {
	head1 = (GL *)malloc(sizeof(GL));
	head1->next = NULL;
}

void denglu(int &x) {
	duru();
	char a[1000], b[1000];
	printf("�������˺ź�����\n");
	cin >> a >> b;
	if (head1->next == NULL) {
		printf("�����˺�\n");
		return ;
	}
	GL *p = head1->next;
	while (p != NULL) {
		if (!strcmp(p->zh, a)) {
			if (!strcmp(p->mm, b)) {
				x = 1;
				return;
			}
			printf("�������\n");
			break;
		} else
			p = p->next;
	}
	if (p == NULL)
		printf("�˺Ŵ���\n");
}

void zhuce() {
	duru();
	string anhao;
	printf("�����밵��\n");
	cin >> anhao;
	if (anhao == "lec") {
		printf("�����봴�����˺ź�����\n");
		char a[1000], b[1000];
		cin >> a >> b;
		GL *p = head1->next;
		while (p != NULL && !strcpy(p->zh, a)) {
			p = p->next;
		}
		if (p) {
			printf("���˺��Ѵ���\n");
		} else {
			GL *q = (GL *)malloc(sizeof(GL));
			strcpy(q->zh, a);
			strcpy(q->mm, b);
			q->next = NULL;
			if (head1->next == NULL) {
				head1->next = q;
			} else {
				q->next = head1->next;
				head1->next = q;
			}
		}

	} else
		printf("���Ŵ���\n");
	GL *p = head1->next;
	if ((fp = fopen("zh", "a+")) == NULL) {
		printf("\n�ļ�����ʧ�ܣ����ܻ���ļ������\n");
		return;
	}
	while (p != NULL) {
		fprintf(fp, "%s %s\n", p->zh, p->mm);
		p = p->next;
	}
	fclose(fp);
}

void menu1() {
	printf("    *             ��ѡ�����б�              *\n");
	printf("    *******************************************\n");
	printf("    *             1����½����ϵͳ             *\n");
	printf("    *             2��ע�����Ա�˺�           *\n");
	printf("    *             3���˳�                     *\n");

}

void duru() {
	if ((fp = fopen("zh", "a+")) == NULL) {
		printf("\n�ļ���ʧ�ܣ����ܻ���ļ������\n");
		return ;
	}
	if (head1 == NULL) {
		CreatNode();//�����ʼû�ڵ���ô�ʹ���
	}
	while (1) {
		GL *p = (GL *)malloc(sizeof(GL));
		p->next = NULL;
		if (fscanf(fp, "%s %s\n", p->zh, p->mm) == EOF) {
			//��ȡ���ı�ĩβ
			break;
		}
		//ͷ��
		if (head1->next == NULL) {
			head1->next = p;
		} else {
			p->next = head1->next;
			head1->next = p;
		}
	}
}

void Loop() {
	CreatNode();
	while (1) {
		system("cls");// ������
		menu();
		printf("���������֣�");
		char ch = getchar();
		switch (ch) {
			case '1':
				Input();
				break;
			case '2':
				Print();
				break;
			case '3':
				SaveData();
				break;
			case '4':
				LoadData();
				break;
			case '5':
				Count();
				break;
			case '6':
				Search();
				break;
			case '7':
				xiugai();
				break;
			case '8':
				Delete();
				break;
			case '9':
				Sort();
				break;
			case '0':
				//�˳�ϵͳ
				exit(0);
				break;
			default:
				break;
		}
	}
}

void menu() {
	printf("\n\n");
	printf("    *******************************************\n");
	printf("    *          ��ӭʹ�óɼ�����ϵͳ           *\n");
	printf("    *******************************************\n");
	printf("    *             ��ѡ�����б�              *\n");
	printf("    *******************************************\n");
	printf("    *             1��¼��ѧ����Ϣ             *\n");
	printf("    *             2����ӡѧ����Ϣ             *\n");
	printf("    *             3������ѧ����Ϣ             *\n");
	printf("    *             4����ȡѧ����Ϣ             *\n");
	printf("    *             5��ͳ��ѧ������             *\n");
	printf("    *             6������ѧ����Ϣ             *\n");
	printf("    *             7���޸�ѧ����Ϣ             *\n");
	printf("    *             8��ɾ��ѧ����Ϣ             *\n");
	printf("    *             9������ѧ����Ϣ             *\n");
	printf("    *             0���˳�ϵͳ                 *\n");
	printf("    *******************************************\n");
}

void CreatNode() {
	head = (Node *)malloc(sizeof(Node));
	head->next = NULL;
}

void Input() {
	Node *p = (Node *)malloc(sizeof(Node));
	p->next = NULL;
	printf("    *******************************************\n");
	printf("    *             ѧ����Ϣ¼�����            *\n");
	printf("    *******************************************\n");
	printf("\n");
	printf("������ѧ��������");
	scanf("%s", p->stu.name);
	printf("������ѧ��ѧ�ţ�(����������)");
	scanf("%lld", &p->stu.xuehao);
	printf("������ѧ���Ա�");
	scanf("%s", p->stu.sex);
	printf("������ѧ�����䣺(����������)");
	scanf("%d", &p->stu.age);
	printf("������ѧ���ɼ���(����������)");
	scanf("%d", &p->stu.grade);
	if (head->next == NULL) {
		head->next = p;
	} else {
		p->next = head->next;
		head->next = p;
	}
	printf("    *            ѧ����Ϣ¼��ɹ���           *\n");
	system("pause");
}

void Print() {
	printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
	printf("---------------------------------------------------------------------------------\n");
	Node *p = head->next;
	while (p != NULL) {
		printf("|\t%lld\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.xuehao, p->stu.name, p->stu.sex, p->stu.age, p->stu.grade);
		printf("---------------------------------------------------------------------------------\n");
		p = p->next;
	}
	if (head->next == NULL) {
		printf("|\t\t\t\tû��ѧ����Ϣ\t\t\t\t\t|\n");
		printf("---------------------------------------------------------------------------------\n");
	}
	printf("\n\n");
	system("pause");
}

void SaveData() {
	printf("\n\n");
	printf("������Ҫ������ļ�����");
	scanf("%s", filename);
	Node *p = head->next;
	if ((fp = fopen(filename, "a+")) == NULL) {
		printf("\n�ļ�����ʧ�ܣ����ܻ���ļ������\n");
		return;
	}
	while (p != NULL) {
		fprintf(fp, "%s %lld %s %d %d\n", p->stu.name, p->stu.xuehao, p->stu.sex, p->stu.age, p->stu.grade);
		p = p->next;
	}
	fclose(fp);
	printf("    *            ѧ����Ϣ����ɹ���           *\n");
	system("pause");
}

void LoadData() {
	printf("\n\n");
	printf("�����뱣����ѧ����Ϣ���ļ�����");
	scanf("%s", filename);
	if ((fp = fopen(filename, "a+")) == NULL) {
		printf("\n�ļ���ʧ�ܣ����ܻ���ļ������\n");
		return ;
	}
	if (head == NULL) {
		CreatNode();//�����ʼû�ڵ���ô�ʹ���
	}
	while (1) {
		Node *p = (Node *)malloc(sizeof(Node));
		p->next = NULL;
		if (fscanf(fp, "%s %lld %s %d %d\n", p->stu.name, &p->stu.xuehao, p->stu.sex, &p->stu.age, &p->stu.grade) == EOF) {
			//��ȡ���ı�ĩβ
			break;
		}
		//ͷ��
		if (head->next == NULL) {
			p->next = head->next;
			head->next = p;
		} else {
			p->next = head->next;
			head->next = p;
		}
	}
}

void Count() {
	Node *p = head->next;
	int cnt = 0;
	while (p != NULL) {
		cnt ++;
		p = p->next;
	}
	printf("ѧ������Ϊ%d\n", cnt);
	system("pause");
}

void Search() {
	while (1) {
		printf("��ѡ���ѯ��ʽ����1����ѧ��   |  ��2�������� | ��-1���˳�\n��ѡ��");
		int k;
		scanf("%d", &k);
		Node *p = head->next;
		if (k == 1) {
			printf("������ѧ��");
			int xuehao;
			scanf("%d", &xuehao);
			int flag = 0;
			while (p != NULL) {
				if (p->stu.xuehao == xuehao) {
					printf("---------------------------------------------------------------------------------\n");
					printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
					printf("---------------------------------------------------------------------------------\n");
					printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.xuehao, p->stu.name, p->stu.sex, p->stu.age, p->stu.grade);
					printf("---------------------------------------------------------------------------------\n");
					flag = 1;
				}
				p = p->next;
			}
			if (!flag) {
				printf("\t\t\t\tδ��ѯ��������Ϣ��\t\t\t\t\t");
				system("pause");
				return;
			}
		} else if (k == 2) {
			char n[20];
			printf("����������:");
			scanf("%s", n);
			while (p && strcmp(n, p->stu.name) != 0) {
				p = p->next;
			}
			if (p) {
				printf("---------------------------------------------------------------------------------\n");
				printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.xuehao, p->stu.name, p->stu.sex, p->stu.age, p->stu.grade);
				printf("---------------------------------------------------------------------------------\n");
			} else {
				printf("\t\t\t\tδ��ѯ��������Ϣ��\t\t\t\t\t");
				return;
			}
		} else if (k == -1) {
			return;
		} else {
			printf("�������������ѡ��:");
		}
	}
}

void xiugai() {
	printf("��������Ҫ�޸���Ա��ѧ��:");
	long long num;
	scanf("%lld", &num);
	Node *p = head->next;
	while (p && p->stu.xuehao != num) {
		p = p->next;
	}
	if (p) {
		printf("��������ĺ��ѧ��ѧ�ţ�");
		scanf("%lld", &p->stu.xuehao);
		printf("��������ĺ��ѧ��������");
		scanf("%s", p->stu.name);
		printf("��������ĺ��ѧ���Ա�");
		scanf("%s", p->stu.sex);
		printf("��������ĺ��ѧ�����䣺");
		scanf("%d", &p->stu.age);
		printf("��������ĺ��ѧ���ɼ���");
		scanf("%d", &p->stu.grade);
	} else {
		printf("���޴���\n");
	}
}

void Delete() {
	Node *p = head->next, *q = head;
	printf("��������Ҫɾ��ѧ����ѧ��");
	long long n;
	scanf("%lld", &n);
	while (p && p->stu.xuehao != n) {
		q = p;
		p = p->next;
	}
	if (p) {
		q->next = p->next;
		free(p);
		printf("ɾ���ɹ�");
	} else {
		printf("���޴�����ɾ��ʧ��\n");
		return ;
	}
}

void Sort() {
	Node *o = head->next;
	int cnt = 0;
	while (o) {
		cnt++;
		o = o->next;
	}
	Node *p, *q;
	for (int i = 0; i < cnt - 1; i ++) {
		p = head->next;
		q = p->next;
		for (int j = 0; j < cnt - j ++, p = p->next, q = q->next) {
			if (p->stu.xuehao > q- 1 - i;>stu.xuehao) {
				Student t = p->stu;
				p->stu = q->stu;
				q->stu = t;
			}
		}
	}
}
