/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#ifndef mouvement.h
#define mouvement.h


#include "plannification.h"

/**************** PROTOTYPES DE NOS FONCTIONS ************************/
/**
    Fonction simulant le déplacement sur une grille

    Pour l'implématation réel, les fonctions bas-niveau de déplacements du robot
    devront être ajouter dans ces fonctions (ou celles ci devront être ré écrites)

**/

/** Fonction mouvement monter
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est déplacée
*/
void goToTop(Cell *c);


/**  Fonction mouvement aller à droite
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est déplacée
*/
void goToRight(Cell *c);


/**   Fonction mouvement aller à gauche
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est déplacée
*/
void goToLeft(Cell *c);


/**  Fonction mouvement descendre
*
*   @cell c : cellule argument
*   @return : la position ou la cellule s'est déplacée
*/
void goToBottom(Cell *c);



#endif
