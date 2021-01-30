#include "proc.h"

void proc()
{
  int i = 0;
  char bar[NUM]; //用于存放进度条数组
  memset(bar, 0, sizeof(bar));
  char label[] = "|/-\\";

  for(i = 0; i < 100; ++i)
  {
    bar[i] = '#';
    printf("[%-100s][%3d%%][%c]\r", bar, i+1, label[i%4]);
    fflush(stdout);
    usleep(100000);
  }
  printf("\n");
}
