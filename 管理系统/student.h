#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct Student {
	long long xuehao;
	char name[2000];
	char sex[400];
	int age;
	int grade;
} Student;

typedef struct guanli {
	char zh[1000];
	char mm[1000];
	struct guanli *next;
} GL;

typedef struct Node {
	Student stu;
	struct Node *next;
} Node;
void denglu(int &x);
void duru();
void xuanze(int &x);
void menu1();
void Create();
void zhuce();
void Loop();
void menu();
void CreatNode();
void Input();
void Print();
void SaveData();
void LoadData();
void Count();
void Search();
void xiugai();
void Delete();
void Sort();