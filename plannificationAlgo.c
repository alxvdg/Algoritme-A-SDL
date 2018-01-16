/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "mouvement.h"
#include "plannification.h"
#include "plannificationAlgo.h"
#include "maPile.h"

int grilleSDL[L][H]={0};

#define TIMER_STOP 0
#define TIMER_START 1

/***************** compare heuristique de 2 noeuds *******************************/
/** return 1 : D = A
    return 0 : D != A
**/
int compareHeuristiqueNoeuds(Noeud n1, Noeud n2)
{
    if ( n1.heuristique < n2.heuristique )
    {
          return 1;
    }
    else if ( n1.heuristique == n2.heuristique )
    {
           return 0;
    }
    else
    {
           return -1;
    }
}

int compareNoeuds(Noeud n1, Noeud n2)
{
    if ( (n1.x == n2.x) & (n1.y == n2.y)  )
        return 1;
    else
        return 0;

}
/*******************************************************************/

/***************** calcul chemin *******************************/
int calcul_chemin (Noeud depart, Noeud objectif,Cell *chemin)
{
    recup_grille(grilleSDL);


    Pile *noeudOuvert = initialiser();
    Pile *noeudFerme = initialiser();

    Noeud nActuel;
    Noeud buffer={0,0,0,0};
    Noeud voisins[4];

    int nbVoisins=0;
    int i=0,nbMouv=0;
    float f=0.0;
    empiler(noeudOuvert,depart); // on initialise la liste de noeuds

    if (noeudOuvert == NULL){exit(EXIT_FAILURE);}
    if (noeudFerme == NULL){exit(EXIT_FAILURE);}

    Element *actuel = noeudOuvert->premier;
    while (actuel != NULL) //on parcours notre liste ici
    {
        grilleSDL[objectif.x][objectif.y]=4;
        grilleSDL[depart.x][depart.y]=4;
        nActuel = depiler(noeudOuvert);
        //printf("Je depile (%d,%d)\n", nActuel.x,nActuel.y);

        if( compareNoeuds(nActuel,objectif) )
        {
           /* printf("\nPile noeud ouvert :\n");
            afficherPile(noeudOuvert);
            printf("\nPile noeud ferme :\n");
            afficherPile(noeudFerme);*/

            objectif.couts=noeudFerme->premier->n.couts+1;
            f=coutHeuristiqueN(cellFromNoeud(objectif),cellFromNoeud(objectif));
            buffer.heuristique=f;
            buffer.heuristique+=buffer.couts;

            empiler(noeudFerme,objectif);
            grilleSDL[objectif.x][objectif.y]=3;
            dessiner_grille(TIMER_STOP);
            nbMouv = reconstituerChemin(noeudFerme,chemin);// Reconstituer le chemin

            // Fin du programme
            clearPile(noeudFerme);
            clearPile(noeudOuvert);
            break;
        }
        else {

            nbVoisins = calculVoisins(nActuel,objectif,voisins);   // Calcul des voisins de nActuel

            // v = voisin[i]
            for(i=0;i<nbVoisins;i++)   // Parcours de tous les voisins v de nActuel
            {
                // Si v existe dans noeudFerme OU v existe dans noeudOuvert avec un cout inferieur
                if(estDansPile(voisins[i],noeudFerme) | estDansPileCout(voisins[i],noeudOuvert)  )
                {
                    //ne rien faire
                }
                // v n'existe pas dans noeudFerme ou v existe dans noeud ouvert mais avec un cout superieur
                else {
                    // Sinon v.couts = nActuel.couts+1
                    // v.heuristique = v.couts + coutHeuristique(v,Objectif)
                    // v.heuristique = v.couts +coutHeuristique(,)

                    buffer.x=voisins[i].x;
                    buffer.y=voisins[i].y;
                    buffer.couts=voisins[i].couts+1;
                    f=coutHeuristiqueN(cellFromNoeud(voisins[i]),cellFromNoeud(objectif));
                    buffer.heuristique=f;
                    buffer.heuristique+=buffer.couts;
                    *(voisins+i)= buffer;

                    empiler(noeudOuvert,voisins[i]);  // Ajouter v à noeudOuvert
                    grilleSDL[voisins[i].x][voisins[i].y]=2;
                }
            }
            // Ajouter noeud visité à noeudFerme
            empiler(noeudFerme,nActuel);
            grilleSDL[nActuel.x][nActuel.y]=3;
        }
        dessiner_grille(TIMER_START);
        triFusion(noeudOuvert,countPile(noeudOuvert)); //On effectue un tri des noeuds selon l'heuristique
        actuel = noeudOuvert->premier; // On passe au prochain noeud dont l'heuristique est la plus faible, grâce au tri
    }
    /*printf("\nPile noeud ouvert :\n");
    afficherPile(noeudOuvert);
    printf("\nPile noeud ferme :\n");
    afficherPile(noeudFerme);*/

    return nbMouv;
}


