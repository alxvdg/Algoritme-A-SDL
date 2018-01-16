/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#ifndef mouvement.h
#define mouvement.h


#include "plannification.h"

/**************** PROTOTYPES DE NOS FONCTIONS ************************/
/**
    Fonction simulant le d�placement sur une grille

    Pour l'impl�matation r�el, les fonctions bas-niveau de d�placements du robot
    devront �tre ajouter dans ces fonctions (ou celles ci devront �tre r� �crites)

**/

/** Fonction mouvement monter
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est d�plac�e
*/
void goToTop(Cell *c);


/**  Fonction mouvement aller � droite
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est d�plac�e
*/
void goToRight(Cell *c);


/**   Fonction mouvement aller � gauche
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est d�plac�e
*/
void goToLeft(Cell *c);


/**  Fonction mouvement descendre
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est d�plac�e
*/
void goToBottom(Cell *c);



#endif
