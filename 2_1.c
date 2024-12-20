#include <stdio.h>

char* function(int a, int r) {
	int mask = (1 << r) - 1;
	static char str[64];
	int index = 0;

	//переводим число из одной СС в другую
	while (a != 0 && index < 63) {
		int ost = a & mask;
		if (ost < 10) {
			str[index++] = '0' + ost;
		}
		else {
			str[index++] = 'A' + (ost - 10);
		}
		a = a >> r;
	}
	str[index] = '\0';

	//переворачиваем строку
	for (int i = 0; i < index / 2; i++) {
		char temp = str[i];
		str[i] = str[index - i - 1];
		str[index - i - 1] = temp;
	}

	return  str;
}


int main() {
	int a, r;
	printf("Enter number a:");
	scanf_s("%d", &a);

	printf("\nEnter the value of r (the number a will move to SS 2^r): ");
	scanf_s("%d", &r);

	char* result = function(a, r);
	printf("\nNumber %d in SS 2^%d = %s", a, r, result);

	return 0;
}
