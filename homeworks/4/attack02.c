#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#define HASHSIZE 54
#define PSIZE 100

struct passw {
    char name[PSIZE];
    char hashedPassword[PSIZE];
    char plainPassword[PSIZE];
};

char toLower(char c) {
    return (c <= 'Z' && c >= 'A') ? c + 32 : c;
}

char toUpper(char c) {
    return (c <= 'z' && c >= 'a') ? c - 32 : c;
}

void print_hex(unsigned char *buf, int len)
{
    int i;
    int n;

    for(i=0,n=0;i<len;i++){
        if(n > 7){
            printf("\n");
            n = 0;
         }
        printf("%02x",buf[i]);
        n++;
    }
    printf("\n");
}

void lower(char * dst, char * src) {
    int i = 0;
    while(src[i] != 0) {
        dst[i] = toLower(src[i]);
        i++;
    }

}

void upper(char * dst, char * src) {
    int i = 0;
    while(src[i] != 0) {
        dst[i] = toUpper(src[i]);
        i++;
    }

}

void ulow(char * dst, char * src) { // First capitalized
    int i = 0;
    dst[i] = toLower(src[i]);
    i = 1;
    while(src[i] != 0) {
        dst[i] = toUpper(src[i]);
        i++;
    }
}

void uonly(char * dst, char * src) { // First capitalized
    int i = 0;
    dst[i] = toLower(src[i]);
    i = 1;
    while(src[i] != 0) {
        dst[i] = src[i];
        i++;
    }
}

int searchOccurrence(char * hashed, char * plain, struct passw * src) {
    int i = 0;
    int flag = 0;
    for (i= 0 ; i < HASHSIZE ; i++) {
        if (!strcmp(hashed, src[i].hashedPassword)) {
            strcpy(src[i].plainPassword,plain);
            flag = 1;
        }
    }
    return flag;
}
void readHashedPasswords(char *source, struct passw *dst) {
    // 1. read name
    memset(dst->hashedPassword,0,PSIZE);
    memset(dst->plainPassword,0,PSIZE);
    memset(dst->name,0,PSIZE);
    int i = 0;
    int tempI = 0;
    while(source[i] == 32) i++;
    while(source[i] != 32) {
        dst->name[tempI] = source[i];
        i++;tempI++;
    }
    dst->name[tempI]=0;
    tempI = 0;
    while(source[i] == 32) i++;
    while(source[i] != 32 && source[i] != 10) {
        dst->hashedPassword[tempI] = source[i];
        i++;tempI++;
    }
    dst->hashedPassword[tempI]=0;
}

void readHashedFile(struct passw * passwords) {
    char location [] = "/home/kmacarenco/gitHubRepos/PSU/cs591_intro_to_security/homeworks/4/hashed.txt";
    FILE * p = fopen(location, "r"); // Open file with reading permission
    size_t len = 0;
    size_t lsize = 0;
    char * line = NULL;
    if (p == NULL) {
        printf("Failed to open %s\n", location);
        exit(1);
    }
    int count = 0;

    while ((lsize = getline(&line, &len, p)) != -1) {
        readHashedPasswords(line, &(passwords[count]));
       count++;
    }
    if (count > HASHSIZE) exit(1);
}
      
int main(int argn, char* argv[])
{
    struct passw passwords [HASHSIZE];
    int i = 0;
    unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];
    char location [] = "/usr/share/dict/words";
    char * dict_word = NULL;
    char variation [PSIZE];
    memset(variation, 0,PSIZE);
    size_t len = 0;
    size_t lsize = 0;
    int j = 0;

    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(temp, 0x0, SHA_DIGEST_LENGTH);
    readHashedFile(passwords);

    FILE * p = fopen(location, "r"); // Open file with reading permission
    if (p == NULL) {
        printf("Failed to open %s\n", location);
        exit(1);
    }
    while ((lsize = getline(&dict_word, &len, p)) != -1) {

        dict_word[lsize-1] = 0;
        SHA1((unsigned char *)dict_word, lsize-1, temp);
        for (i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
        }

        searchOccurrence(buf, dict_word, passwords);
        memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
        memset(temp, 0x0, SHA_DIGEST_LENGTH);

        lower(variation, dict_word);
        SHA1((unsigned char *)variation, lsize-1, temp);
        for (i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
        }
        searchOccurrence(buf, variation, passwords);
        memset(variation, 0,PSIZE);
        memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
        memset(temp, 0x0, SHA_DIGEST_LENGTH);

        upper(variation, dict_word);
        SHA1((unsigned char *)variation, lsize-1, temp);
        for (i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
        }
        searchOccurrence(buf, variation, passwords);
        memset(variation, 0,PSIZE);
        memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
        memset(temp, 0x0, SHA_DIGEST_LENGTH);

        ulow(variation, dict_word);
        SHA1((unsigned char *)variation, lsize-1, temp);
        for (i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
        }
        searchOccurrence(buf, variation, passwords);
        memset(variation, 0,PSIZE);
        memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
        memset(temp, 0x0, SHA_DIGEST_LENGTH);

        uonly(variation, dict_word);
        SHA1((unsigned char *)variation, lsize-1, temp);
        for (i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
        }
        searchOccurrence(buf, variation, passwords);
        memset(variation, 0,PSIZE);
        memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
        memset(temp, 0x0, SHA_DIGEST_LENGTH);
    }
 
    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(temp, 0x0, SHA_DIGEST_LENGTH);

    for  (j = 0; j < HASHSIZE; j++) {
        printf("uname %s hashed %s Decoded %s\n", passwords[j].name, passwords[j].hashedPassword, passwords[j].plainPassword);
    }

    SHA_CTX ctx;
    fclose(p);
    return 0;
}
