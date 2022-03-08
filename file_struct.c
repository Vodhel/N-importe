#include <stdio.h>
#include <stdlib.h>
#include "file_struct.h"
#include "experiment.h"

QueueS * creerFileStruct(){

	QueueS* q=malloc(sizeof(QueueS));
	q->debut = NULL;
	q->fin = NULL;
	return q;
}

int estFileStructVide ( QueueS p ){

	return (p.debut == NULL);
}

void enfileStruct ( QueueS * p , struct_t* data ){

	Elem_FileStruct* temp = malloc(sizeof(Elem_FileStruct));
	temp->data = data;
	temp->precedent = NULL;

	if(estFileStructVide(*p)){
		p->debut=temp;
	}else{
		p->fin->precedent = temp;
	}

	p->fin = temp;
}

struct_t* defileStruct ( QueueS * p ){

	if(estFileStructVide(*p)){
		return NULL;
	}else{
		Elem_FileStruct* temp = p->debut->precedent;
		struct_t* donnee = malloc(sizeof(struct_t));
		*donnee=*(p->debut->data);
		free(p->debut);
		p->debut=temp;
		return donnee;
	}
}

struct_t teteFileStruct ( QueueS p ){
		return *(p.debut->data);
}

void afficheFileStruct ( QueueS p , void (*f)(struct_t*) ){
	while(p.debut != NULL){
		f(p.debut->data);
		p.debut=p.debut->precedent;
	}
}

void freeFileStruct( QueueS *p ){

	Elem_FileStruct* maillon = p->debut;
	
	while( maillon != NULL){
		p->debut=p->debut->precedent;
		//free(maillon->data);//question
		free(maillon);
		maillon = p->debut;
	}
	free(p);
}