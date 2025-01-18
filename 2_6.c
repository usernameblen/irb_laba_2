#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

double power(double value, int degree) {
	if (value == 0 && degree != 0) {
		return 0;
	}
	else if (degree == 0) {
		return 1;
	}
	else if (degree % 2 == 0) {
		return power(value * value, degree / 2);
	}
	else  if (degree % 2 == 1) {
		return value * power(value * value, (degree - 1) / 2);
	}
}

int value_of_polynomial(double* result, double x, int n_degree, ...) {
	if (n_degree < 0) {
		return 1; //несуществующая степень многочлена
	}

	va_list(coef_list);
	va_start(coef_list, n_degree);
	if (n_degree == 0) {
		*result = va_arg(coef_list, double); 
		return 0;
	}

	//array with coefficients
	double* coefficients = (double*)malloc((n_degree + 1) * sizeof(double));
	if (coefficients == NULL) {
		return 2; //memory error
	}


	*result = 0.0;
	for (int i = 0; i < (n_degree + 1); i++) {
		coefficients[i] = va_arg(coef_list, double);
	 	*result += power(x, n_degree - i) * coefficients[i];
	}

	
	va_end(coef_list);
	free(coefficients);
	return 0; //good
}

int main() {
	double result;
	switch (value_of_polynomial(&result,1.5, 3, 2.5, -3.7, 1.9, -4.2)) {
	case 0:
		printf("Result: %.2f", result);
		break;
	case 1:
		printf("Non-existent degree of a polynomial.");//несуществующая степень многочлена
		break;
	case 2:
		printf("Error with memory.");
		break;
	}

	return 0;
}
