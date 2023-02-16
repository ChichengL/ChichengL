#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct Student {
	int xuehao;
	char name[20];
	char sex[4];
	int age;
	int grade;
} Student;

typedef struct Node {
	Student stu;
	struct Node *next;
} Node;
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