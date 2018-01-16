/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#ifndef mapile.h
#define mapile.h

#include "plannificationAlgo.h"
/**************** DEFINITION DE NOS STRUCTURES ************************/
/* Ici on d�finit les deux structures n�cessaires � la cr�ation de notre pile
    Pour faire simple on g�re seulement l'�l�ment de "t�te" de la pile et
    cela fonctionne selon la r�gle : dernier arriv� premier trait� (car en haut de la
                                                                                pile)
*/
typedef struct Element Element;
struct Element
{
    Noeud n;
    Element *suivant;
};

typedef struct {
    Element *premier;
}Pile;

/********************************************************************/



/**************** PROTOTYPES FONCTIONS ************************/

/**
    Permet d'ajouter un �l�ment en haut de la pile
    @param *pile : adresse du premier �l�ment de pile
    @param n : Noeud � ajouter � la pile
*/
void empiler(Pile *pile, Noeud n);


/**
    Permet d'ajouter un �l�ment en fin de la pile
    @param *pile : adresse du premier �l�ment de pile
    @param n : Noeud � ajouter � la pile
    Rq : fonctionnement non test�
*/
void enfiler(Pile *pile, Noeud n);


/**
    Permet d'enlever un �l�ment en fin de pile
    @param *pile : adresse du premier �l�ment de pile
    @return n : dernier noeud de la pile
*/
Noeud defiler(Pile *pile);


/**
    Permet d'enlever un �l�ment en haut de la pile
    @param *pile : adresse du premier �l�ment de pile
    @return n : premier noeud de la pile
*/
Noeud depiler(Pile *pile);


/**
    Permet de supprimer la pile
    @param *pile : adresse du premier �l�ment de pile
*/
void clearPile(Pile *pile);


/**
    V�rifie si un noeud n est dans la pile
    @param *pile : adresse du premier �l�ment de pile
    @param n : Noeud � v�rifier dans la pile
*/
int estDansPile(Noeud n,Pile *pile);


/**
    Permet d'effectuer un tri fusion sur notre pile de noeud selon l'heuristique de chaque noeud
    fonction appel�e r�cursivement

    @param *pile : adresse du premier �l�ment de pile
    @param nb : taille de la pile
*/
void triFusion(Pile *pile,int nb);


/**
    Permet de fusionner deux piles en une seule selon le principe d'interclassement(dans l'ordre)
    On a deux piles : on compare les heuristiques de chaque noeuds en tete de celles-ci et on place le
    noeud avec l'heuristique la plus grande en premier puis l'autre
    Permet de trier par ordre croissant les noeuds selon leurs heuristiques
    fonction appel�e r�cursivement

    @param *fusion : adresse du premier �l�ment de pile fusion
    @param *pile1 : adresse du premier �l�ment de pile1 � fusionner
    @param *pile2 : adresse du premier �l�ment de pile2 ) fusionner
*/
void fusionPile(Pile* fusion, Pile *pile1, Pile *pile2);


/**
    V�rifie si un noeud au cout plus bas que n est dans la pile
    @param *pile : adresse du premier �l�ment de pile
    @param n : Noeud � v�rifier dans la pile
    @return : 1 s'il n'y a pas de noeud n avec un cout inf�rieur 0 sinon
*/
int estDansPileCout(Noeud n,Pile *pile);


/**
    Renvoit le nombre de noeuds dans une pile de noeuds
    @param *pile : adresse du premier �l�ment de pile
    @return : le nombre de noeud dans la pile
*/
int countPile(Pile *pile);


/**
    Affiche les �l�ments de la pile sur la console
    @param *pile : adresse du premier �l�ment de pile
*/
void afficherPile(Pile *pile);


/********************************************************************/

#endif
