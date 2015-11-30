#include <stdio.h>

void vuln() {
  int x = 0;
  int y = 1;
  char buf[256];

  printf("This is vuln()\n");
  printf("Enter your input: ");
  scanf("%254s", buf);
  printf("You entered: ");
  printf(buf);

  return;
}

int main(int argc, char* argv[])
{
  vuln();
  printf("Sorry, try again.");
  return 0;
}
