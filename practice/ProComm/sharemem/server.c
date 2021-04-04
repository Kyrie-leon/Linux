#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include"comm.h"
#include<sys/shm.h>

int main()
{
  key_t k = ftok(PATHNAME,PROJ_ID);  
  printf("key:%p\n",k);
  int shmid = shmget(k,SIZE, IPC_CREAT|IPC_EXCL|0666);
  if(shmid < 0)
  {
    perror("shmget");
    return 1;
  }
  printf("shmid:%d\n", shmid);

  sleep(10);
  char * str = shmat(shmid,NULL,0);
  while(1)
  {
    printf("%s\n",str);
  }

  shmdt(str);
  sleep(5);

  shmctl(shmid, IPC_RMID,NULL);

  sleep(10);
  return 0;
}
