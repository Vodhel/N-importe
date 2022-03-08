#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile_char.h"

int estPileVide ( Pile p ){
	return p==NULL;
}

void empile ( Pile * p , char* data ){
	Elem_pile* new = malloc(sizeof(Elem_pile));
	new->data=data;
	new->precedent=*p;

	*p=new;
}

char* depile ( Pile * p ){

	if(estPileVide(*p)){
		return "-1";
	}

	Elem_pile* temp = *p;
	char* donnee=malloc(sizeof(temp->data)); 
	strcpy(donnee,temp->data);
	*p=(*p)->precedent;
	free(temp);
	return donnee;
}

char* tetePile ( Pile p ){
	if(p==NULL){
		return "-1";
	}

	return p->data;
}

void affichePile ( Pile  p ){
	while(p!=NULL){
		printf("%s\n", p->data);
		p=p->precedent;
	}
}

void freePile( Pile p){
	while(p!=NULL){
		Elem_pile* temp=p;
		p=p->precedent;
		free(temp);
	}
}