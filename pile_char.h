# ifndef PILE_H
# define PILE_H

typedef struct e_pile
{
  char * data ;
  struct e_pile * precedent ;
} Elem_pile ;

/* Une pile est un pointeur vers son premier element*/
typedef Elem_pile * Pile ;

/* Teste si la pile est vide */
int estPileVide ( Pile p ) ;

/* Ajoute l'element donn' en tete de la pile */

void empile ( Pile * p , char* data ) ;

/* Supprime le premier element de la pile et retourne sa valeur -1 si
   la pile est vide */
char* depile ( Pile * p ) ;

/* Retourne la valeur du premier element de la pile sans le supprimer
retourne -1 si la pile est vide */
char* tetePile ( Pile p ) ;

/* Affiche la pile en entier pour les tests*/
void affichePile ( Pile  p ) ;

/* Libère la mémoire */
void freePile( Pile p);

# endif
