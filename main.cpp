#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <string>

using namespace std;

//s, d, b, f

void handleTemplate(va_list *argsList, string *input, unsigned int* cursor, char templateKey);

int nextInt(string *input, unsigned int* cursor);

void nextString(string *input, unsigned int* cursor, string* result);

bool nextBool(string *input, unsigned int* cursor);

int main() {
    const char *format = "%d %s %b\0";
    int a = 0;
    string b;
    bool c = false;
    sscanf("12 sfdf true", format, &a, &b, &c);
    printf("%d %s %s", a, b.c_str(), c ? "true" : "false");
    return 0;
}

int sscanf(const char* input, const char *format, ...) {
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

    string inputStr = string(input);
    unsigned int cursor = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            handleTemplate(&argsList, &inputStr, &cursor, format[i]);
        } else if (format[i] == input[cursor]) {
            cursor++;
        } else exit(2);
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
            *va_arg(*argsList, bool*) = nextBool(input, cursor);
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

bool nextBool(string *input, unsigned int* cursor) {
    unsigned long size = input->size() - *cursor + 1;
    if (size >= 4 && input->substr(*cursor, 4) == "true") {
        *cursor = *cursor + 4;
        return true;
    } else if (size >= 5 && input->substr(*cursor, 5) == "false") {
        *cursor = *cursor + 5;
        return false;
    } else exit(1);
}