#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_NUM (1<<16)

unsigned int get_random() {
  unsigned int x = 0;
  int fd = open("/dev/urandom", O_RDONLY);
  int rc = read(fd, &x, sizeof(int));
  close(fd);
  return x;
}

int play_game(const char *name) {
  int a = 1;
  int magic = get_random() % MAX_NUM;
  int b = 2;
  int guess = 0;

  printf("What is the magic number, ");
  printf(name);
  printf("?  ");
  scanf("%d", &guess);

  return (guess == magic);
}


int main(int argc, char* argv[])
{
  char name[32];
  int success = 0;

  srand(time(NULL));

  printf("What is your name?  ");
  scanf("%31s", name);

  success = play_game(name);
  if(success){
    printf("You win!\n");
    system("/bin/sh");
  }
  else {
    printf("Sorry, try again.\n");
  }

  return 0;
}
