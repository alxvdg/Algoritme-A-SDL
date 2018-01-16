/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mouvement.h"
#include "plannification.h"

/************ FONCTION MOUVEMENTS ***************/

goToLeft(Cell *c)
{
    Cell ce=*c;
    ce.x=ce.x-1;
    *c=ce;

}

goToRight(Cell *c)
{
    Cell ce=*c;
    ce.x=ce.x+1;
    *c=ce;

}

goToBottom(Cell *c)
{
    Cell ce=*c;
    ce.y=ce.y+1;
    *c=ce;

}

goToTop(Cell *c)
{
    Cell ce=*c;
    ce.y=ce.y-1;
    *c=ce;

}
/********************************************************************/
