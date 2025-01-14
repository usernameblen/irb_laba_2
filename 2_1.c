#include <stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

char* function(int a, int r) {
	int mask = (1 << r) - 1;
	char *str = (char *)malloc(100);
	if (str == NULL) {
		return NULL;
	}
	int index = 0;

	//переводим число из одной СС в другую
	while (a != 0 && index < 99) {
		int ost = a & mask;
		if (ost < 10) {
			str[index++] = '0' | ost;
		}
		else {
			str[index++] = 'A' | (ost - 10);
		}
		a = a >> r;
	}
	str[index] = '\0';

	//освобождаем память которая не понадобилась
	//str = (char *)realloc(str, index + 1);
	str = (char*)realloc(str, index+1);
	if (str == NULL) {
		return NULL;
	}
	//переворачиваем строку
	int half_len = index >> 1;
	//for (int i = 0; i < half_len; i++) {
	for(int i = 0; i < half_len; i++){
		char temp = str[i];
		str[i] = str[index - i - 1];
		str[index - i - 1] = temp;
	}

	return  str;
}


int main() {
	int a, r;
	printf("Enter number a:");
	scanf("%d", &a);

	printf("\nEnter the value of r (the number a will move to SS 2^r): ");
	scanf("%d", &r);

	char* result = function(a, r);
	if (result == NULL) {
		printf("Erorr whit memory.\n");
	}
	else {
		printf("\nNumber %d in SS 2^%d = %s", a, r, result);
	}
	free(result);
	return 0;
}
