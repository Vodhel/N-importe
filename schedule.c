#include "schedule.h"

QueueS* scheduleStart(char* filename)
{
  xmlFile_t * xmlFile = openXML(filename);
  char * s, *tag;
  int prev_state = IDLE;
  experiment_t* exp;
  QueueS *q = creerFileStruct();
  while ((s = nextString(xmlFile))!= NULL )
    {
      if(prev_state == DEBUT)
	{
	  exp->time = atoi(s);
	  prev_state = IDLE;
	}
      else{
	if(prev_state == NOM)
	  {
	    strcpy(exp->name,s);
	    prev_state = IDLE;     
	  }
      }
      if(isTag(s))
	{
	  tag = tagName(s);
	  if(isOpeningTag(s) && !strcmp(tag,"experience"))
	    exp = malloc(sizeof(experiment_t));
	  else{
	    if(isOpeningTag(s) && !strcmp(tag,"debut")) 
	      prev_state = DEBUT;
	    if(isOpeningTag(s) && !strcmp(tag,"nom")) 
	      prev_state = NOM;
	    if(isClosingTag(s) && !strcmp(tag,"experience"))
	      {
		enfileStruct(q,exp);
		free(exp);
	      }
	  }
	  free(tag);
	}
    }
  closeXML(xmlFile);
  return q;
}


