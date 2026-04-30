#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Usage: test_scheduler <tickets>\n");
    exit(1);
  }

  int tickets = atoi(argv[1]);

  if(settickets(tickets) < 0){
    printf("Error setting tickets\n");
    exit(1);
  }

  while(1){
    // keep running
  }

  return 0;
}