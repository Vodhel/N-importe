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
        empile(&p,tag);         //on empile seulement les balises ouvrantes
      }

      if(isClosingTag(s)){
        if(estPileVide(p)){
          printf("Pas de balise ouvrante pour %s\n",s);   //Si on rencontre une balise fermante et que la pile est vide alors il manque une balise ouvrante
          closeXML(xmlFile);
          return;

        }else{
          char *temp=depile(&p);

          if(strcmp(tagName(s),tagName(temp))){   //Sinon on verifie que la balise fermante correspond bien à la balise ouvrante en tete de pile
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

  if(!estPileVide(p)){  //Si apres le parcours du fichiers xml, dans la pile il reste des balises ouvrantes alors il manque des balises fermantes
    printf("Pas de balise fermante pour %s\n", tetePile(p));
  }else{
    printf("Pas d'erreur\n"); //Sinon aucune erreur
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

        noeud++; //donne le id du noeud correspondant

        fprintf(out,"\t %d [label=\"%s\"];\n", noeud, tagName(s)); //print la declaration d'un sommet

        if(!estPileVide(p)){
          fprintf(out,"\t %d -> %d\n", tetePile2(p), noeud);  //si la pile n'est pas vide alors le noeud à un père
                                                              //on print alors l'arc correspondant
        }

        tag=malloc(sizeof(s));
        strcpy(tag,s);
        empile2(&p,tag,noeud);  //on empile tous les balises ouvrantes et leurs id
                                //empile2 ajoute en tete de pile la balise et le id du noeud

      }

      if(isClosingTag(s)){  //on depile tous les balises qui ont ete refermées
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
