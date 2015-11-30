#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

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
      
      
      
int main(int argn, char* argv[])
{
    int i = 0;
    unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];
    char pass [] = "HackTheWorld";
 
    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(temp, 0x0, SHA_DIGEST_LENGTH);
 
    SHA1((unsigned char *)pass, strlen(argv[1]), temp);
 
    for (i=0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
    }

    char t[60];
    memset(t,0,60);
    for (i=0; i < SHA_DIGEST_LENGTH; i++) {
        t[0]=buf[i*2];
        t[1]=buf[i*2+1];
        printf("%02x\n", (int)strtol(t, NULL, 16));
    }
    printf("\n");
    SHA_CTX ctx;
    return 0;
}
