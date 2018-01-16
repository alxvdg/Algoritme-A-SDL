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





Cell P1 = {0,0,'v'};
Cell P2 = {4,0,'v'};
Cell P3 = {8,0,'v'};
Cell P4 = {8,3,'v'};
Cell P5 = {8,5,'v'};
Cell P6 = {4,5,'v'};
Cell P7 = {0,5,'v'};
Cell P8 = {0,3,'v'};

Cell R1 = {3,2,'v'};
Cell R2 = {5,2,'v'};

int main ( int argc, char** argv )
{
    /****** INITIALISATION DU PROBLEME ******/
    Cell Checkpoint[NB_CHECKPOINT]={P1, P2, P3, P4, P5, P6, P7, P8};
    Cell obstacles[NB_OBSTACLE]={ {2,2,'f'}, {2,3,'f'},{3,3,'f'},{4,3,'f'},{5,3,'f'},{6,3,'f'},{6,2,'f'} };

    initCheckpoint(Checkpoint,NB_CHECKPOINT);
    initObstacles(obstacles,NB_OBSTACLE);
    initR1(R1);
    initR2(R2);
    /****** ************************ ******/

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }


    // program main loop
    bool done = false;
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
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
