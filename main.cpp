#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <string>

using namespace std;

//s, d, b, f

void *readAll(FILE *stream, string *result);
void handleTemplate(va_list* argsList, string* input, int startIndex, char templateKey);
int nextint(string* input, int startIndex);

int main() {
    const char* format = "%s\0";
    FILE *stream = fopen("/home/andrew/test", "r");
    fscanf(stream, format);
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
            keys[i] = format[i+1];
    }

    va_list argsList;
    va_start(argsList, keysCount);

    string input;
    readAll(stream, &input);
    printf("input is: %s", input.c_str());

    for (int i = 0; format[i] != '\0'; i++) {

    }

    va_end(argsList);
}

void handleTemplate(va_list* argsList, string* input, int startIndex, char templateKey) {
    switch (templateKey) {
        case 'd':

            break;
        case 's':

            break;
        case 'b':

            break;
        default:
            break;
    }
}

int nextint(string* input, int startIndex) {
    match_results matchResults;
    regex e("^-?[0-9]+");
    regex_search(input, matchResults, e);
}

void *readAll(FILE *stream, string* result) {
    int buffer;
    while ((buffer = fgetc(stream)) != '\0') {
        if (buffer == EOF) break;
        *result += (char)buffer;
    }
}