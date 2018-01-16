/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "maPile.h"
#include "plannification.h"
#include "plannificationAlgo.h"

Pile *initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}

void empiler(Pile *pile, Noeud n)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->n = n;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

void enfiler(Pile *pile, Noeud n)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->n = n;
    nouveau->suivant = NULL;

    if (pile->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element *elementActuel = pile->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
        pile->premier = nouveau;
    }
}

Noeud defiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Noeud n = {0,0,0,0};

    /* On vérifie s'il y a quelque chose à défiler */
    if (pile->premier != NULL)
    {
        Element *elementDefile = pile->premier;

        n = elementDefile->n;
        pile->premier = elementDefile->suivant;
        free(elementDefile);
    }

    return n;
}


Noeud depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Noeud noeud = {0,0,0,0};
    Element *elementDepile = pile->premier;
    if (pile != NULL && pile->premier != NULL)
    {
        noeud = elementDepile->n;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }
    return noeud;
}

void clearPile(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;
    while (actuel != NULL)
    {
        depiler(pile);
        actuel = actuel->suivant;
    }
}



int estDansPile(Noeud n,Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;
    while (actuel != NULL)
    {
        if( compareNoeuds(n,actuel->n) )
            return 1;

        actuel = actuel->suivant;
    }
    return 0;
}

void triFusion(Pile *pile,int nb)
{
    int i=0,mid;
    if(nb < 2) return; //condition pour stopper la recursivité de l'algo de triage

    Pile *pile1 = initialiser(); // pile 1
    Pile *pile2 = initialiser(); // pile 2
	mid = nb/2;  // milieu de la liste

    if (pile1 == NULL || pile2 == NULL || pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = pile->premier;
    Noeud nActuel;
    while (actuel != NULL)
    {
        if(i < mid)
        {
            nActuel=depiler(pile);
            empiler(pile1,nActuel);
        }
        else if(i < nb){
            nActuel=depiler(pile);
            empiler(pile2,nActuel);
        }
        i++;
        actuel = pile->premier;//actuel->suivant;
    }

    /*printf("\nAffichage pile origine P:\n");
    afficherPile(pile);
    printf("\nAffichage pile P1:\n");
    afficherPile(pile1);
    printf("\nAffichage pile P2:\n");
    afficherPile(pile2);*/

    triFusion(pile1,countPile(pile1));
    triFusion(pile2,countPile(pile2));
    fusionPile(pile,pile1,pile2);
}

void fusionPile(Pile* fusion, Pile *pile1, Pile *pile2)
{

    if (pile1 == NULL || pile2 == NULL || fusion == NULL)
    {
        exit(EXIT_FAILURE);
    }

    /*printf("\n***ETAPE COMBINAISON DES PILES***\n");
    printf("\nAffichage pile P1:\n");
    afficherPile(pile1);
    printf("\nAffichage pile P2:\n");
    afficherPile(pile2);*/

    Element *tete1 = pile1->premier;
    Element *tete2 = pile2->premier;
    Noeud n;
    while ( tete1 != NULL && tete2 != NULL )
    {
        if( compareHeuristiqueNoeuds(tete1->n, tete2->n)==-1 ) // si tete1 < tete2
        {
            n=depiler(pile2);
            //empiler(fusion,n);
            enfiler(fusion,n); // on le met à la fin de liste
            tete2 = pile2->premier;//actuel->suivant;
        }
        else
        {
            n=depiler(pile1);
            //empiler(fusion,n);
            enfiler(fusion,n); // on met à la fin de liste
            tete1 = pile1->premier;//actuel->suivant
        }
    }
    while ( tete1 != NULL)
    {
        n=depiler(pile1);
        //empiler(fusion,n);
        enfiler(fusion,n); // on met à la fin de liste
        tete1 = pile1->premier;//actuel->suivant;
    }
    while ( tete2 != NULL )
    {
        n=depiler(pile2);
        //empiler(fusion,n);
        enfiler(fusion,n); // on met à la fin de liste
        tete2 = pile2->premier;//actuel->suivant;
    }

    /*printf("\nAffichage pile fusion:\n");
    afficherPile(fusion);
    printf("\n******************************\n");*/

}

/***********************************************************************/

int estDansPileCout(Noeud n,Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;
    while (actuel != NULL)
    {
        if( compareNoeuds(n,actuel->n) )
        {
            if(n.couts < actuel->n.couts)
                return 1;
        }

        actuel = actuel->suivant;
    }
    return 0;
}

int countPile(Pile *pile)
{
    int i=0;
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;
    while (actuel != NULL)
    {
        actuel = actuel->suivant;
        i++;
    }

    return i;
}


void afficherPile(Pile *pile)
{
    int i=0;
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;
    while (actuel != NULL)
    {
        printf("%d : (%d,%d) | couts = %d | heuristique = %f\n", i,actuel->n.x, actuel->n.y, actuel->n.couts, actuel->n.heuristique);
        actuel = actuel->suivant;
        i++;
    }
    printf("\n");

}


