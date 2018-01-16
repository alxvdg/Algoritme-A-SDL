/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#ifndef mapile.h
#define mapile.h

#include "plannificationAlgo.h"
/**************** DEFINITION DE NOS STRUCTURES ************************/
/* Ici on définit les deux structures nécessaires à la création de notre pile
    Pour faire simple on gère seulement l'élément de "tête" de la pile et
    cela fonctionne selon la règle : dernier arrivé premier traité (car en haut de la
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
    Permet d'ajouter un élément en haut de la pile
    @param *pile : adresse du premier élément de pile
    @param n : Noeud à ajouter à la pile
*/
void empiler(Pile *pile, Noeud n);


/**
    Permet d'ajouter un élément en fin de la pile
    @param *pile : adresse du premier élément de pile
    @param n : Noeud à ajouter à la pile
    Rq : fonctionnement non testé
*/
void enfiler(Pile *pile, Noeud n);


/**
    Permet d'enlever un élément en fin de pile
    @param *pile : adresse du premier élément de pile
    @return n : dernier noeud de la pile
*/
Noeud defiler(Pile *pile);


/**
    Permet d'enlever un élément en haut de la pile
    @param *pile : adresse du premier élément de pile
    @return n : premier noeud de la pile
*/
Noeud depiler(Pile *pile);


/**
    Permet de supprimer la pile
    @param *pile : adresse du premier élément de pile
*/
void clearPile(Pile *pile);


/**
    Vérifie si un noeud n est dans la pile
    @param *pile : adresse du premier élément de pile
    @param n : Noeud à vérifier dans la pile
*/
int estDansPile(Noeud n,Pile *pile);


/**
    Permet d'effectuer un tri fusion sur notre pile de noeud selon l'heuristique de chaque noeud
    fonction appelée récursivement

    @param *pile : adresse du premier élément de pile
    @param nb : taille de la pile
*/
void triFusion(Pile *pile,int nb);


/**
    Permet de fusionner deux piles en une seule selon le principe d'interclassement(dans l'ordre)
    On a deux piles : on compare les heuristiques de chaque noeuds en tete de celles-ci et on place le
    noeud avec l'heuristique la plus grande en premier puis l'autre
    Permet de trier par ordre croissant les noeuds selon leurs heuristiques
    fonction appelée récursivement

    @param *fusion : adresse du premier élément de pile fusion
    @param *pile1 : adresse du premier élément de pile1 à fusionner
    @param *pile2 : adresse du premier élément de pile2 ) fusionner
*/
void fusionPile(Pile* fusion, Pile *pile1, Pile *pile2);


/**
    Vérifie si un noeud au cout plus bas que n est dans la pile
    @param *pile : adresse du premier élément de pile
    @param n : Noeud à vérifier dans la pile
    @return : 1 s'il n'y a pas de noeud n avec un cout inférieur 0 sinon
*/
int estDansPileCout(Noeud n,Pile *pile);


/**
    Renvoit le nombre de noeuds dans une pile de noeuds
    @param *pile : adresse du premier élément de pile
    @return : le nombre de noeud dans la pile
*/
int countPile(Pile *pile);


/**
    Affiche les éléments de la pile sur la console
    @param *pile : adresse du premier élément de pile
*/
void afficherPile(Pile *pile);


/********************************************************************/

#endif
