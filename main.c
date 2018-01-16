#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <SDL/SDL.h>

#include "theorieJeux.h"
#include "mouvement.h"
#include "plannification.h"
#include "maPile.h"
#include "patrouille.h"

Cell depart = {0,0,'v'};
Cell arrive = {20,20,'v'};

int main ( int argc, char** argv )
{
    Cell* chemin = NULL;

    /****** INITIALISATION DU PROBLEME ******/
    Cell obstacles[NB_OBSTACLE]={ {3,7,'f'}, {4,6,'f'},{5,5,'f'},{6,4,'f'},{7,3,'f'},{2,8,'f'},{9,9,'f'} };
    init_grille (obstacles);
    /****** ************************ ******/

    /** Allocation chemin*/
    chemin = malloc(L * H * sizeof(Cell));
    if (chemin == NULL){exit(0);}// On vérifie si l'allocation a marché ou non
    /*******************/

    planningAlgo(depart,arrive,chemin);

    //patrouille();


    return 0;
}

