#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pile_char.h"
#include "file_struct.h"
#include "experiment.h"
#include "xmlReader.h"
#include "schedule.h"

void checkXML(char* filename)
{
}
void drawGraph(char* filename,FILE* out) {
}


void usage()
{
  printf("USAGE : ./xmlChercher filename.xml\n");
}

int main(int argc, char * argv[])
{
  if(argc <= 1)
    {
      usage();
      return EXIT_FAILURE;
    }
 
  fonctionXML(argv[1]);
  //Exercice 3: Question3 : affiche les balises uniquement
  
  //checkXML(argv[1]);
  //completeSchedule(argv[1]);
  //drawGraph(argv[1],stdout);
  return EXIT_SUCCESS;
}
