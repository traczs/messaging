#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


void classFunc(char**keyWord,char**whiteSpace,char**definitions,char**tempArr,int i,int wordCount,char**funcArr)
{
  char className[50];
  int end;
  if(strcmp(keyWord[i],"class")==0)
  {
    strcpy(keyWord[i],"struct");
    strcpy(definitions[i],keyWord[i]);
    strcpy(funcArr[i],keyWord[i]);

    i++;
    strcpy(definitions[i],keyWord[i]);
    strcpy(className,keyWord[i]);
    strcpy(funcArr[i],className);

    i++;
    int temp = i;
    if(strcmp(keyWord[i],"{")==0)
    {

      int leftBracket = 1;
      while(leftBracket != 0)
      {
        i++;
        if(strcmp(keyWord[i],"{") == 0)
        {
          leftBracket++;
        }
        if(strcmp(keyWord[i],"}") == 0)
        {
          leftBracket--;
        }
      }
      i = i+2;
      keyWord[i][0]=';';
      end = i;
      i= temp;
      i= i+2;
      varCheck(i,keyWord,definitions,className,whiteSpace);
      nameChange(keyWord,definitions,className,end,i,whiteSpace,funcArr);
      funcOut(keyWord,tempArr,whiteSpace,end,i,wordCount);
    }
    else
    {
      /* class A myA; store the myA? or leave it?*/
      makeConst(className,keyWord,funcArr,i);
    }

  }
}
/*void putVar(int i,char** keyWord,char**whiteSpace,char**funcArr)
{
  while(strcmp(keyWord[i],",")!=0 && strcmp(keyWord[i],";")!=0 && strcmp(keyWord[i],"(")!=0)
  {
    i++;
  }
  if(strcmp(keyWord[i],";")==0)
  {
    i--;
    strcpy(funcArr[i],keyWord[i]);
    i++;

  }
  else if(strcmp(keyWord[i],",")==0)
  {
    i--;
    strcpy(funcArr[i],keyWord[i]);
    i=i+2;
    putVar(i,keyWord,whiteSpace,funcArr);
  }
}*/
void varCheck(int i,char** keyWord,char**definitions,char *className,char**whiteSpace)
{
  if((strcmp(keyWord[i],"int")==0)||(strcmp(keyWord[i],"float")==0)||(strcmp(keyWord[i],"double")==0)||(strcmp(keyWord[i],"long")==0)||(strcmp(keyWord[i],"char")==0)||(strcmp(keyWord[i],"short")==0)||(strcmp(keyWord[i],"void")==0)||(strcmp(keyWord[i],"signed")==0)||(strcmp(keyWord[i],"unsigned")==0))
  {
    strcpy(definitions[i],keyWord[i]);
    i++;
    /*putVar(i,keyWord,whiteSpace,funcArr);*/
    varCheck(i,keyWord,definitions,className,whiteSpace);
  }
  else
  {
    if(strcmp(keyWord[i],"(")==0)
    {
      while(strcmp(keyWord[i],")")!=0)
      {
        strcpy(definitions[i],keyWord[i]);
        i++;
      }
      strcpy(definitions[i],keyWord[i]);
      i++;
      varCheck(i,keyWord,definitions,className,whiteSpace);
    }
    else if(strcmp(keyWord[i],";")==0)
    {
      strcpy(definitions[i],keyWord[i]);
      i++;
      varCheck(i,keyWord,definitions,className,whiteSpace);
    }
    else if(strcmp(keyWord[i]," ")==0)
    {
      i++;
      varCheck(i,keyWord,definitions,className,whiteSpace);
    }
    else if(strcmp(keyWord[i],"{")==0)
    {
      while(strcmp(keyWord[i],"}")!=0)
      {
        strcpy(definitions[i],keyWord[i]);

        i++;
      }
      strcpy(definitions[i],keyWord[i]);

      i++;
      varCheck(i,keyWord,definitions,className,whiteSpace);
    }
    else if((strcmp(keyWord[i],"}")==0)&&(strcmp(keyWord[i+2],";")==0))
    {
      printf("STOP");
    }
    else
    {
      strcpy(definitions[i],keyWord[i]);
      i++;
      varCheck(i,keyWord,definitions,className,whiteSpace);
    }
  }
}

