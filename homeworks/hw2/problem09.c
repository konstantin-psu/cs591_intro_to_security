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

  return 0;
}

int main(int argc, char* argv[])
{
  vuln();
  return 0;
}

0xbffff540
0x0804859f <+0>:   push   %ebp
0x080485a0 <+1>: mov    %esp,%ebp
0x080485a2 <+3>: and    $0xfffffff0,%esp
0x080485a5 <+6>: call   0x80484dd <vuln>
0x080485aa <+11>:    mov    $0x0,%eax
0x080485af <+16>:    leave  
0x080485b0 <+17>:    ret    

                        0x0032322d  0xb7fd23c4  0xb7fff000
0xbffff748: 0xbffff758  0x080485aa

0xbffff738: 0xbffff7fc  0xb7e5b42d  0xb7fd23c4  0xb7fff000
0xbffff748: 0xbffff758  0x080485aa  0x080485c0  0x00000000
0xbffff758: 0x00000000  0xb7e41a83  0x00000001  0xbffff7f4
0xbffff768: 0xbffff7fc  0xb7feccea  0x00000001  0xbffff7f4
0xbffff778: 0xbffff794  0x0804a020  0x0804825c  0xb7fd2000
0xbffff788: 0x00000000  0x00000000  0x00000000  0xaa3399ee
0xbffff798: 0x9de9ddfe


1d323232c423fdb710f0ffb7 58 f7 ff bf aa 85 04 08   





