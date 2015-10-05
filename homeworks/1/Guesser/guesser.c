#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

const char MYNAME [4] = "Bob";

void get_user_input(char ** line) {
    size_t size = 0;
    size = getline(line, &size, stdin); //read line
    assert(size); //make sure read succeeded
    char * _line = *line;
    _line[size - 1] = 0;
}

void ask_name() {
    char * question_buffer = NULL;
    get_user_input(&question_buffer);
    char buffer [50];
    sprintf(buffer, "What is your name?");
    if(strcmp(question_buffer, buffer) == 0) printf("%s\n", MYNAME);
    else {
        free(question_buffer);
        printf("???"); exit(0);
    }
    free(question_buffer);
}

void ask_number() {
    char * question_buffer = NULL;
    get_user_input(&question_buffer);
    char buffer [50];
    sprintf(buffer, "What is the magic number, %s?",MYNAME);
    if(strcmp(question_buffer, buffer) == 0) printf("12345\n");
    else {
        free(question_buffer);
        printf("???"); exit(0);
    }
    free(question_buffer);
}

void ask_hint() {
    char * question_buffer = NULL;
    get_user_input(&question_buffer);
    if (strcmp(question_buffer, "TOO HIGH") == 0 || strcmp(question_buffer, "TOO LOW") == 0 || strcmp(question_buffer, "SUCCESS") == 0) {
        free(question_buffer);
        exit(0);
    } else {
        free(question_buffer);
        exit(1);
    }
}

int main() {
    ask_name();
    ask_number();
    ask_hint();
    return 0;
}
