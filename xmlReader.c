#include <string.h>
#include <stdlib.h>
#include "xmlReader.h"
xmlFile_t * openXML(char * filename)
{
  FILE *fp;
  xmlFile_t * xmlFile = malloc(sizeof(xmlFile_t));
  fp = fopen(filename, "r");

  if (fp == NULL) 
    {
      printf("Impossible d'ouvrir le fichier %s", filename);
      return NULL;
    }
  xmlFile->fp = fp;
  xmlFile->word[0] = '\0'; 
  xmlFile->eof = 0;
  return xmlFile;
}

void closeXML(xmlFile_t * xmlFile)
{
  fclose(xmlFile->fp);
  free(xmlFile);
}

char * nextString(xmlFile_t * xmlFile)
{
  char c;
  
  if(xmlFile->eof)
    {
      return NULL;
    }
  c = fgetc(xmlFile->fp);
  while( c != EOF && c != '>' && c!='<')  
    {
      strncat(xmlFile->word,&c,1);
      c = fgetc(xmlFile->fp); 
    }
  switch (c) {
  case '<' :
    strcpy(xmlFile->buf,xmlFile->word);
    strcpy(xmlFile->word,"<");
    break;
  case '>' :
    strncat(xmlFile->word,&c,1);
    strcpy(xmlFile->buf,xmlFile->word);
    xmlFile->word[0] = '\0';
    break;
  case EOF:
    strcpy(xmlFile->buf,xmlFile->word);
    xmlFile->eof = 1;
    break;
  default:
    printf("Can't happen ! ");
  }
  return xmlFile->buf;
}

int isTag(char * s)
{
  return s[0] == '<';
}

int isClosingTag(char * s)
{
  return (s[0] == '<') && (s[1] ==  '/');
}

int isOpeningTag(char * s)
{
  return isTag(s) && ! isClosingTag(s);
}

// to be freed externaly
char * tagName(char * tag)
{
  char * new_s;
  int start = isClosingTag(tag)?2:1;
  char* pos_sp = strchr(tag,' ');
  char* pos_gt = strchr(tag,'>');
  char* end    = (pos_sp==NULL)? pos_gt: pos_sp;
  size_t t = end - tag;
  new_s = malloc((t-start +1) * sizeof(char));
  char* i;
  int j=0;
  for(i = tag+ start; i !=end; i++)
    {
      new_s[j++]=*i;
    }
  new_s[j]='\0';
  return new_s;
}

void fonctionXML(char* filename)
{
  xmlFile_t * xmlFile = openXML(filename);
  char *s;
  int indent = 0;
  int i;
  while ((s = nextString(xmlFile)) != NULL)
    {
      if(isTag(s))
	{
	  if(isClosingTag(s))
	    indent--;
	  for(i = 0; i< indent; i++)
	    printf(" ");
	  printf("%s\n",s);
	  if(isOpeningTag(s))
	    indent++;
	}
    }
  closeXML(xmlFile);

}
