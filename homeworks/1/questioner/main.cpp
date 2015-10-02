#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

char * get_name();

int main() {

//    char cwd[1024];
//    getcwd(cwd, sizeof(cwd));
//    printf("Current working dir: %s\n", cwd);
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char * name = NULL;
    char * token =NULL, * string = NULL;
    int def = 12345;
    char separator = ' ';
    int i = 0;
    char * player_name = "kon";

    get_name();


    char answers [12] = "answers.txt";
    FILE *fp = fopen("/home/konstantin/gitHubRepos/PSU/cs591_intro_to_security/homeworks/1/questioner/answers.txt", "r");
    if (fp == NULL) {
        printf("Failed to open %s", answers);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        i = 0;
        while ((token = strsep(&line, " ")) != NULL)
            if (i > 1 ) {
                exit(EXIT_FAILURE);
            } else if (i == 0) {
                strcmp(player_name,token);
            }
            i++;
            printf("%s\n", token);
    }

    fclose(fp);
    return 0;
}

char * get_input() {
    char * line = (char *)calloc(256, sizeof(char));
    if (!fgets(line, sizeof(line), stdin)) {
        exit(EXIT_FAILURE);
    }
    return line;
}

char * get_name() {
    printf("What is your name?\n");
    char * name = get_input();
    assert(name != NULL);
    size_t s = sizeof(*name)/sizeof(name);
    printf("%d\n", s);
//    for (int i = 0; i < sizeof(*name)/sizeof(name); i++) {
//        printf("%d", name[i]);
//    }
    return get_input();
}

char * get_number(char * name) {
    char * line = (char *)calloc(256, sizeof(char));
    int i;
    if (!fgets(line, sizeof(line), stdin)) {
        exit(EXIT_FAILURE);
    }
    return line;
}
