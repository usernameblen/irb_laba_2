#include <stdio.h>
//↓работа с динам. памятью ↓
#include<stdlib.h> 
//изменение регистра↓
#include<ctype.h>
#include<math.h>

//ФУНКЦИИ ДЛЯ ДРУГИХ ФУНКЦИЙ

char* strcatmy(char* first, const char* second) {

    //создаем указатель на первую строку, чтобы еë прочесть и не потерять указатель на начало строки
    char* ptr = first;
    while (*ptr != '\0') {
        ptr++;
    }

    //не создаем доп. указатель, тк. мы просто читаем строку и в эьом нет необходимости
    while (*second != '\0') {
        *ptr = *second;
        ptr++;
        second++;
    }
    *ptr = '\0';

    return first;
}

//функция подсчета длины 
int strlenn(const char* str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

//функция strcpy
char* strcpyy(const char* str, char* result) {
    int len = strlenn(str);
    for (int i = 0; i < len; i++) {
        result[i] = str[i];
    }
    result[len] = '\0';
    return result;
}

int strcmpp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 < *str2) {
            return -1;
        }
        else if (*str1 > *str2) {
            return 1;
        }
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0') {
        return 0;
    }
    else if (*str1 == '\0') {
        return -1;
    }
    else {
        return 1;
    }
}



//ОСНОВНЫЕ ФУНКЦИИ

//функция подсчета длины
char* strlenme(const char* str) {
    int len = strlenn(str);
    //вычислим колво цифр в len(ceil - округление вверх)
    int quan_sym = (int)ceil(log10(len + 1)) + 1;/* для завершующего нуля*/
    char* result = (char*)malloc(quan_sym);
    if (result == NULL) {
        return NULL;
    }

    //функция число -> строка
    snprintf(result, quan_sym, "%d", len);

    return result;
}

// функция для переворота строки
char* reverse_string(const char* str) {
    int n = strlenn(str);
    char* result = (char*)malloc(n + 1);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        result[i] = str[n - i - 1];
    }
    result[n] = '\0';
    return result;
}

//нечетный элемент - большой регистр
char* big_letter(const char* str) {
    int len = strlenn(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        if (i % 2 == 1) {
            result[i] = str[i] - 32;
        }
        else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';
    return result;
}

//сортировка в нужном порядке
char* sortt(const char* str) {
    int len = strlenn(str);
    char* result = (char*)malloc(len + 1);
    strcpyy(str, result);

    char* ptr = result;
    int i = 0;
    char temp;

    //сортировка цифр 
    for (; *ptr != '\0'; ptr++) {
        if (*ptr >= '0' && *ptr <= '9') {
            temp = result[i];
            result[i] = *ptr;
            *ptr = temp;
            i++;
        }
    }

    //поставим указатель на первый элемент не цифру 
    i = 0;
    for (ptr = result; *ptr >= '0' && *ptr <= '9'; ptr++) {
        i++;
    }

    //сортировка букв 
    for (; *ptr != '\0'; ptr++) {
        if ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')) {
            char temp = result[i];
            result[i] = *ptr;
            *ptr = temp;
            i++;
        }
    }

    return result;
}

char* concat(char** strings, int count) {
    int total_len = 0;
    for (int i = 0; i < count; i++) {
        total_len += strlenn(strings[i]);
    }

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcatmy(result, strings[i]);
    }

    return result;
}


void generate(char** strings, int count) {
    for (int i = 0; i < count; i++) {
        int j = rand() % count;
        char* temp = strings[i];
        strings[i] = strings[j];
        strings[j] = temp;
    }
}

int main(int argc, char* argv[]) {
    //checking the number of arguments
    if (argc < 3) {
        printf("not enough arguments: flag, string(s)\n");
        return 1;
    }

    char* flag = &argv[1][1];
    char* str = argv[2];

    if (strcmpp(flag, "l") == 0) {
        printf("Result: %s\n", strlenme(str));
    }
    else if (strcmpp(flag, "r") == 0) {
        char* result = reverse_string(str);
        printf("Result: %s\n", result);
    }
    else if (strcmpp(flag, "u") == 0) {
        char* result = big_letter(str);
        printf("Result: %s\n", result);
    }
    else if (strcmpp(flag, "n") == 0) {
        char* result = sortt(str);
        printf("Result: %s\n", result);
    }
    else if (strcmpp(flag, "c") == 0) {
        //checking the number of arguments
        if (argc < 4) {
            printf("not enough arguments: seed, string(s)\n");
            return 1;
        }
        //                 из строки в число
        unsigned int seed = (unsigned int)atoi(argv[2]);
        srand(seed);
        //kol-vo strings
        int count = argc - 3;//name of file & flag & seed


        //array of strings
        char** strings_to_cat = (char**)malloc(count * sizeof(char*));
        if (strings_to_cat == NULL) {
            printf("Erorr with memory");
            return 1;
        }

        //int index = 0;
        for (int i = 3; i < argc; i++) {
            strings_to_cat[i - 3] = argv[i];
        }

        generate(strings_to_cat, count);
        char* result = concat(strings_to_cat, count);
        printf("result: %s", result);

        free(result);
        free(strings_to_cat);
    }
    else {
        printf("Erorr flag, menyay!");
        return 1;
    }

    return 0;
}
