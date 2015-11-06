#include <stdio.h>
#include <malloc.h>
#include <string.h>

char* load_flag() {
  char *the_flag = (char *) malloc(32*sizeof(char));
  FILE *f = fopen("/home/flags/hw03/flag02.txt", "r");
  fscanf(f, "%31s", the_flag);
  fclose(f);
  return the_flag;
}

int main(int argc, char *argv[]) 
{
  char *flag = load_flag();
  char *reason = (char *) malloc(64*sizeof(char));

  printf("Why should I give you the flag?  ");
  scanf("%63s", reason);

  printf("\n");
  printf("I'm not sure that \"");
  printf(reason);
  printf("\" is a very good reason.\n");

  return 0;
}