/*******************************************************************/


/********* COPIE PILE NOEUDS DANS UN TABLEAU DE CELLULE ******************/
// retourne le nombre d'éléments
int reconstituerChemin(Pile *pile, Cell *chemin)
{
    int i=0,cout=0;
    Noeud n;
    Noeud nPrecedent;
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;

    cout = actuel->n.couts; // on initialise le cout au cout pour atteindre l'objectif
    nPrecedent = actuel->n;
    while (actuel != NULL)
    {
        if(cout!=0)
        {
            while( (cout != actuel->n.couts)) {  depiler(pile); actuel = actuel->suivant; }
            n = depiler(pile);
            if( calculHamiltonienN( cellFromNoeud(n),cellFromNoeud(nPrecedent) ) == 1 || calculHamiltonienN( cellFromNoeud(n),cellFromNoeud(nPrecedent) ) == 0  )
            {
                *(chemin+i)=cellFromNoeud(n);//actuel->n);
               // printf("%d : noeud (%d,%d)\n",cout,(*(chemin+i)).x,(*(chemin+i)).y);
               grilleSDL[n.x][n.y]=4;

                cout--;
                i++;
                nPrecedent=n;
            }
        }
        actuel = actuel->suivant;
    }
    dessiner_grille(TIMER_STOP);
    return i;
}
/*******************************************************************/



/***************** ASSIGNATION CELLULE A PARTIR D'UN NOEUD *******************************/
int calculVoisins (Noeud nDepart,Noeud arrivee,Noeud *voisins)
{
    int i=0,nb=0;;
    Cell depart = cellFromNoeud(nDepart);
    Cell cell_voisins[4];
    Noeud buffer={0,0,0,0};


    CasesVoisines(depart, cell_voisins);

    for(i=0; i<4; i++)
    {
        if(Valid(cell_voisins[i]))
        {
            buffer.x=cell_voisins[i].x;
            buffer.y=cell_voisins[i].y;
            buffer.couts=nDepart.couts;
            buffer.heuristique=nDepart.heuristique;
            *(voisins+nb)= buffer;
            //printf("heuristique = %f\n",voisins[nb].heuristique);
            nb++;

        }
        //printf("Cell 1 : (%d,%d) - Cell 2 : (%d,%d)\n",cellFromNoeud(voisins[i]).x, cellFromNoeud(voisins[i]).y, arriv.x, arriv.y);
        //printf("heuristique = %f\n",voisins[i].heuristique);
    }
    return nb;
}
/*******************************************************/

/**************** calcul hamiltonien et euclidien ****************************/
int calculHamiltonienN(Cell depart, Cell arrivee)
{

    return (abs(depart.x-arrivee.x)+abs(depart.y-arrivee.y));
}

float calculEuclidienN(Cell depart, Cell arrivee)
{
    return (sqrt( pow((depart.x - arrivee.x),2)+ pow((depart.y - arrivee.y),2) ));   //pow (x,2) donne x a la puissance 2
}
/**************************************************************/

