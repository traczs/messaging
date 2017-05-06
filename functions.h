#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

/**
* classFunc
* searches through each class, renames it into struct and calls on other functions
* return: void
*/
void classFunc(char**keyWord,char**whiteSpace,char**definitions,char**tempArr,int i,int wordCount,char**funcArr);
/**
* varCheck
* recursively goes through each class and copies relevant keywords to another 2d arrray
* return: void
*/
void varCheck(int i,char** keyWord,char**definitions,char *className,char**whiteSpace);

/**
* nameChange
* goes through the class and changes the names of the functions to handle method overloading
* return: void
*/
void nameChange(char** keyWord,char**definitions,char*className,int end,int i,char** whiteSpace,char**funcArr);
/**
* funcOut
* goes through the file and brings out all the functions out of the class
* return:void
*/
void funcOut(char ** keyWord,char **tempArr,char** whiteSpace,int end,int i,int wordCount);

/**
* makeConst
* creates constructors
* return: void
*/
void makeConst(char*className,char**keyWord,char**funcArr,int i);
/*void putVar(int i,char** keyWord,char**whiteSpace,char**funcArr);*/

#endif
