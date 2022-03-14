#include "schedule.h"
#include "experiment.h"

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

void completeSchedule(char * filename) 
{
	struct_t* Elem;
	QueueS* fileTemp = creerFileStruct();
	QueueS* file = scheduleStart(filename);
	
	afficheFileStruct(*file, afficheExperiment); 
  
	Elem = defileStruct(file);
	printf("début %s", Elem->name); 
	enfileStruct(fileTemp, Elem);		//On initialise fileTemp et affiche le premier message de début
	
	while (file != NULL)			//Tant que file n'est pas vide
	{
		
		if(fileTemp->debut->data->time + 90 > file->debut->data->time) //Si l'élément de file commence avant que ne termine celui de file temp...
		{
			Elem = defileStruct(file);			//On affiche son début et l'enfile à fileTemp
			enfileStruct(fileTemp, Elem);
		}
		else							//Sinon...
		{
			Elem = defileStruct(fileTemp);			//On defile fileTemp, on affiche la fin de cet element et on defile
			printf("fin %s", Elem->name);			//l'element de file pour l'enfiler a file temp
			Elem = defileStruct(file);
			enfileStruct(fileTemp, Elem);
		}		
	}
	while(fileTemp)							//Enfin une fois file vidé, on vide fileTemp en affichant toute les fins
	{
		Elem = defileStruct(fileTemp);
		printf("fin %s", Elem->name);
	}
	
	free(Elem);
	
}

