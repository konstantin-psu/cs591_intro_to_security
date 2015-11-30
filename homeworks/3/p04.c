#include <stdio.h>

#ifndef MAGICNUM
#define MAGICNUM 0x41424344
#endif


void vuln() {
  int x = 0;
  int y = 1;
  char buf[128];

  printf("This is vuln() \tx = %08x \ty = %08x\n", x, y);
  printf("Enter your input: ");
  scanf("%127s", buf);
  printf("You entered: ");
  printf(buf);
  printf("\n\n");
  printf("Now x = %08x and y = %08x\n", x, y);

  if(x==MAGICNUM) {
    printf("Success!\n");
    system("/bin/sh");
  }
  else {
    puts("Sorry, try again.");
  }

  return;
}

int main(int argc, char* argv[])
{
  vuln();
  return 0;
}

