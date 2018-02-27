#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <string>

using namespace std;

//s, d, b, f

void read_all(FILE *stream, char **result);

void handle_template(va_list *argsList, char *input, unsigned int *cursor, char templateKey);

int next_int(char *input, unsigned int *cursor);

void next_string(char *input, unsigned int *cursor, char **result);

bool next_bool(char *input, unsigned int *cursor);

int main() {
    const char *format = "%d %s %b\n%b\0";
    FILE *stream = fopen("/home/andrew/test", "r");
    int a = 0;
    char* b;
    bool c = false;
    bool d = false;
    fscanf(stream, format, &a, &b, &c, &d);
    printf("%d %s %s %s", a, b, c ? "true" : "false", d ? "true" : "false");
    free(b);
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

    char *input;
    unsigned int cursor = 0;
    read_all(stream, &input);
    printf("input is: %s", input);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            handle_template(&argsList, input, &cursor, format[i]);
        } else if (format[i] == input[cursor]) {
            cursor++;
        } else exit(2);
    }

    free(input);
    va_end(argsList);
}

void handle_template(va_list *argsList, char *input, unsigned int *cursor, char templateKey) {
    switch (templateKey) {
        case 'd':
            *va_arg(*argsList, int*) = next_int(input, cursor);
            break;
        case 's': {
            char* result;
            next_string(input, cursor, &result);
            *va_arg(*argsList, char**) = result;
            break;
        }
        case 'b':
            *va_arg(*argsList, bool*) = next_bool(input, cursor);
            break;
        default:
            break;
    }
}

int next_int(char *input, unsigned int *cursor) {
    char intStr[11];
    int counter = 0;
    for (unsigned long i = *cursor; i < strlen(input); i++) {
        if (isdigit(input[i]) || (i == *cursor && input[i] == '-'))
            intStr[counter++] = input[i];
        else break;
        (*cursor)++;
    }

    return atoi(intStr);
}

void next_string(char *input, unsigned int *cursor, char **result) {
    unsigned int startIndex = *cursor;
    for (unsigned long i = *cursor; i < strlen(input); i++) {
        if (isdigit(input[i]) || isblank(input[i]) || iscntrl(input[i]) || isspace(input[i]))
            break;
        (*cursor)++;
    }
    unsigned int desiredStrSize = *cursor - startIndex;
    *result = (char *)calloc(1, desiredStrSize + 1);
    memcpy(*result, input + startIndex, desiredStrSize);
}

bool next_bool(char *input, unsigned int *cursor) {
    bool result = false;
    unsigned long size = strlen(input) - *cursor + 1;
    if (size >= 4) {
        char* substr = (char*)calloc(1, 5);
        memcpy(substr, input + *cursor, 4);
        if (strcmp(substr, "true") == 0) {
            *cursor = *cursor + 4;
            result = true;
        }
        free(substr);
    } else if (size >= 5) {
        char* substr = (char*)calloc(1, 6);
        memcpy(substr, input + *cursor, 5);
        if (strcmp(substr, "false") == 0) {
            *cursor = *cursor + 5;
            result = false;
        }
        free(substr);
    } else exit(1);

    return result;
}

void read_all(FILE *stream, char **result) {
    long lSize;
    fseek( stream , 0L , SEEK_END);
    lSize = ftell( stream );
    rewind( stream );
    *result = (char *)calloc( 1, lSize+1 );
    fread( *result , lSize, 1 , stream);
    fclose(stream);
}