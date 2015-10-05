#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

void get_user_input(char ** line, bool alpha) {
    size_t size = 0;
    size = getline(line, &size, stdin);
    assert(size);
    char * _line = *line;
    int i = 0;
    for (i = 0; i < size; i++) {
        if (_line[i] == 0)
            break;
        else if (_line[i] == 10) {
            _line[i] = 0;
            break;
        }
        if (alpha) {
            assert((_line[i] >= 65 && _line[i] <= 90) || (_line[i] >= 97 && _line[i] <= 122)); //Fail if current char is not an ASCII English letter
        } else {
            assert(_line[i] >= 48 && _line[i] <= 57);
        }
    }
}

void get_name(char ** name) {
    printf("What is your name?\n");
    get_user_input(name, true);
}

void get_number(char ** _number, char name []) {
    printf("What is your magic number, %s?\n", name);
    get_user_input(_number, false);
}


int  name_length(char * line, size_t size) {
    //assuming that line contains name and number separated by space!
    int i = 0;
    for (i = 0; i < size; i++) {
         assert (!(line[i] == 0 || line[i] == 10 || i + 1 == size)); //Should never reach end of line
        if (line[i] == 32)
            break;
        assert((line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122)); //Fail if current char is not an ASCII English letter
    }
    return i;
}

int  number_length(char * line, size_t number_begin, size_t size) {
    //assuming that line contains name and number separated by space!
    int i = 0;
    for (i = number_begin; i < size; i++) {
        if (line[i] == 0 || line[i] == 10) //END of line reached
            break;
        assert(line[i] >= 48 && line[i] <= 57);
    }
    return i;
}

void cmp_and_print(int cmp) {
    if (cmp == 0)  {
        printf("SUCCESS\n");
    } else if (cmp > 0) {
        printf("TOO HIGH\n");
    } else {
        printf("TOO LOW\n");
    }
    return;
}

int main() {
    char *line = NULL; // answers will be read here
    size_t len = 0;     // answers len
    ssize_t read = 0;       // answer line length
    char default_answer[6] = "12345"; //default answer
    char *pname = NULL;
    char *guessed_number = NULL;

    get_name(&pname);
    get_number(&guessed_number, pname);

    FILE *fp = fopen("/home/kmacarenco/gitHubRepos/PSU/cs591_intro_to_security/homeworks/1/questioner/answers.txt", "r");
    if (fp == NULL)  assert(fp != NULL);

    bool match = false;
    while ((read = getline(&line, &len, fp)) != -1) {

        int name_ends_at = name_length(line, read);
        line[name_ends_at] = 0;

        if (strcmp(pname, line) == 0) {
            int number_ends_at = number_length(line, name_ends_at + 1, read);
            line[number_ends_at] = 0;
            int cmp = strcmp(guessed_number, line + name_ends_at + 1);
            cmp_and_print(cmp);
            match = true;
            break;
        }
        free(line);
        line = NULL;
    }

    //Name not found in the answers.txt -> compare to default value
    if (!match) {
        int cmp = strcmp(guessed_number, default_answer);
        cmp_and_print(cmp);
    }

    fclose(fp);
    if (line != NULL) free(line);
    if (pname != NULL) free(pname);
    if (guessed_number != NULL) free(guessed_number);

    return 0;
}