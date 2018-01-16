/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mouvement.h"
#include "plannification.h"
#include "plannificationAlgo.h"
#include "maPile.h"
/******************* INITIALISATION DE LA GRILLE  ****************/

int grille[L][H]={0};

/*****************************************************************/

/********************FONCTION VALID**********************************/
/*  Vérifie si la position est valide ou non par rapport a la grille*/
/*  De plus, prend en compte les obstacles
        1 = obstacle
        0 = libre */

int Valid (Cell c)
{
    if( (c.x<L) & (c.x>=0) & (c.y<H) & (c.y>=0) & (c.etat=='v')) return 1;
}
/********************************************************************/

/********************FONCTION VALID**********************************/
/* Initialise la grille avec les obstacles*/
void init_grille (Cell obs[NB_OBSTACLE])
{
    int i=0,j=0;

    // On initialise la matrice à 0
    for(i=0; i<L; i++)
    {
        for(j=0;j<H;j++)
        {
            grille[i][j]=0;
        }
    }

    // On initialise les obstacles
    for(i=0; i<NB_OBSTACLE; i++)
    {
        if( obs[i].etat == 'f')
        {
            grille[obs[i].x][obs[i].y]= 1;
        }
    }

}
/********************************************************************/


/* récupère la grille */
void recup_grille (int g[L][H])
{
    int i=0,j=0;

    for(i=0; i<L; i++)
    {
        for(j=0;j<H;j++)
        {
            g[i][j] = grille[i][j];
        }
    }
}



/************FONCTION QUI AFFICHE LA GRILLE***************/

void AfficheGrille(void)
{
    int i = 0,j=0;
    for(i=0;i<H;i++)
    {
        for(j=0;j<L;j++)
        {
            printf(" %d ",grille[j][i]);
            if(j==L-1){printf("\n");}
        }
    }
    printf("\n");
}

/**********************************************************************/

/************FONCTION QUI RENVOIE LES CASES VOISINES D'UN POINT******/
void CasesVoisines(Cell c, Cell tab[4])
{
    int i=0;

    tab[0].x = c.x ;
    tab[0].y = c.y-1 ;

    tab[1].x = c.x ;
    tab[1].y = c.y+1 ;

    tab[2].x = c.x-1 ;
    tab[2].y = c.y ;

    tab[3].x = c.x+1 ;
    tab[3].y = c.y;

    for(i=0; i<4; i++)
    {
        if(grille[tab[i].x][tab[i].y]==1)
            tab[i].etat='f';
        else
            tab[i].etat='v';
    }
}
/********************************************************************/




/***************FONCTION QUI AFFICHE LES COORDONÉES DES VOISINS******/
void AfficheVoisins(Cell tab[4])
{
    printf("Les cases voisines du point sont :\n");
    int i;
    for(i=0;i<4;i++)
    {
        if(Valid(tab[i]))
            if(grille[tab[i].x][tab[i].y]==0)
                printf("%d,%d\n",tab[i].x,tab[i].y);
    }
    printf("\n");

}
/********************************************************************/

/**************** calcul hamiltonien et euclidien ****************************/
int calculHamiltonien(Cell depart, Cell arrivee)
{
    return (abs(depart.x-arrivee.x)+abs(depart.y-arrivee.y));
}

float calculEuclidien(Cell depart, Cell arrivee)
{
    return (sqrt( pow((depart.x - arrivee.x),2)+ pow((depart.y - arrivee.y),2) ));   //pow (x,2) donne x a la puissance 2
}
/**************************************************************/

/**************** COUT HEURISTIQUE     ***********************/
float coutHeuristique(Cell depart, Cell arrivee,float *f)
{
    *f=(calculHamiltonien(depart,arrivee) + calculEuclidien(depart,arrivee));
    //printf("\ncout hamiltonien : %d\n cout euclidien : %f\ncout heuristique : %f\n",calculHamiltonien(depart,arrivee),calculEuclidien(depart,arrivee),*f);
}
/**************************************************************/


/*********** fonction calcul meilleure direction à prendre parmis les voisins  *********/

Cell directionOptimisee( Cell voisin[4], Cell arrivee )
{
    float f=0.0,fmin=0.0;
    int i=0,c=0;
    Cell direction;

    for(i=0;i<4;i++)
    {
        if(Valid(voisin[i]))
        {
            coutHeuristique(voisin[i],arrivee,&f);
            if(fmin==0 && c==0)
            {
                fmin=f;
                direction=voisin[i];
                c++;
            }
            if(f<fmin)
            {
                fmin=f;
                direction=voisin[i] ;
            }
            //printf("voisin[%d]:(%d,%d) : cout = %f\n",i,voisin[i].x,voisin[i].y,f);
        }
    }
    //printf("direction = (%d,%d)\n ",direction.x,direction.y);

    return direction;
}
/*******************************************/



