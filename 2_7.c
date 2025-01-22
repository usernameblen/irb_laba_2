#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

unsigned int unsigned_pow(unsigned int value, unsigned int degree) {
    unsigned int result = 1;
    while (degree > 0) {
        if (degree % 2 == 1) {
            result *= value;
        }
        value *= value;
        degree /= 2;
    }
    return result;
}


int change_system_to_ten(const char* value, int sys) {
    int value_in_ten = 0;
    int power = 1;
    int len = strlen(value);

    for (int i = len - 1; i >= 0; i--) {
        if (value[i] >= '0' && value[i] <= '9') {
            value_in_ten += (value[i] - '0') * power;
        }
        else if (value[i] >= 'A' && value[i] <= 'Z') {
            value_in_ten += (value[i] - 'A' + 10) * power;
        }
        else {
            //printf("Error value\n");
            return -1; //error value
        }
        power *= sys;
    }
    return value_in_ten;
}

void reverse_string(char str[]) {
	int n = strlen(str);
	for (int i = 0; i < n / 2; i++) {
		char temp = str[i];
		str[i] = str[n - i - 1];
		str[n - i - 1] = temp;
	}
}


char* change_to_base_sys(int value, int base) {
    char* res = NULL;
    res = (char*)malloc(33);
    if (!res) {
        return NULL;
    }
    int index = 0;

    //the numbers < 0
    if (value < 0 && base == 10) {
        res[index++] = '-';
        value = -value;
    }

    do {
        res[index++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[value % base];
        value /= base;
    } while (value > 0);

    res[index] = '\0';

    
    reverse_string(res);

    return res;
}


void the_kramer_number(int count, unsigned int base, ...) {
    va_list args;
    va_start(args, base);

    if (base < 2 || base > 32) {
        printf("Error: invalid base\n");
        va_end(args);
        return;
    }

    for (int i = 0; i < count; i++) {
        char* str_num = va_arg(args, char*);
        int num = change_system_to_ten(str_num, base);
        if (num == -1) {
            printf("Error: invalid number %s in base %u\n", str_num, base);
            continue;
        }
 

        if (num < 0) {
            printf("Error: invalid number %s in base %u\n", str_num, base);
            continue; 
        }

        int num_squared = unsigned_pow(num, 2);
        char* num_squared_str = change_to_base_sys(num_squared, base);

        if (!num_squared_str) {
            printf("Error memory.");
            break;
        }

        int len = strlen(num_squared_str);
        int mid = len / 2;

     
        char* left = NULL;
        left = (char*)malloc(mid + 1);
        if (!left) {
            printf("Error memory.");
            free(num_squared_str);
            break;
        }

        char* right = NULL;
        right = (char*)malloc(len - mid + 1);
        if (!right) {
            printf("Error memory.");
            free(left);
            free(num_squared_str);
            break;
        }

        strncpy(left, num_squared_str, mid);
        left[mid] = '\0';

        strcpy(right, num_squared_str + mid);
        right[len - mid] = '\0';

        int left_sum = change_system_to_ten(left, base);
        int right_sum = change_system_to_ten(right, base);

        if (num == left_sum + right_sum) {
            printf("%s is a Kaprekar number in base %u\n", str_num, base);
        }

        //освобождение выделенной памяти
        free(left);
        free(right);
        free(num_squared_str);
    }

    va_end(args);
}

int main() {
    the_kramer_number(15, 16, "23", "2", "1", "6", "A", "F", "33", "55", "5B", "78", "88", "AB", "CD", "FF", "15F");
    return 0;
}