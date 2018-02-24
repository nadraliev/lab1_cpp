#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <string>

using namespace std;

//s, d, b, f

void readAll(FILE *stream, string *result);

void handleTemplate(va_list *argsList, string *input, unsigned int* cursor, char templateKey);

int nextInt(string *input, unsigned int* cursor);

void nextString(string *input, unsigned int* cursor, string* result);

int main() {
    const char *format = "%d%s\0";
    FILE *stream = fopen("/home/andrew/test", "r");
    int a = 0;
    string b;
    fscanf(stream, format, &a, &b);
    printf("%d %s", a, b.c_str());
    return 0;
}

int fscanf(FILE *stream, const char *format, ...) {
    int keysCount = 0;
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') keysCount++;
    }
    printf("Number of keys: %d\n", keysCount);

    char *keys = new char[keysCount];
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            keys[i] = format[i + 1];
    }

    va_list argsList;
    va_start(argsList, format);

    string input;
    unsigned int cursor = 0;
    readAll(stream, &input);
    printf("input is: %s", input.c_str());

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            handleTemplate(&argsList, &input, &cursor, format[i]);
        }
    }

    va_end(argsList);
}

void handleTemplate(va_list *argsList, string *input, unsigned int* cursor, char templateKey) {
    switch (templateKey) {
        case 'd':
            *va_arg(*argsList, int*) = nextInt(input, cursor);
            break;
        case 's': {
            string result;
            nextString(input, cursor, &result);
            *va_arg(*argsList, string*) = result;
            break;
        }
        case 'b':

            break;
        default:
            break;
    }
}

int nextInt(string *input, unsigned int* cursor) {
    string intStr;
    unsigned long size = input->size() - *cursor;
    for (unsigned long i = *cursor; i < size; i++) {
        if (isdigit((*input)[i]) || (i == *cursor && (*input)[i] == '-'))
            intStr += (*input)[i];
        else break;
        (*cursor)++;
    }

    return stoi(intStr);
}

void nextString(string *input, unsigned int* cursor, string* result) {
    unsigned long size = input->size() - *cursor + 1;
    for (unsigned long i = *cursor; i < size; i++) {
        if (!isdigit((*input)[i]) && !isblank((*input)[i]) && !iscntrl((*input)[i]) && !isspace((*input)[i]))
            *result += (*input)[i];
        else break;
        (*cursor)++;
    }
}

void readAll(FILE *stream, string *result) {
    int buffer;
    while ((buffer = fgetc(stream)) != '\0') {
        if (buffer == EOF) break;
        *result += (char) buffer;
    }
}