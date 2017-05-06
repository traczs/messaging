#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[])
{
  FILE* codeFile;
  codeFile = fopen(argv[1],"r");
  FILE* outFile;
  int i;
  char file[50];
  for(i=0;i<50;i++)
  {
    file[i] = '\0';
  }
  for(i=0;i<strlen(argv[1])-1;i++)
  {
      file[i] = argv[1][i];
  }
  file[strlen(argv[1])-1] = '\0';
  outFile = fopen(file,"w");
  char c;
  char tempc;
  int charCountw = 0;
  int charCount = 0;
  int wordCount = 0;

  /*initialization of all the 2d arrrays*/
  char** keyWord;
  char** whiteSpace;
  char**definitions;
  char**tempArr;
  char** funcArr;
  keyWord = malloc(sizeof(char*)*2000);
  whiteSpace= malloc(sizeof(char*)*2000);
  definitions=malloc(sizeof(char*)*2000);
  tempArr = malloc(sizeof(char*)*2000);
  funcArr= malloc(sizeof(char*)*2000);

  for(i = 0; i < 2000; i++)
  {
    keyWord[i] = malloc(sizeof(char)*2000);
    definitions[i]=malloc(sizeof(char)*2000);
    tempArr[i]=malloc(sizeof(char)*2000);
    whiteSpace[i] = malloc(sizeof(char)*2000);
    funcArr[i] = malloc(sizeof(char)*2000);
  }
  int j;
  for(i=0;i<2000;i++)
  {
    for(j=0;j<2000;j++)
    {
      keyWord[i][j] = '\0';
      definitions[i][j] = '\0';
      tempArr[i][j] = '\0';
      whiteSpace[i][j] = '\0';
      funcArr[i][j] = '\0';
    }
  }

  if(!codeFile)
  {
    printf("no such file\n");
    return 0;
  }
  /*parsing the file*/
  while((c = getc(codeFile)) != EOF)
  {
    /*checking for whitespace*/
    if(c==' '||c=='\n'||c=='\t'||c=='\r')
    {
      whiteSpace[wordCount][charCountw] = c;
      if(tempc==' '||tempc=='\n'||tempc=='\t'||tempc=='\r')
      {
        charCountw++;
      }
      else
      {
        charCountw = 0;
        wordCount++;
      }
      charCount = 0;
    }
    /*checking for strings*/
    else if(c=='\"')
    {
      charCount = 0;
      keyWord[wordCount][charCount] = c;
      charCount++;
      c = getc(codeFile);
      while(c != '\"' && tempc != '\n')
      {
        keyWord[wordCount][charCount] = c;
        charCount++;
        charCountw = 0;
        tempc = c;
        c = getc(codeFile);
        if(tempc=='\\' && c=='\"')
        {
          keyWord[wordCount][charCount] = c;
          charCount++;
          charCountw = 0;
          tempc = c;
          c = getc(codeFile);
          continue;
        }
      }
      keyWord[wordCount][charCount] = c;
      charCount = 0;
      charCountw = 0;
      tempc = c;
      wordCount++;
    }
    /*checking for block comments*/
    else if(c=='*')
    {
      if(tempc=='/')
      {
        while(c!= '/' || tempc!='*')
        {
          keyWord[wordCount][charCount] = c;
          charCount++;
          charCountw = 0;
          tempc = c;
          c = getc(codeFile);
        }
        keyWord[wordCount][charCount] = c;
        charCount = 0;
        charCountw = 0;
        tempc = c;
        wordCount++;
      }
      else
      {
        keyWord[wordCount][charCount] = c;
        charCount++;
        charCountw = 0;
      }
    }
    /*checking for #*/
    else if(c=='#')
    {
      while(c!='\n')
      {
        keyWord[wordCount][charCount] = c;
        charCount++;
        charCountw = 0;
        tempc = c;
        c = getc(codeFile);
      }
      whiteSpace[wordCount][charCountw] = c;
      charCount = 0;
      charCountw = 0;
      tempc = c;
      wordCount++;
    }
    /*checking for single line comments*/
    else if(c=='/')
    {
      if(tempc=='/')
      {
        while(c!='\n')
        {
          keyWord[wordCount][charCount] = c;
          charCount++;
          charCountw = 0;
          tempc = c;
          c = getc(codeFile);
        }
        keyWord[wordCount][charCount] = c;
        charCount = 0;
        charCountw = 0;
        tempc = c;
        wordCount++;
      }
      else
      {
        keyWord[wordCount][charCount] = c;
        charCount++;
        charCountw = 0;
      }
    }

    else if(c=='('||c==')'||c=='{'||c=='}'||c==';'||c=='.'||c=='='||c==','||c=='+'||c=='*')
    {
      if((tempc!=' ')&&(tempc!='\n')&&(tempc!='\t')&&(tempc!='\r'))
      {
        wordCount++;
        charCount = 0;
      }
      keyWord[wordCount][charCount] = c;
      wordCount++;
      charCount = 0;
      charCountw = 0;
    }
    else
    {
      keyWord[wordCount][charCount] = c;
      charCount++;
      charCountw = 0;
    }
    tempc = c;
  }

  for(i=0;i<wordCount;i++)
  {
    classFunc(keyWord,whiteSpace,definitions,tempArr,i,wordCount,funcArr);
  }

  for (j = 0; j < 2000; j++)
  {
    fprintf(outFile,"%s",keyWord[j]);
    fprintf(outFile,"%s",whiteSpace[j]);
    /*this for loop is a test to be deleted at the end````````~~~~~~~~~~~~~*/
  }

/*freeing everything*/
  for(i=0;i<2000;i++)
  {
    free(keyWord[i]);
    free(definitions[i]);
    free(tempArr[i]);
    free(funcArr[i]);
  }
  free(keyWord);
  free(definitions);
  free(tempArr);
  free(funcArr);
  for(i=0;i<2000;i++)
  {
    free(whiteSpace[i]);
  }
  free(whiteSpace);
  fclose(codeFile);
  fclose(outFile);
  return 0;
}