/**************** COUT HEURISTIQUE     ***********************/
float coutHeuristiqueN(Cell depart, Cell arrivee)
{
    //printf("depart : (%d,%d)\tarrivee: (%d,%d)\n",depart.x,depart.y,arrivee.x,arrivee.y);
    float tmp = (calculHamiltonienN(depart,arrivee) + calculEuclidienN(depart,arrivee));
   // printf("\ncout hamiltonien : %d\n cout euclidien : %f\ncout heuristique : %f\n",calculHamiltonienN(depart,arrivee),calculEuclidienN(depart,arrivee),tmp);
    return tmp;
}
/**************************************************************/

/***************** ASSIGNATION CELLULE A PARTIR D'UN NOEUD *******************************/
Cell cellFromNoeud (Noeud n)
{
    Cell c;
    c.x=n.x;
    c.y=n.y;
    return c;
}
/*******************************************************************/

/***************** ASSIGNATION NOEUD A PARTIR D'UNE CELLULE *******************************/
Noeud noeudFromCell (Cell c)
{
    Noeud n;
    n.x=c.x;
    n.y=c.y;
    n.couts=0;
    n.heuristique=0;
    return n;
}
/*******************************************************************/



int my_callbackfunc(int interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}


/*** dessiner grille ****/

void dessiner_grille(int timer)
{

    int i=0,j=0,ox=1,oy=1;
    static int size = 25;
    static int margin = 0;

    //Initialisation
    int x, y, width;
	unsigned char *p;
	SDL_Rect rect;
	Uint32 color;

    /** Chargement des paramètres d'affichage du QRcode **/
	ox += margin * size;
	oy += margin * size;
	int largeur=L*size;
	int hauteur=H*size;

    /**********************************/

    /*** Affichage graphique de la fenêtre et du QRcode ***/
    // initialize SDL video

    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER  ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        //return 1;
    }


    // On met un titre à notre fenêtre
    SDL_WM_SetCaption("Fenetre affichage QRcode", NULL);

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(largeur+100, hauteur+100, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
       // return 1;
    }

    /* Start the timer; the callback below will be executed after the delay */
    Uint32 delay = (33 / 10) * 200;  /* To round it down to the nearest 10 ms */
    int *my_callback_param;

    SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, my_callback_param);


	// Création de notre objet graphique dans lequel nous affichons le QRcode avec un fond blanc
	SDL_Surface* bmp = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur+ox, hauteur+oy, 32, 0, 0, 0, 0);

    for(i=0; i<L; i++)
    {
        for(j=0;j<H;j++)
        {
            // Boucle pour dessiner le QRcode à l'écran
            rect.x = ox + i * size;
            rect.y = oy + j * size;
            rect.w = (size-1);
            rect.h = (size-1);
            if(grilleSDL[i][j]==0 )
                color = SDL_MapRGBA(bmp->format, 255, 255, 255, 255); //blanc
            else if (grilleSDL[i][j]==2 )
                color = SDL_MapRGBA(bmp->format, 128, 128, 128, 255); // gris
            else if (grilleSDL[i][j]==3 )
                color = SDL_MapRGBA(bmp->format, 255, 0, 0, 255); // rouge
            else if (grilleSDL[i][j]==4 )
                color = SDL_MapRGBA(bmp->format, 0, 255, 0, 255); // rouge
            else
                color = SDL_MapRGBA(bmp->format, 0, 0, 0, 255); //noir

            SDL_FillRect(bmp, &rect, color);
        }
    }

    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
       // return 1;
    }

    // centre le QRcode au milieu de l'écran
    SDL_Rect dstrect;
   dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    int done = 0;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = 1;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = 1;
                    break;
                }

            case SDL_USEREVENT:
                {
                /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
                if(timer==1){
                done = 1;}
                break;
                }

            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        // draw bitmap, notre qrcode
       SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
      SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    /**********************************/

    // all is well ;)
    printf("Exited cleanly\n");
}





/**************************/
