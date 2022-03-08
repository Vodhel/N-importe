#pragma once

#include <stdio.h>


#define BUF_SIZE 2048

typedef struct {
  FILE *fp;
  char word[BUF_SIZE];
  char buf[BUF_SIZE];
  char eof;
} xmlFile_t; 

xmlFile_t * openXML(char * filename);
void closeXML(xmlFile_t * xmlFile);
char * nextString(xmlFile_t * xmlFile);
int isTag(char * s);
int isClosingTag(char * s);
int isOpeningTag(char * s);
void fonctionXML(char* filename);
// to be freed externaly
char * tagName(char * tag);
