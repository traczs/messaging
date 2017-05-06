#ifndef __POST_H__
#define __POST_H__
/**
* struct
**/
struct userPost
{
  char *username;
  char *streamname;
  char *date;
  char *text;
};

void updateStream(struct userPost *st);
void addUser(char *username, char *list);
void removeUser(char *username, char *list);

#endif
