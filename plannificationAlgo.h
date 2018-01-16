/*
* AUTHOR : Alexandre VIDEGRAIN
* ESIX 3A 2017-2018
*/

#ifndef plannificationalgo.h
#define plannificationalgo.h


#include "plannification.h"

/****************DEFINITION DE NOS STRUCTURES************************/

typedef struct{
    int x;
    int y;
    int couts;
    float heuristique;
}Noeud;
/********************************************************************/

int my_callbackfunc(int interval, void *param);
/**************** PROTOTYPES DE NOS FONCTIONS ************************/


/**  Convertit un noeud au format cellule
*
*   @param n : noeud à convertir
*   @return cell : résultat de la conversion
*/
Cell cellFromNoeud (Noeud n);


/**  Convertit une cellule au format noeud
*
*   @param c : cell à convertir
*   @return noeud : résultat de la conversion
*/
Noeud noeudFromCell (Cell c);


/**  Compare l'heuristique de 2 noeuds
*
*   @param n1 : premier noeud à comparer
*   @param n2 : second noeud à comparer
*   @return : 1 si l'heuristique du 1er est inférieur au 2nd, 0 si égal et -1 si supérieur
*/
int compareHeuristiqueNoeuds(Noeud n1, Noeud n2);


/**  Compare les positions de  2 noeuds
*
*   @param n1 : premier noeud à comparer
*   @param n2 : second noeud à comparer
*   @return : 1 si les deux noeuds ont la même position, sinon 0
*/
int compareNoeuds(Noeud n1, Noeud n2);


/**  ALGORITHME FINAL A*
* L'algorithme commence à un nœud choisi(départ). Il applique à ce nœud un "coût" (0).
* A* estime ensuite la distance qui sépare ce nœud du but à atteindre (heuristique du noeud)
* Le nœud est alors ajouté à une file d'attente prioritaire, appelée noeudOuvert
* L'algorithme retire le premier nœud de la file d'attente prioritaire (le nœud à l'heuristique la plus basse est retiré en premier).
* Si la file d'attente est vide cela interrompt l'algorithme.
* Si le nœud retenu est le nœud d'arrivée, A* reconstruit le chemin complet et s'arrête.
* Pour cette reconstruction on se sert d'une partie des informations sauvées dans la liste appelé noeudFerme

* Si le nœud n'est pas le nœud d'arrivée, de nouveaux nœuds sont créés pour tous les nœuds contigus admissibles ;
* Pour chaque nœud successif, A* calcule son coût et le stocke avec le nœud.
* Ce coût est calculé à partir de la somme du coût de son ancêtre et du coût de l'opération pour atteindre ce nouveau nœud.

* L'algorithme maintient également la liste de nœuds qui ont été vérifiés, appelée noeudFerme.
* Si un nœud produit est déjà dans cette liste avec un coût égal ou inférieur,
* aucune opération n'est faite.

* Une fois les trois étapes ci-dessus réalisées pour chaque nouveau nœud contigu,
* le nœud original pris de la file d'attente prioritaire est ajouté à la liste des nœuds vérifiés.
* Le prochain nœud est alors retiré de la file d'attente prioritaire et le processus recommence.

*   @param depart : noeud d'origine
*   @param objectif : noeud à atteindre
*   @param *chemin : tableau de cellule où sera ranger le parcours/chemin
*   @return : le nombre de mouvement à effectuer entre les deux cellules
*/
int calcul_chemin (Noeud depart, Noeud objectif,Cell *chemin);


/********* COPIE PILE NOEUDS DANS UN TABLEAU DE CELLULE ******************/
/**  Reconstitue le chemin entre les deux noeuds
*
*   @param *pile : pile des noeuds "fermés"
*   @param *chemin : tableaux de cellules à remplir
*   @return : nombre de mouvement
*/
//int reconstituerChemin(Pile *pile, Cell *chemin);


/**  Calcul les noeuds voisins
*
*   @param nDepart : noeud de depart
*   @param arrivee : noeud objectif, à atteindre
*   @param *voisins : tableaux des noeuds voisins
*   @return : nombre de voisins
*/
int calculVoisins (Noeud nDepart,Noeud arrivee,Noeud *voisins);


/**************** calcul hamiltonien et euclidien ****************************/
/**  Calcul la distance hamiltonienne (= de manhattan) entre deux cellules
*
*   @param depart : cellule de départ
*   @param arrivee : cellule d'arrivée
*   @return : distance entre les deux
*/
int calculHamiltonienN(Cell depart, Cell arrivee);


/**  Calcul la distance euclidienne (= vol d'oiseau) entre deux cellules
*
*   @param depart : cellule de départ
*   @param arrivee : cellule d'arrivée
*   @return : distance entre les deux
*/
float calculEuclidienN(Cell depart, Cell arrivee);


/**************** COUT HEURISTIQUE     ***********************/
/**  Calcul le cout heuristique entre deux cellules
*   Est la somme du cout euclidien et hamiltonien
*
*   @param depart : cellule de départ
*   @param arrivee : cellule d'arrivée
*   @param f : adresse ou écrire le résultat
*/
float coutHeuristiqueN(Cell depart, Cell arrivee);






/********************************************************************/
#endif
