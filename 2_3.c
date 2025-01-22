#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

int free_resources(char flag, ...) {
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
			va_end(args);
			break;
		}else{
			va_end(args);
			//break;
			return 1;
		}
		flag = va_arg(args, char);
	}
	return 0;
}

int main() {
	//some file
	FILE* file = fopen("nothing.txt", "r"); // == 'f'
	if (file == NULL) {
		return 1;
	}
	//some dinamic array
	char* array = NULL;
	array = (char*)malloc(15 * sizeof(char)); // == 'm'
	if (array == NULL) {
		return 1;
	}

	switch (free_resources('f', file, 'm', array, '\0')) {
	case 0:
		printf("DONE!");
		break;
	case 1:
		printf("error! flag is incorrect.\n");
		break;
	}
	
	return 0;
}
