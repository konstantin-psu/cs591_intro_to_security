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
      
      
      
int main(int argc, char* argv[])
{
    SHA_CTX ctx;
    return 0;
}
