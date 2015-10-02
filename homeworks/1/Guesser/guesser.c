#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

const char MYNAME [4] = "Bob";

//the only global variable to keep track of all allocated pointers
struct pointers_tracker {
    char * allocated[40];
    size_t tot_size;
    size_t allcoated_size;
};

struct pointers_tracker tracker;

void init() {
    tracker.tot_size = 40;
    tracker.allcoated_size = 0;
}

char * _calloc(size_t  size) { // In this exercise allocating only strings.
    char * ptr = (char*)calloc(size, sizeof(char));
    tracker.allocated[tracker.allcoated_size] = ptr;
    tracker.allcoated_size++;
    return ptr;
};
void cleanup() {
    int i = 0;
    for (i = 0; i< tracker.allcoated_size;i++) {
        free(tracker.allocated[i]);
    }
}

void _assert(bool condition) {
    if (condition) return;
    cleanup();
    assert(condition);
}

void clean_exit() {
    cleanup();
    exit(0);
}

void get_input(char * line, size_t size) {
    bool status = fgets(line, size, stdin);
    _assert(status);
}
void flush() {
    char c;
    while((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}
void get_name_question() {
    const size_t q_size = 19;
    char * question_buffer = _calloc(256);
    char name_question_template [q_size];
    strcpy(name_question_template, "What is your name?");
    get_input(question_buffer, 256);
    question_buffer[q_size - 1] = 0;

    _assert(strcmp(question_buffer, name_question_template) == 0);
    printf("%s\n", MYNAME);
}



void get_number_question() {
    const size_t q_size = 31;
    char * question_buffer = _calloc(256);
    char number_question_template [q_size];
    sprintf(number_question_template, "What is the magic number, %s?", MYNAME);
    get_input(question_buffer, 256);
    question_buffer[q_size - 1] = 0;

    _assert(strcmp(question_buffer, number_question_template) == 0);
    printf("12345");

}


int main() {
    init();
    get_name_question();
    get_number_question();
    clean_exit();
    return 0;
}
