#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_struct.h"
#include "experiment.h"
#include "xmlReader.h"
#include "schedule.h"
#include "pile_char.h"

void checkXML(char* filename){

  xmlFile_t* xmlFile = openXML(filename);
  char* s;
  char* tag;
  Pile p=NULL;

  while((s=nextString(xmlFile))!=NULL){

    if(isTag(s)){
      if(isOpeningTag(s)){
        tag=malloc(sizeof(s));
        strcpy(tag,s);
        empile(&p,tag);
      }

      if(isClosingTag(s)){
        if(estPileVide(p)){
          printf("Pas de balise ouvrante pour %s\n",s);
          closeXML(xmlFile);
          return;

        }else{
          char *temp=depile(&p);

          if(strcmp(tagName(s),tagName(temp))){
            printf("balise %s lu, mais </%s> attendu\n", s, tagName(temp));
            free(tag);
            free(temp);
            closeXML(xmlFile);
            return;
          }
          free(temp);
        }
      }
    }
  }

  if(!estPileVide(p)){
    printf("Pas de balise fermante pour %s\n", tetePile(p));
  }else{
    printf("Pas d'erreur\n");
  }

  free(tag);
  freePile(p);
  closeXML(xmlFile);
}



void drawGraph(char* filename,FILE* out) {

  xmlFile_t* xmlFile = openXML(filename);
  char* s;
  char* tag;
  int noeud=-1;
  Pile p=NULL;

  fprintf(out,"digraph {\n");

  while((s=nextString(xmlFile))!=NULL){

    if(isTag(s)){

      if(isOpeningTag(s)){

        noeud++;

        fprintf(out,"\t %d [label=\"%s\"];\n", noeud, tagName(s));

        if(!estPileVide(p)){
          fprintf(out,"\t %d -> %d\n", tetePile2(p), noeud);
        }

        tag=malloc(sizeof(s));
        strcpy(tag,s);
        empile2(&p,tag,noeud);

      }

      if(isClosingTag(s)){
        depile(&p);
      }
    }
  }

  fprintf(out, "}");
  free(tag);
  closeXML(xmlFile);
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
 
  //fonctionXML(argv[1]);
  //Exercice 3: Question3 : affiche les balises du fichier xml uniquement

  //checkXML(argv[1]);
  //completeSchedule(argv[1]);


  FILE* stdout=fopen("experience.dot","r+");
  drawGraph(argv[1],stdout);
  fclose(stdout);

  //Exo6:
  //Commande tape : ./xmlChecker fichiers_xml/petit.xml | dot -Tpdf > petit.pdf petit.dot

  return EXIT_SUCCESS;
}
