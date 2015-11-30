#include <stdio.h>

#ifndef MAGICNUM
#define MAGICNUM 0x495f3342
#endif

int x = 0x41424344;

void vuln() {
  int y = 1;
  char buf[128];

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

