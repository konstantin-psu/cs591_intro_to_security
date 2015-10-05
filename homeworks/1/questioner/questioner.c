#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>


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

void get_input(char ** line, size_t size) {
    bool status = getline(line, &size, stdin);
    _assert(status);
}

void get_name(char * name, size_t * size) {
    printf("What is your name?\n");
    *size = 0;
    get_input(&name, *size);
    // Want to restrict input to English Alphabet in ASCII
    int i = 0;
    for (i = 0; i < *size; i++) {
        if (name[i] == 0 || name[i] == 10) //Read to the end of the Name (whichever comes first)
            break;
        _assert((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122)); //Fail if current char is not an ASCII English letter
    }
    *size = i;
}

int  name_length(char * line, size_t size) {
    //assuming that line contains name and number separated by space!
    int i = 0;
    for (i = 0; i < size; i++) {
         _assert (!(line[i] == 0 || line[i] == 10 || i + 1 == size)); //Should never reach end of line
        if (line[i] == 32)
            break;
        _assert((line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122)); //Fail if current char is not an ASCII English letter
    }
    return i;
}

int  number_length(char * line, size_t number_begin, size_t size) {
    //assuming that line contains name and number separated by space!
    int i = 0;
    for (i = number_begin; i < size; i++) {
        if (line[i] == 0 || line[i] == 10) //END of line reached
            break;
        _assert(line[i] >= 48 && line[i] <= 57);
    }
    return i;
}


void get_number(char * number, size_t * size, char name []) {
    printf("What is your magic number, %s?\n", name);
    get_input(&number, *size);
    // Want to restrict input to English Alphabet in ASCII
    int i = 0;
    for (i = 0; i < *size; i++) {
        if (number[i] == 0 || number[i] == 10) //Read to the end of the Name (whichever comes first)
            break;
        _assert(number[i] >= 48 && number[i] <= 57);
    }
    *size = i;
}

void cmp_and_print(int cmp) {
    if (cmp == 0)  {
        printf("SUCCESS");
    } else if (cmp > 0) {
        printf("TOO HIGH");
    } else {
        printf("TOO LOW");
    }
    return;
}

int main() {
    init();
    char * line = NULL; // answers will be read here
    size_t len = 0;     // answers len
    ssize_t read;       // answer line length
    char default_answer [6] = "12345"; //default answer
    int i = 0;          // iterator
    size_t size = 256;  // default input size
    size_t input_size = size; // input size 2 (will be modified during user data collection)
    char * input_line = NULL; //buffer for input line

    get_name(input_line, &input_size);

    char pname[input_size + 1];
    memset(pname, 0, input_size + 1);
    while (i < input_size) {
        pname[i] = input_line[i];
        i++;
    }
    memset(input_line, 0, size);
    input_size = size;

    get_number(input_line, &input_size, pname);

    char guessed_number[input_size + 1];
    memset(guessed_number, 0, input_size + 1);
    i = 0;
    while (i < input_size) {
        guessed_number[i] = input_line[i];
        i++;
    }


    char answers [12] = "answers.txt";
    //FILE *fp = fopen("/home/kmacarenco/gitHubRepos/PSU/cs591_intro_to_security/homeworks/1/questioner/answers.txt", "r");
    FILE *fp = fopen("/home/konstantin/gitHubRepos/PSU/cs591_intro_to_security/homeworks/1/questioner/answers.txt", "r");
    if (fp == NULL) { //TODO change to assert
        printf("Failed to open %s", answers);
        _assert(fp != NULL);
    }

    char * rname = _calloc(size);
    char * rnumber = _calloc(size);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);

        memset(rname, 0, size);
        memset(rnumber, 0, size);

        int name_ends_at = name_length(line, read);
        int number_ends_at = number_length(line, name_ends_at+1, read);
        strncpy(rname, line, name_ends_at);
        strncpy(rnumber, line + name_ends_at + 1, number_ends_at-name_ends_at -1);
        if (strcmp(pname, rname) == 0) {
            int cmp = strcmp(guessed_number, rnumber);
            cmp_and_print(cmp);
            fclose(fp);
            clean_exit();
        }
    }

    //Name not found in the answers.txt -> compare with walue

    int cmp = strcmp(guessed_number, default_answer);
    cmp_and_print(cmp);

    fclose(fp);
    clean_exit();
    return 0;
}

