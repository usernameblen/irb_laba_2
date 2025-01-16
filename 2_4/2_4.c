#include<stdio.h>
#include<stdarg.h>

void clean_buf(char* buffer, size_t size) {
	for (int i = 0; i < size; i++) {
		buffer[i] = '\0';
	}
}

int strlenme(const char* str) {
	int cnt = 0;
	while (*str != '\0') {
		cnt++;
		str++;
	}
	return cnt;
}

//функция поиска подстроки, итог: номер символа
int find_the_index(const char* str, const char* substr) {
	for (int i = 0; i < strlenme(str); i++) {
		if (str[i] == substr[0]) {
			int g = 0;
			while (substr[g] != '\0' && str[i+g] == substr[g]) {
				g++;
			}
			if (substr[g] == '\0') {
				return i + 1;
			}
		}
	}

	return -1;//substr is not found
}

int find_the_substring(const char* substr, int count_of_files, ...) {
	if (*substr == 0) {//string is empty
		return 1;  
	}
	va_list(files);
	va_start(files, count_of_files);

	char* file_name;
	char buf[BUFSIZ], chr;
	int index_file, number_of_string, buffer_index, result_symbol;
	

	for (index_file = 0; index_file < count_of_files; index_file++) {
		file_name = va_arg(files, const char*);
		FILE* file = fopen(file_name, "r");
		if (file == NULL) {
			printf("File number %d is not open\n", index_file + 1);
			continue;//to next file
		}

		number_of_string = 1;
		buffer_index = 0;
		while ((chr = fgetc(file)) != EOF) {
			if (chr == '\n') {
				buf[buffer_index] = '\0';
				//найти подстроку в строке(+символ и номер строки)
				result_symbol = find_the_index(buf, substr);
				if (result_symbol != -1) {
					printf("File number %d: string number %d, index number %d (at 1)\n", index_file + 1, number_of_string, result_symbol);
				}
				number_of_string++;
				buffer_index = 0;
			}
			else {
				buf[buffer_index++] = chr;
			}
		}
		if (buffer_index > 0) {
			buf[buffer_index] = '\0';
			//найти подстроку в строке(+символ и номер строки)
			result_symbol = find_the_index(buf, substr);
			if (result_symbol != -1) {
				printf("File number %d: string number %d, index number %d (at 1)\n", index_file+1, number_of_string, result_symbol);
			}
		}

		fclose(file);
	}
	va_end(files);
	return 0;
}

int main() {

	switch (find_the_substring("hello", 3, "file_one.txt", "file_two.txt", "file_three.txt")) {
	case 0:
		printf("oh good, it is done.");
		break;

	case 1:
		printf("oookeey. the substring is empty...");
		break;

	}

	return 0;
}
