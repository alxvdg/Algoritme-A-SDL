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
*   @param n : noeud � convertir
*   @return cell : r�sultat de la conversion
*/
Cell cellFromNoeud (Noeud n);


/**  Convertit une cellule au format noeud
*
*   @param c : cell � convertir
*   @return noeud : r�sultat de la conversion
*/
Noeud noeudFromCell (Cell c);


/**  Compare l'heuristique de 2 noeuds
*
*   @param n1 : premier noeud � comparer
*   @param n2 : second noeud � comparer
*   @return : 1 si l'heuristique du 1er est inf�rieur au 2nd, 0 si �gal et -1 si sup�rieur
*/
int compareHeuristiqueNoeuds(Noeud n1, Noeud n2);


/**  Compare les positions de  2 noeuds
*
*   @param n1 : premier noeud � comparer
*   @param n2 : second noeud � comparer
*   @return : 1 si les deux noeuds ont la m�me position, sinon 0
*/
int compareNoeuds(Noeud n1, Noeud n2);


/**  ALGORITHME FINAL A*
* L'algorithme commence � un n�ud choisi(d�part). Il applique � ce n�ud un "co�t" (0).
* A* estime ensuite la distance qui s�pare ce n�ud du but � atteindre (heuristique du noeud)
* Le n�ud est alors ajout� � une file d'attente prioritaire, appel�e noeudOuvert
* L'algorithme retire le premier n�ud de la file d'attente prioritaire (le n�ud � l'heuristique la plus basse est retir� en premier).
* Si la file d'attente est vide cela interrompt l'algorithme.
* Si le n�ud retenu est le n�ud d'arriv�e, A* reconstruit le chemin complet et s'arr�te.
* Pour cette reconstruction on se sert d'une partie des informations sauv�es dans la liste appel� noeudFerme

* Si le n�ud n'est pas le n�ud d'arriv�e, de nouveaux n�uds sont cr��s pour tous les n�uds contigus admissibles ;
* Pour chaque n�ud successif, A* calcule son co�t et le stocke avec le n�ud.
* Ce co�t est calcul� � partir de la somme du co�t de son anc�tre et du co�t de l'op�ration pour atteindre ce nouveau n�ud.

* L'algorithme maintient �galement la liste de n�uds qui ont �t� v�rifi�s, appel�e noeudFerme.
* Si un n�ud produit est d�j� dans cette liste avec un co�t �gal ou inf�rieur,
* aucune op�ration n'est faite.

* Une fois les trois �tapes ci-dessus r�alis�es pour chaque nouveau n�ud contigu,
* le n�ud original pris de la file d'attente prioritaire est ajout� � la liste des n�uds v�rifi�s.
* Le prochain n�ud est alors retir� de la file d'attente prioritaire et le processus recommence.

*   @param depart : noeud d'origine
*   @param objectif : noeud � atteindre
*   @param *chemin : tableau de cellule o� sera ranger le parcours/chemin
*   @return : le nombre de mouvement � effectuer entre les deux cellules
*/
int calcul_chemin (Noeud depart, Noeud objectif,Cell *chemin);


/********* COPIE PILE NOEUDS DANS UN TABLEAU DE CELLULE ******************/
/**  Reconstitue le chemin entre les deux noeuds
*
*   @param *pile : pile des noeuds "ferm�s"
*   @param *chemin : tableaux de cellules � remplir
*   @return : nombre de mouvement
*/
//int reconstituerChemin(Pile *pile, Cell *chemin);


/**  Calcul les noeuds voisins
*
*   @param nDepart : noeud de depart
*   @param arrivee : noeud objectif, � atteindre
*   @param *voisins : tableaux des noeuds voisins
*   @return : nombre de voisins
*/
int calculVoisins (Noeud nDepart,Noeud arrivee,Noeud *voisins);


/**************** calcul hamiltonien et euclidien ****************************/
/**  Calcul la distance hamiltonienne (= de manhattan) entre deux cellules
*
*   @param depart : cellule de d�part
*   @param arrivee : cellule d'arriv�e
*   @return : distance entre les deux
*/
int calculHamiltonienN(Cell depart, Cell arrivee);


/**  Calcul la distance euclidienne (= vol d'oiseau) entre deux cellules
*
*   @param depart : cellule de d�part
*   @param arrivee : cellule d'arriv�e
*   @return : distance entre les deux
*/
float calculEuclidienN(Cell depart, Cell arrivee);


/**************** COUT HEURISTIQUE     ***********************/
/**  Calcul le cout heuristique entre deux cellules
*   Est la somme du cout euclidien et hamiltonien
*
*   @param depart : cellule de d�part
*   @param arrivee : cellule d'arriv�e
*   @param f : adresse ou �crire le r�sultat
*/
float coutHeuristiqueN(Cell depart, Cell arrivee);






/********************************************************************/
#endif
