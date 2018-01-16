
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

#define N 10 //Définition de la longueur d'un coté de la matrice grille
#define H 21 //definition hauteur grille
#define L 21//definition largeur grille
#define NB_OBSTACLE 7 //Définition du nombre d'obstacles

/****************DEFINITION DE NOS STRUCTURES************************/

typedef struct{
    int x;
    int y;
    char etat;
}Cell;

/********************************************************************/


/**************** PROTOTYPES DE NOS FONCTIONS ************************/

/**  Vérifie si la position est valide ou non par rapport a la grille
*
*   @cell c : cellule à vérifier
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


/**  Remplit le tableau tab des cases voisines d'une cellule donnée
*
*   @cell c : cellule argument
*   @cell tab : tableau des cellules voisines
*/
void CasesVoisines(Cell c, Cell voisin[4]);


/**  Affiche les voisins à partir du tableau
*
*   @cell tab c : tableau des cellules voisines
*/
void AfficheVoisins(Cell voisin[4]);


/**  Calcul la distance hamiltonienne (= de manhattan) entre deux cellules
*
*   @param depart : cellule de départ
*   @param arrivee : cellule d'arrivée
*   @return : distance entre les deux
*/
int calculHamiltonien(Cell depart, Cell arrivee);


/**  Calcul la distance euclidienne (= vol d'oiseau) entre deux cellules
*
*   @param depart : cellule de départ
*   @param arrivee : cellule d'arrivée
*   @return : distance entre les deux
*/
float calculEuclidien(Cell depart, Cell arrivee);


/**  Calcul le cout heuristique entre deux cellules
*   Est la somme du cout euclidien et hamiltonien
*
*   @param depart : cellule de départ
*   @param arrivee : cellule d'arrivée
*   @param f : adresse ou écrire le résultat
*/
float coutHeuristique(Cell depart, Cell arrivee,float *f);



/**  indique la meilleure direction ou se diriger parmis les voisins d'une cellule
*
*   @param voisin : tableau des 4 voisins d'une cellule "départ"
*   @param arrive : cellule d'arrivée
*   @return cell : cellule ou se diriger
*/
Cell directionOptimisee( Cell voisin[4], Cell arrivee );


/**  Premier algorithme, Fonction calcul le meilleur chemin à emprunter
*
*   @cell D : cellule départ
*   @cell A : cellule destination
*   @char *plan : chemin à emprunter
*   @return int : retourne le nombre de déplacement à effectuer
*/
int planning (Cell D, Cell A, Cell *plan);


/**  Fonction qui permet à une cellule de suivre un chemin et d'arriver à une cellule de destination
*
*   @cell *chemin : chemin à suivre, tableau de cellule
*   @int nvMvt : nombre de cellule dans ce chemin
*   @cell src : cellule de départ
*   @return cell : retourne la cellule d'arrivée
*/
Cell suivreChemin(Cell *chemin, int nbMvt,Cell src);


/**  Fonction qui permet de suivre un plan (haut, bas, droite, gauche)
*
*   @char *plan : plan à suivre, tableau des directions à prendre
*   @int nbMvt : nomre de déplacement à réaliser
*   @Cell : cellule de départ
*/
Cell suivrePlan (char *plan, int nbMvt, Cell depart);



/**  Fonction qui test si deux cellules sont égales
*
*   @cell c : cellule à vérifier
*   @cell c : cellule à vérifier
*   @return int : 1 si égales 0 sinon
*/
int equals(Cell D, Cell A);


/**  Fonction qui renvoit l'identifiant de l'action à faire
*
*   @cell c : cellule départ
*   @cell c : cellule destination
*   @return : 0:rien 1:monter 2:descendre 3:gauche 4:droite
*/
int action(Cell src, Cell dst);


/**  Fonction qui convertit en string l'action à faire
*
*   @int nbAction : identifiant de l'action à réaliser
*   @return *char : string de l'action a réaliser
*/
char* actionToString(int nbAction);


/**  Algorithme final, algorithme connu sous le nom de "plannification A*"
*
*   @cell D : cellule départ
*   @cell A : cellule destination
*   @char *chemin : tableau de cellules à "remplir"
*   @return int : retourne le nombre de déplacement à effectuer
*/
int planningAlgo(Cell D, Cell A, Cell *chemin);
/*********************************************************************/

#endif
