#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

void free_resources(char flag, ...) {
	char* ptr;
	FILE* fptr;
	va_list args;
	va_start(args, flag);
	while (1) {
		if (flag == 'f') {
			fptr = va_arg(args, FILE*);
			fclose(fptr);
		}
		else if (flag == 'm') {
			ptr = va_arg(args, char*);
			free(ptr);
		}
		else if (flag == '\0') {
			break;
		}else{
			printf("error! flag is incorrect.\n");
			break;
		}
		flag = va_arg(args, char);
	}
	va_end(args);
}

int main() {
	//some file
	FILE* file = fopen("nothing.txt", "r"); // == 'f'
	//some dinamic array
	char* array = NULL;
	array = (char*)malloc(15 * sizeof(char)); // == 'm'
	if (array == NULL) {
		return 1;
	}

	free_resources('f', file, 'm', array, '\0');
	printf("DONE!");

	return 0;
}
