#include "student.h"

int main() {
	long long zh, mm;
	int flag = 0;
	while (1) {
		printf("���������Ա�˺�:");
		scanf("%lld", &zh);
		printf("���������Ա����:");
		scanf("%lld", &mm);
		if (zh == 123456789 && mm == 123456789) {
			flag = 1;
			break;
		} else {
			printf("�˺Ż����������,����������\n");
		}
	}
	if (flag) {
		Loop();
	}
	return 0;
}