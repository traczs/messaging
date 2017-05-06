#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stream.h"

int main(int argc, char *argv[]) {
  int i= 0;
  int remove =0;
  char*author;
  char* streams;
  author = malloc(sizeof(char)*175);
  streams = malloc(sizeof(char)*255);
  for(i=1;i<argc;i++)
  {
    if(strcmp(argv[i],"-r")==0)
    {
      remove =1;
    }
    else
    {
      strcat(author,argv[i]);
      strcat(author,"_");
    }
  }
  printf("list streams: ");
  fgets(streams,255,stdin);
  if(remove ==1)
  {
    removeUser(author,streams);
  }
  else
  {
    addUser(author,streams);
  }
  free(author);
  /*free(streams);*/
  return 0;
}
