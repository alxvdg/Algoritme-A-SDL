
#ifndef plannification.h
#define plannification.h


/** MOUVEMENT
----- 1 -----
--3- POS -4--
----- 2 -----
HAUT 1
BAS 2
GAUCHE 3
DROITE 4
RIEN 0
**/

/** ETAT
    v : valide
    f : obstacle
**/
/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#define N 10 //D�finition de la longueur d'un cot� de la matrice grille
#define H 21 //definition hauteur grille
#define L 21//definition largeur grille
#define NB_OBSTACLE 7 //D�finition du nombre d'obstacles

/****************DEFINITION DE NOS STRUCTURES************************/

typedef struct{
    int x;
    int y;
    char etat;
}Cell;

/********************************************************************/


/**************** PROTOTYPES DE NOS FONCTIONS ************************/

/**  V�rifie si la position est valide ou non par rapport a la grille
*
*   @cell c : cellule � v�rifier
*   @return : 1 si valide 0 sinon
*/
int Valid (Cell c);


/**  Affiche la grille sur la console
*
*/
void AfficheGrille(void);


/**  Initialise la grille selon un tableau de cellules obstacles
*
*   @cell obs : tableau de cellules
*/
void init_grille (Cell obs[NB_OBSTACLE]);


/**  Remplit le tableau tab des cases voisines d'une cellule donn�e
*
*   @cell c : cellule argument
*   @cell tab : tableau des cellules voisines
*/
void CasesVoisines(Cell c, Cell voisin[4]);


/**  Affiche les voisins � partir du tableau
*
*   @cell tab c : tableau des cellules voisines
*/
void AfficheVoisins(Cell voisin[4]);


/**  Calcul la distance hamiltonienne (= de manhattan) entre deux cellules
*
*   @param depart : cellule de d�part
*   @param arrivee : cellule d'arriv�e
*   @return : distance entre les deux
*/
int calculHamiltonien(Cell depart, Cell arrivee);


/**  Calcul la distance euclidienne (= vol d'oiseau) entre deux cellules
*
*   @param depart : cellule de d�part
*   @param arrivee : cellule d'arriv�e
*   @return : distance entre les deux
*/
float calculEuclidien(Cell depart, Cell arrivee);


/**  Calcul le cout heuristique entre deux cellules
*   Est la somme du cout euclidien et hamiltonien
*
*   @param depart : cellule de d�part
*   @param arrivee : cellule d'arriv�e
*   @param f : adresse ou �crire le r�sultat
*/
float coutHeuristique(Cell depart, Cell arrivee,float *f);



/**  indique la meilleure direction ou se diriger parmis les voisins d'une cellule
*
*   @param voisin : tableau des 4 voisins d'une cellule "d�part"
*   @param arrive : cellule d'arriv�e
*   @return cell : cellule ou se diriger
*/
Cell directionOptimisee( Cell voisin[4], Cell arrivee );


/**  Premier algorithme, Fonction calcul le meilleur chemin � emprunter
*
*   @cell D : cellule d�part
*   @cell A : cellule destination
*   @char *plan : chemin � emprunter
*   @return int : retourne le nombre de d�placement � effectuer
*/
int planning (Cell D, Cell A, Cell *plan);


/**  Fonction qui permet � une cellule de suivre un chemin et d'arriver � une cellule de destination
*
*   @cell *chemin : chemin � suivre, tableau de cellule
*   @int nvMvt : nombre de cellule dans ce chemin
*   @cell src : cellule de d�part
*   @return cell : retourne la cellule d'arriv�e
*/
Cell suivreChemin(Cell *chemin, int nbMvt,Cell src);


/**  Fonction qui permet de suivre un plan (haut, bas, droite, gauche)
*
*   @char *plan : plan � suivre, tableau des directions � prendre
*   @int nbMvt : nomre de d�placement � r�aliser
*   @Cell : cellule de d�part
*/
Cell suivrePlan (char *plan, int nbMvt, Cell depart);



/**  Fonction qui test si deux cellules sont �gales
*
*   @cell c : cellule � v�rifier
*   @cell c : cellule � v�rifier
*   @return int : 1 si �gales 0 sinon
*/
int equals(Cell D, Cell A);


/**  Fonction qui renvoit l'identifiant de l'action � faire
*
*   @cell c : cellule d�part
*   @cell c : cellule destination
*   @return : 0:rien 1:monter 2:descendre 3:gauche 4:droite
*/
int action(Cell src, Cell dst);


/**  Fonction qui convertit en string l'action � faire
*
*   @int nbAction : identifiant de l'action � r�aliser
*   @return *char : string de l'action a r�aliser
*/
char* actionToString(int nbAction);


/**  Algorithme final, algorithme connu sous le nom de "plannification A*"
*
*   @cell D : cellule d�part
*   @cell A : cellule destination
*   @char *chemin : tableau de cellules � "remplir"
*   @return int : retourne le nombre de d�placement � effectuer
*/
int planningAlgo(Cell D, Cell A, Cell *chemin);
/*********************************************************************/

#endif
