#include "student.h"

int main() {
	long long zh, mm;
	int flag = 0;
	while (1) {
		printf("请输入管理员账号:");
		scanf("%lld", &zh);
		printf("请输入管理员密码:");
		scanf("%lld", &mm);
		if (zh == 123456789 && mm == 123456789) {
			flag = 1;
			break;
		} else {
			printf("账号或者密码错误,请重新输入\n");
		}
	}
	if (flag) {
		Loop();
	}
	return 0;
}