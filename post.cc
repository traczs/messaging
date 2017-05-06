#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "stream.h"


struct PostEntry{
  struct userPost *  (*readInput)();
  struct userPost * (*formatEntry)();
  void (*getTimeDate)();
  void (*submitPost)();
};
typedef struct PostEntry PostEntry;

void submitPost(struct userPost *st)
{
  updateStream(st);
}

void getTimeDate(char**date)
{
  char date2[65];
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  strftime(date2, sizeof(date2), "%c", tm);
  strcpy(*date,date2);
}

struct userPost * formatEntry(char*author,char*stream,char*text)
{
  char *date = malloc(sizeof(char)*500);
  struct userPost * post = malloc(sizeof(struct userPost));
  post->username = malloc(sizeof(char)*strlen(author)+1);
  strcpy(post->username,author);
  post->streamname = malloc(sizeof(char)*strlen(stream)+1);
  strcpy(post->streamname,stream);
  post->text = malloc(sizeof(char)*strlen(text)+1);
  strcpy(post->text,text);
  getTimeDate(&date);
  post->date = malloc(sizeof(char)*strlen(date)+1);
  strcpy(post->date,date);
  free(date);
  return post;

}

struct userPost * readInput(int argc,char *argv[])
{
  struct userPost * temp = NULL;
  char*author;
  char*stream;
  char*text;
  char*tempText;
  author = malloc(sizeof(char)*175);
  stream = malloc(sizeof(char)*175);
  text = malloc(sizeof(char)*500);
  tempText = malloc(sizeof(char)*500);
  int i=0;
  int authorLen=0;
  for(i=1;i<argc;i++)
  {
    if(authorLen>=175)
    {
      break;
    }
    strcat(author,argv[i]);
    strcat(author,"_");
    authorLen = strlen(author);
  }
  printf("stream: ");
  fgets(stream,175,stdin);
  stream = strtok(stream,"\n");
  printf("enter text: ");
  while((fgets(tempText,500,stdin)))
  {
    strcat(text,tempText);
    printf("-");
  }
  temp = formatEntry(author,stream,text);
  /*free(temp->username);
  free(temp->streamname);
  free(temp->date);
  free(temp->text);
  free(temp);*/

  free(author);
  free(stream);
  free(text);
  free(tempText);
  return temp;
}


void constructorPost(struct PostEntry * tempStr)
{
  tempStr->readInput = readInput;
  tempStr->formatEntry = formatEntry;
  tempStr->getTimeDate = getTimeDate;
  tempStr->submitPost = submitPost;
}

int main(int argc, char *argv[]) {
  struct userPost * temp = NULL;
  PostEntry newEntry;
  constructorPost(&newEntry);
  temp = newEntry.readInput(argc,argv);
  newEntry.submitPost(temp);
  /*printf("time : %s\n",temp->date);*/

  free(temp->streamname);
  free(temp->username);
  free(temp->text);
  free(temp->date);
  free(temp);
  return 0;
}
