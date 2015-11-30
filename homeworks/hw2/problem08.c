#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void (*func_ptr)(void) = NULL;

int vuln() {
  char age[3];
  char name[256];
  char favcolor[256];

  /* Read exploit code from the attacker */
  puts("How old are you?");
  gets(age);
  if(atoi(age) < 18) {
    puts("You are too young to play!");
    return -18;
  }

  puts("What is your name?");
  gets(name);
  if(strlen(name) != 6) {
    puts("Name check failed.");
    return -1;
  }

  puts("What is your favorite color?");
  gets(favcolor);
  printf("Read %d characters of favorite color.\n", strlen(favcolor));

  /* And execute it */
  func_ptr = favcolor;
  func_ptr();

  return 0;
}

int main(int argc, char* argv[])
{
  vuln();
  return 0;
}
