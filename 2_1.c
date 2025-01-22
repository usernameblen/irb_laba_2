#include <stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

int plus_some(int number, int carry) { //carry - слагаемое
	while (carry != 0) {
		// сложение без переноса
		int sum = number ^ carry;
		// если первое выражение = 0 => перенос не нужен
		carry = (number & carry) << 1;
		// обновляем number 
		number = sum;
	}
	return number;
}

int minus_some(int number, int b) {
	return plus_some(number, plus_some(~b, 1));
}

int function(int a, int r, char *str, size_t size) {
	if (r < 1 || r > 5) {
		return 1;
	}

	int mask = minus_some((1 << r), 1);
	int index = 0;

	//переводим число из одной СС в другую
	while (a != 0 && index < minus_some(size, 1)) {
		int ost = a & mask;
		if (ost < 10) {
			str[index++] = '0' | ost;
		}
		else {
			str[index++] = 'A' | minus_some(ost, 10);
		}
		a = a >> r;
	}
	str[index] = '\0';

	//переворачиваем строку
	int half_len = index >> 1;

	for (int i = 0; i < half_len; i = plus_some(i, 1)) {
		int q = minus_some(minus_some(index, i), 1);
		char temp = str[i];
		str[i] = str[q];
		str[q] = temp;
	}

	return 0;
}


int main() {
	int a, r;
	printf("Enter number a:");

	if (scanf("%d", &a) != 1) { //функция scanf возвращает кол-во успешно считанных элементов
		printf("\ninvalid number a\n");
		return 1;
	}

	printf("\nEnter the value of r (the number a will move to SS 2^r): ");

	if (scanf("%d", &r) != 1) {
		printf("\ninvalid number r\n");
		return 1;
	}

	char result[40];

	switch (function(a, r, &result, 40)) {
	case 0:
		printf("\nNumber %d in SS 2^%d = %s", a, r, result);
		break;
	case 1:
		printf("Error! r can be from 1 to 5.\n");
		break;
	}
	return 0;
}