void nameChange(char** keyWord,char**definitions,char*className,int end,int i,char**whiteSpace,char**funcArr)
{
  int location;
  char name[50];
  strcpy(name,className);
  while(end>i)
  {
    while((strcmp(definitions[i],"int")!=0)&&(strcmp(definitions[i],"float")!=0)&&(strcmp(definitions[i],"double")!=0)&&(strcmp(definitions[i],"long")!=0)&&(strcmp(definitions[i],"char")!=0)&&(strcmp(definitions[i],"short")!=0)&&(strcmp(definitions[i],"void")!=0)&&(strcmp(definitions[i],"unsigned")!=0)&&(strcmp(definitions[i],"signed")!=0)&&(end>i))
    {
      i++;
    }
    int place = i;
    while(strcmp(definitions[i],"(")!=0&&strcmp(definitions[i],",")!=0&&(strcmp(whiteSpace[i],"\n")!=0))
    {
      i--;
    }
    if(strcmp(definitions[i],"(")==0||strcmp(definitions[i],",")==0)
    {
      while((strcmp(definitions[i],")")!=0)&&(end>i))
      {
          if((strcmp(definitions[i],"int")==0)||(strcmp(definitions[i],"float")==0)||(strcmp(definitions[i],"double")==0)||(strcmp(definitions[i],"long")==0)||(strcmp(definitions[i],"char")==0)||(strcmp(definitions[i],"short")==0)||(strcmp(definitions[i],"void")==0)||(strcmp(definitions[i],"signed")==0)||(strcmp(definitions[i],"unsigned")==0))
          {
            char temp[3];
            temp[0] = definitions[i][0];
            temp[1] = '\0';
            strcat(definitions[location],temp);

          }
          i++;
      }
      i++;
    }
    else
    {
      i=place;
    }
    while((strcmp(definitions[i],"(")!=0)&&(strcmp(definitions[i],";")!=0)&&(end>i))
    {
      i++;
    }
    if(strcmp(definitions[i],";")==0)
    {
      continue;
    }
    else if (strcmp(definitions[i],"(")==0)
    {
      i--;
      if(strcmp(definitions[i],"printf")!=0&&strcmp(definitions[i],"scanf")!=0&&strcmp(definitions[i],"fprintf")!=0&&strcmp(definitions[i],"fscanf")!=0&&strcmp(definitions[i],"return")!=0&&strcmp(definitions[i],"getchar")!=0)
      {
        location = i;
        strcat(className,definitions[i]);
        strcpy(definitions[i],className);
      }
      /*while(strcmp(definitions[i],"\0")!=0)
      {
        i++;
      }*/
      i++;;
    }
    strcpy(keyWord[location],definitions[location]);
    strcpy(funcArr[location],definitions[location]);
    strcpy(className,name);
  }
}

