#include "s.h"
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
	printf("请输入账号和密码(不支持空格)\n");
	cin >> a >> b;
	if (head1->next == NULL) {
		printf("暂无账号\n");
		return ;
	}
	GL *p = head1->next;
	while (p != NULL) {
		if (!strcmp(p->zh, a)) {
			if (!strcmp(p->mm, b)) {
				x = 1;
				return;
			}
			printf("密码错误\n");
			break;
		} else
			p = p->next;
	}
	if (p == NULL)
		printf("账号错误\n");
}

void zhuce() {
	duru();
	string anhao;
	printf("请输入暗号\n");
	cin >> anhao;
	if (anhao == "lec") {
		printf("请输入创建的账号和密码(不支持空格)\n");
		char a[1000], b[1000];
		cin >> a >> b;
		GL *p = head1->next;
		while (p != NULL && !strcpy(p->zh, a)) {
			p = p->next;
		}
		if (p) {
			printf("该账号已存在\n");
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
		printf("暗号错误\n");
	GL *p = head1->next;
	if ((fp = fopen("zh", "a+")) == NULL) {
		printf("\n文件保存失败！不能获得文件句柄！\n");
		return;
	}
	while (p != NULL) {
		fprintf(fp, "%s %s\n", p->zh, p->mm);
		p = p->next;
	}
	fclose(fp);
}

void menu1() {
	printf("    *             请选择功能列表              *\n");
	printf("    *******************************************\n");
	printf("    *             1：登陆管理系统             *\n");
	printf("    *             2：注册管理员账号           *\n");
	printf("    *             3：退出                     *\n");

}

void duru() {
	if ((fp = fopen("zh", "a+")) == NULL) {
		printf("\n文件打开失败！不能获得文件句柄！\n");
		return ;
	}
	if (head1 == NULL) {
		CreatNode();//如果开始没节点那么就创建
	}
	while (1) {
		GL *p = (GL *)malloc(sizeof(GL));
		p->next = NULL;
		if (fscanf(fp, "%s %s\n", p->zh, p->mm) == EOF) {
			//读取至文本末尾
			break;
		}
		//头插
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
		system("cls");// 清除输出
		menu();
		printf("请输入数字：");
		int ch;
		cin >> ch;
		switch (ch) {
			case 1:
				Input();
				break;
			case 2:
				Print();
				break;
			case 3:
				SaveData();
				break;
			case 4:
				LoadData();
				break;
			case 5:
				Count();
				break;
			case 6:
				Search();
				break;
			case 7:
				xiugai();
				break;
			case 8:
				Delete();
				break;
			case 9:
				Sort();
				break;
			case 0:
				//退出系统
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
	printf("    *          欢迎使用成绩管理系统           *\n");
	printf("    *******************************************\n");
	printf("    *             请选择功能列表              *\n");
	printf("    *******************************************\n");
	printf("    *             1：录入学生信息             *\n");
	printf("    *             2：打印学生信息             *\n");
	printf("    *             3：保存学生信息             *\n");
	printf("    *             4：读取学生信息             *\n");
	printf("    *             5：统计学生人数             *\n");
	printf("    *             6：查找学生信息             *\n");
	printf("    *             7：修改学生信息             *\n");
	printf("    *             8：删除学生信息             *\n");
	printf("    *             9：排序学生信息(学号,字典序)*\n");
	printf("    *             0：退出系统                 *\n");
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
	printf("    *             学生信息录入界面            *\n");
	printf("    *******************************************\n");
	printf("\n");
	printf("请输入学生学号：(请输入数字)");
	scanf("%s", p->stu.xuehao);
	Node* q = head->next;
	while(q&&strcmp(q->stu.xuehao,p->stu.xuehao)!=0)
	{
		q=q->next;
	}
	
	
	if(q==NULL)
	{
		printf("请输入学生姓名：");
	scanf("%s", p->stu.name);
	printf("请输入学生性别：");
	scanf("%s", p->stu.sex);
	printf("请输入学生年龄：(请输入数字)");
	scanf("%s", p->stu.age);
	printf("请输入学生成绩(总成绩)：(请输入数字)");
	scanf("%s", p->stu.grade);
	if (head->next == NULL) {
		head->next = p;
	} else {
		p->next = head->next;
		head->next = p;
	}
	printf("    *            学生信息录入成功！           *\n");
	system("pause");
	}
	else{
		printf("该学生已经存在，请重新尝试\n");
		system("pause");
	}
}

void Print() {
	printf("\t学号\t\t姓名\t\t性别\t\t年龄\t\t成绩\t\n");
	printf("---------------------------------------------------------------------------------\n");
	Node *p = head->next;
	while (p != NULL) {
		printf("|\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\n", p->stu.xuehao, p->stu.name, p->stu.sex, p->stu.age, p->stu.grade);
		printf("---------------------------------------------------------------------------------\n");
		p = p->next;
	}
	if (head->next == NULL) {
		printf("|\t\t\t\t没有学生信息\t\t\t\t\t|\n");
		printf("---------------------------------------------------------------------------------\n");
	}
	printf("\n\n");
	system("pause");
}

void SaveData() {
	printf("\n\n");
	printf("请输入要保存的文件名：");
	scanf("%s", filename);
	Node *p = head->next;
	if ((fp = fopen(filename, "a+")) == NULL) {
		printf("\n文件保存失败！不能获得文件句柄！\n");
		return;
	}
	while (p != NULL) {
		fprintf(fp, "%s %s %s %s %s\n", p->stu.name, p->stu.xuehao, p->stu.sex, p->stu.age, p->stu.grade);
		p = p->next;
	}
	fclose(fp);
	printf("    *            学生信息保存成功！           *\n");
	system("pause");
}

void LoadData() {
	printf("\n\n");
	printf("请输入保存有学生信息的文件名：");
	scanf("%s", filename);
	if ((fp = fopen(filename, "a+")) == NULL) {
		printf("\n文件打开失败！不能获得文件句柄！\n");
		return ;
	}
	if (head == NULL) {
		CreatNode();//如果开始没节点那么就创建
	}
	while (1) {
		Node *p = (Node *)malloc(sizeof(Node));
		p->next = NULL;
		if (fscanf(fp, "%s %s %s %s %s\n", p->stu.name, &p->stu.xuehao, p->stu.sex, &p->stu.age, &p->stu.grade) == EOF) {
			//读取至文本末尾
			break;
		}
		//头插
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
	printf("学生人数为%d\n", cnt);
	system("pause");
}

void Search() {
	while (1) {
		printf("请选择查询方式：【1】按学号   |  【2】按姓名 | 【-1】退出\n请选择：");
		int k;
		scanf("%d", &k);
		Node *p = head->next;
		if (k == 1) {
			printf("请输入学号");
			char xuehao[1000];
			scanf("%s", xuehao);
			int flag = 0;
			while (p != NULL) {
				if (strcmp(p->stu.xuehao, xuehao)) {
					printf("---------------------------------------------------------------------------------\n");
					printf("|\t学号\t\t姓名\t\t性别\t\t年龄\t\t成绩\t\n");
					printf("---------------------------------------------------------------------------------\n");
					printf("|\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\n", p->stu.xuehao, p->stu.name, p->stu.sex, p->stu.age, p->stu.grade);
					printf("---------------------------------------------------------------------------------\n");
					flag = 1;
				}
				p = p->next;
			}
			if (!flag) {
				printf("\t\t\t\t未查询到该生信息！\t\t\t\t\t");
				system("pause");
				return;
			}
		} else if (k == 2) {
			char n[200];
			printf("请输入姓名:");
			scanf("%s", n);
			while (p && strcmp(n, p->stu.name) != 0) {
				p = p->next;
			}
			if (p) {
				printf("---------------------------------------------------------------------------------\n");
				printf("|\t学号\t\t姓名\t\t性别\t\t年龄\t\t成绩\t\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("|\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\n", p->stu.xuehao, p->stu.name, p->stu.sex, p->stu.age, p->stu.grade);
				printf("---------------------------------------------------------------------------------\n");
			} else {
				printf("\t\t\t\t未查询到该生信息！\t\t\t\t\t");
				return;
			}
		} else if (k == -1) {
			return;
		} else {
			printf("输入错误，请重新选择:");
		}
	}
}

void xiugai() {
	printf("请输入需要修改人员的学号:");
	char num[1000];
	scanf("%s", num);
	Node *p = head->next;
	while (p && strcmp(p->stu.xuehao, num)) {
		p = p->next;
	}
	if (p) {
		printf("请输入更改后的学生学号：");
		scanf("%s", p->stu.xuehao);
		printf("请输入更改后的学生姓名：");
		scanf("%s", p->stu.name);
		printf("请输入更改后的学生性别：");
		scanf("%s", p->stu.sex);
		printf("请输入更改后的学生年龄：");
		scanf("%s", p->stu.age);
		printf("请输入更改后的学生成绩：");
		scanf("%s", p->stu.grade);
	} else {
		printf("查无此生\n");
	}
}

void Delete() {
	Node *p = head->next, *q = head;
	printf("请输入需要删除学生的学号");
	char n[1000];
	scanf("%s", n);
	while (p && strcmp(p->stu.xuehao, n)) {
		q = p;
		p = p->next;
	}
	if (p) {
		q->next = p->next;
		free(p);
		printf("删除成功");
	} else {
		printf("查无此生，删除失败\n");
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
		for (int j = 0; j < cnt - i - 1;j++,p = p->next, q = q->next) {
			if (strcmp(p->stu.xuehao, q->stu.xuehao) == 1) {
				Student t = p->stu;
				p->stu = q->stu;
				q->stu = t;
			}
		}
	}
}