/***************** ALGORITHME PLANNING *******************************/
/**  cell D : départ
    cell A : arrivée
    char *plan : tableau des cellules à suivre
**/
int planning(Cell D, Cell A, Cell *chemin)
{
    int i=0;

    Cell dir;
    Cell tab[4];
    Cell etat=D;
    /** Allocation tableau*/
    char* plan = NULL;
    plan = malloc(H * L * sizeof(char));
    if (plan == NULL) // On vérifie si l'allocation a marché ou non
    {
        exit(0); // On arrête tout
    }
    /*******************/

    while ( (equals(etat,A)!=1) )
    {
        CasesVoisines(etat,tab); // met dans tab les cases voisines de la case etat
        dir = directionOptimisee(tab,A);

        if(  (*(plan+i-1)==1) && (*(plan+i-2)==2)  && (i!=0) ) // si on revient à la cellule précédente (boucle) - BAS HAUT
        {
            //on annule cette possibilité de chemin
            grille[dir.x][dir.y]=1;// On enlève la possibilité de direction qui met le robot dans une boucle
            //AfficheGrille();
            i=i-2;
        }
        else if(  (*(plan+i-1)==2) && (*(plan+i-2)==1)  && (i!=0) ) // si on revient à la cellule précédente (boucle) - HAUT BAS
        {
            grille[dir.x][dir.y]=1;// On enlève la possibilité de direction qui met le robot dans une boucle
            i=i-2;
        }
        else if(  (*(plan+i-1)==3) && (*(plan+i-2)==4)  && (i!=0) ) // si on revient à la cellule précédente (boucle) - DROTIE GAUCHE
        {
            grille[dir.x][dir.y]=1;// On enlève la possibilité de direction qui met le robot dans une boucle
            i=i-2;
        }
        else if(  (*(plan+i-1)==4) && (*(plan+i-2)==3)  && (i!=0) ) // si on revient à la cellule précédente (boucle) - GAUCHE DROITE
        {
           grille[dir.x][dir.y]=1;// On enlève la possibilité de direction qui met le robot dans une boucle
            i=i-2;
        }
        else {  //tout les autres cas
            //grille[dir.x][dir.y]=2;

            *(plan+i)= action(etat,dir);
             *(chemin+i)= dir;
           // printf("%d : (%d)\n",i,*(plan+i));
            i++;
            etat=dir;
        }
    }
    free(plan);

    return i;
}
/*******************************************************************/


/***************** SUIVRE CHEMIN *******************************/
Cell suivreChemin (Cell *chemin, int nbMvt,Cell src)
{
    int i=0;

    /** Allocation tableau*/
    char* plan = NULL;
    plan = malloc(H * L * sizeof(Cell));
    Cell c = src;
    if (plan == NULL) // On vérifie si l'allocation a marché ou non
    {
        exit(0); // On arrête tout
    }
    /*******************/

    for(i=0;i<nbMvt;i++)
    {
        *(plan+i)=action(c,chemin[nbMvt-i-1]); // car le chemin est donné à l'envers
        c=chemin[nbMvt-i-1];
       //printf("(%d,%d)\t",c.x,c.y);
       //printf("%s\n",actionToString(*(plan+i)));
    }
    c = suivrePlan(plan,nbMvt,src);
    c = chemin[0];
    free(plan);
   // printf("Cellule d'arrivee : (%d,%d)\n",c.x,c.y);
    return c; //retourne la cellule d'arrivée
}
/*******************************************************************/

/***************** SUIVRE PLAN *******************************/
Cell suivrePlan (char *plan, int nbMvt, Cell depart)
{
    int i=0;
    Cell c=depart;
    for(i=0; i<nbMvt; i++)
    {
        if(*(plan+i)==1)
            goToTop(&c);

        if(*(plan+i)==2)
            goToBottom(&c);

        if(*(plan+i)==3)
            goToLeft(&c);

        if(*(plan+i)==4)
            goToRight(&c);

        grille[c.x][c.y]=2; // à commenter à l'implémentation sur le robot
    }

    return c;
}
/*******************************************************************/

/***************** VERIFIE SI DEUX CELL SONT EGALES *******************************/
/** return 1 : D = A
    return 0 : D != A
**/
int equals(Cell D, Cell A)
{
    if ((D.y==A.y) && (D.x==A.x)) {
          return 1;
    }
    else {
           return 0;
    }
}
/*******************************************************************/


/***************** Renvoit l'action à faire ********************/
int action(Cell src, Cell dst)
{
    int nbAction=0;

    if ( (dst.x-src.x)==1 )
    {
            nbAction = 4;
    }
    else if ( (dst.x-src.x)== -1 )
    {
            nbAction = 3;
    }
    else if ( (dst.y-src.y)== 1 )
    {
            nbAction = 2;
    }
    else if ( (dst.y-src.y)== -1 )
    {
            nbAction = 1;
    }

    return nbAction;
}
/**********************************************/

/***************** Renvoit l'action à faire ********************/
char* actionToString(int nbAction)
{
    char* strAction="rien";

    if ( nbAction == 4 )
    {
        strAction = "DROITE";
    }
    else  if ( nbAction == 3 )
    {
        strAction = "GAUCHE";
    }
    else  if ( nbAction == 2 )
    {
        strAction = "BAS";
    }
    else  if ( nbAction == 1 )
    {
        strAction = "HAUT";
    }

    return strAction;
}
/**********************************************/


/*************** ALGO PLANNIFICATION A star ***************/


int planningAlgo(Cell D, Cell A, Cell *chemin)
{
    int nbMouv=0;

    Noeud depart = noeudFromCell(D);
    Noeud objectif = noeudFromCell(A);
    nbMouv = calcul_chemin(depart, objectif,chemin);

    return nbMouv;
}


/**********************************************************/