void funcOut(char ** keyWord,char **tempArr,char**whiteSpace,int end,int i,int wordCount)
{
  int start;
  while(end>i)
  {
    while((strcmp(keyWord[i],"int")!=0)&&(strcmp(keyWord[i],"float")!=0)&&(strcmp(keyWord[i],"double")!=0)&&(strcmp(keyWord[i],"long")!=0)&&(strcmp(keyWord[i],"char")!=0)&&(strcmp(keyWord[i],"short")!=0)&&(strcmp(keyWord[i],"void")!=0)&&(strcmp(keyWord[i],"unsigned")!=0)&&(strcmp(keyWord[i],"signed")!=0)&&(end>i))
    {
      i++;
    }
    start = i;
    while((strcmp(keyWord[i],"(")!=0)&&(strcmp(keyWord[i],";")!=0)&&(end>i))
    {
      i++;
    }
    if(strcmp(keyWord[i],";")==0)
    {
      continue;
    }
    else if (strcmp(keyWord[i],"(")==0)
    {
      int bracket = i;
      i = start;
      int j = 0;
      /*while(strcmp(keyWord[i],"{")==0)
      {
        strcpy(tempArr[j],keyWord[i]);
        i++;
      }*/
      int leftBracket = 1;
      while(leftBracket != 0)
      {
        if (strcmp(keyWord[i],"{")==0)
        {
          leftBracket++;
        }
        if (strcmp(keyWord[i],"}")==0)
        {
          leftBracket--;
        }
        strcpy(tempArr[i],keyWord[i]);
        i++;
        j++;
      }
      i--;
      strcpy(tempArr[i],"\0");
      i++;
      char* func;
      func = malloc(sizeof(char)*50);
      int q;
      for(q=0;q<50;q++)
      {
        func[q] = '\0';
      }
      func[0] = '*';
      strcat(func,keyWord[bracket-1]);
      strcpy(keyWord[bracket-1],keyWord[bracket]);
      strcpy(keyWord[bracket],func);
      free(func);
      bracket++;
      while(strcmp(keyWord[bracket],")")!=0)
      {
        strcpy(keyWord[bracket]," ");
        bracket++;
      }
      bracket= bracket+2;
      strcpy(keyWord[bracket],"();");
      leftBracket = 1;
      bracket++;
      int marker = 0;
      while(leftBracket != 0)
      {
        if (strcmp(keyWord[bracket],"{")==0)
        {
          leftBracket++;
        }
        if (strcmp(keyWord[bracket],"}")==0)
        {
          leftBracket--;
        }
        strcpy(keyWord[bracket]," ");
        bracket++;
        marker++;
      }
      for(j=wordCount+1;j<2000;j++)
      {
        strcpy(keyWord[j],tempArr[j - wordCount]);
        strcat(keyWord[j],whiteSpace[j - wordCount]);
      }
      i= bracket;
    }
    i++;
  }
}

void makeConst(char*className,char**keyWord,char**funcArr,int i)
{
  char name[50] = " ";
  strcpy(name,keyWord[i]);
  while(strcmp(keyWord[i],";")!=0)
  {
    i++;
  }
  strcat(keyWord[i]," \nconstructor");
  strcat(keyWord[i],className);
  strcat(keyWord[i],"(&");
  strcat(keyWord[i],name);
  strcat(keyWord[i],");");
  i=1999;
  while(strcmp(keyWord[i],"\0")==0)
  {
    i--;
  }
  i++;
  strcpy(keyWord[i],"void constructor");
  strcat(keyWord[i],className);
  strcat(keyWord[i],"(struct ");
  strcat(keyWord[i],className);
  strcat(keyWord[i]," * tempStr) {\n");
  i++;
  int j;
  for(j=0;j<2000;j++)
  {
    if(strcmp(funcArr[j],className)==0)
    {
      break;
    }
  }
  j++;
  while(strcmp(funcArr[j],"struct")!=0&&(j<2000))
  {
    if(strcmp(funcArr[j],"\0")==0)
    {
      j++;
    }
    else
    {
      strcpy(keyWord[i],"tempStr");
      strcat(keyWord[i],"->");
      strcat(keyWord[i],funcArr[j]);
      strcat(keyWord[i], " = ");
      strcat(keyWord[i],funcArr[j]);
      strcat(keyWord[i],";\n");
      j++;
      i++;
    }
  }
  strcat(keyWord[i],"}\n");
  for (j = 0; j < 2000; j++) {
    if(strcmp(keyWord[j],name)==0&&strcmp(keyWord[j+1],".")==0)
    {
      j=j+2;
      int k = 0;
      while(strcmp(funcArr[k],className)!=0&&(k<2000))
      {
        k++;
      }
      while(strstr(funcArr[k],keyWord[j])==NULL&&(k<2000))
      {
        k++;
      }
      strcpy(keyWord[j],funcArr[k]);
    }
  }
}
