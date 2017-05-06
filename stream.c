#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "stream.h"

void updateStream(struct userPost *st)
{
   FILE * file;
   static int filesize;
   char*filename = malloc(sizeof(char)*50);
   char*itoa = malloc(sizeof(char)*10);
   strcpy(filename,"messages/");
   strcat(filename,st->streamname);
   strcat(filename,"StreamUsers");
   file = fopen(filename,"r");
   if(!file)
   {
     printf("Stream does not exist\n");
     return;
   }
   char* c= malloc(sizeof(char)*255);
   char*temp= malloc(sizeof(char)*175);
   int add =1;
   while(fgets(c,255,file)!=NULL)
   {
     char*user = strtok(c," ");
     if(strcmp(user,st->username)==0)
     {
       add = 0;
     }
   }
   if(add==1)
   {
     printf("User does not have access to the stream\n");
     return;
   }
    fclose(file);
    free(temp);
    free(c);

   strcpy(filename,"messages/");
   strcat(filename,st->streamname);
   strcat(filename,"Stream");
   file = fopen(filename,"a");
   fputs("Sender: ",file);
   fputs(st->username,file);
   fputs("\n",file);
   fputs("Date: ",file);
   fputs(st->date,file);
   fputs("\n",file);
   fputs(st->text,file);
   fseek(file,0,SEEK_END);
   filesize = ftell(file);
   fclose(file);

   strcpy(filename,"messages/");
   strcat(filename,st->streamname);
   strcat(filename,"StreamData");
   file = fopen(filename,"a");
   sprintf(itoa,"%d",filesize);
   fputs(itoa,file);
   fputs("\n",file);
   free(itoa);
   fclose(file);


    free(filename);

}


void addUser(char *username, char *list)
{
  FILE* file;
  char*filename = malloc(sizeof(char)*50);
  char** streams;
  streams = malloc(sizeof(char*)*200);
  int q=0;
  for (q = 0; q < 200; q++) {
    streams[q] = malloc(sizeof(char)*200);
  }
  int i=1;
  int j =0;
  char*temp1 = malloc(sizeof(char)*255);
  streams[0] = strtok(list,",\n");
  while((temp1=strtok(NULL," ,\n")) != NULL)
  {
    strcpy(streams[i],temp1);
    i++;
  }
  free(temp1);


  for(j=0;j<i;j++)
  {
    strcpy(filename,"messages/");
    strcat(filename,streams[j]);
    strcat(filename,"StreamUsers");
    /*adding the stream names to a big list for the python program*/
    file = fopen("StreamList","a+");
    char* c1= malloc(sizeof(char)*255);
    char*temp1= malloc(sizeof(char)*175);
    int add =1;
    while(fgets(c1,255,file)!=NULL)
    {
      char*user = strtok(c1,"\n");
      if(strcmp(user,streams[j])==0)
      {
        add = 0;
      }
     }
     if(add==1)
     {
       fputs(streams[j],file);
       fputs("\n",file);
     }
     fclose(file);
     free(temp1);
     free(c1);

    file = fopen(filename,"a+");
    char* c= malloc(sizeof(char)*255);
    char*temp= malloc(sizeof(char)*175);
    add =1;
    while(fgets(c,255,file)!=NULL)
    {
      char*user = strtok(c," ");
      if(strcmp(user,username)==0)
      {
        add = 0;
        printf("username already exists in one or more streams\n");
      }
     }
     if(add==1)
     {
       fputs(username,file);
       fputs(" 0\n",file);
     }
     fclose(file);
     free(temp);
     free(c);
   }

   for (q = 0; q < 200; q++) {
     free(streams[q]);
   }
   free(streams);
   free(filename);
}

void removeUser(char *username, char *list)
{
  FILE* file;
  char*filename = malloc(sizeof(char)*50);
  char** streams;
  streams = malloc(sizeof(char*)*200);
  int q=0;
  for (q = 0; q < 200; q++) {
    streams[q] = malloc(sizeof(char)*200);
  }
  int i=1;
  int j =0;
  char*temp1;
  streams[0] = strtok(list,",\n");
  while((temp1=strtok(NULL,",\n")) != NULL)
  {
    strcpy(streams[i],temp1) ;
    i++;
  }


  for(j=0;j<i;j++)
  {
    strcpy(filename,"messages/");
    strcat(filename,streams[j]);
    strcat(filename,"StreamUsers");
    file = fopen(filename,"r");
    char* c= malloc(sizeof(char)*255);
    char* d= malloc(sizeof(char)*255);
    char*temp= malloc(sizeof(char)*175);
    char* fileTemp = malloc(sizeof(char)*50000);
    strcpy(fileTemp,"");
    while(fgets(c,255,file)!=NULL)
    {
      strcpy(d,c);
      char*user = strtok(c," ");
      if(strcmp(user,username)!=0)
      {
        strcat(fileTemp,d);
      }
    }
    fclose(file);
    file = fopen(filename,"w");
    fputs(fileTemp,file);
    fclose(file);
    free(temp);
    free(fileTemp);
    free(d);
    free(c);
   }

   for (q = 0; q < 200; q++) {
     free(streams[q]);
   }
   free(streams);
   free(filename);

}
