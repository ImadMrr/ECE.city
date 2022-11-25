#include "header.h"

Graphe* CreerGraphe()
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (t_sommet***)malloc(60*sizeof(t_sommet**));
    for(int i=0; i<60; i++)
    {
        Newgraphe->pSommet[i] = (t_sommet**)malloc(26*sizeof(t_sommet*));
    }
    for(int L = 0 ; L<60; L++)
    {
        for(int C = 0; C<26; C++)
        {
            Newgraphe->pSommet[L][C]=(t_sommet*)malloc(sizeof(t_sommet));
            Newgraphe->pSommet[L][C]->ligne = L;
            Newgraphe->pSommet[L][C]->colonne = C;
            Newgraphe->pSommet[L][C]->arc=NULL;
            Newgraphe->pSommet[L][C]->pred_L = -1;
            Newgraphe->pSommet[L][C]->pred_C = -1;
            Newgraphe->pSommet[L][C]->couleur = 0;
        }
    }
    return Newgraphe;
}

Graphe* CreerArete(Graphe* g,int s1_L,int s1_C,int s2_L,int s2_C)
{
    if(g->pSommet[s1_L][s1_C]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->ligne=s2_L;//le sommet adj à arc est s2
        Newarc->colonne=s2_C;//le sommet adj à arc est s2
        Newarc->valeur=1;
        Newarc->arc_suivant=NULL;//l'arv suivant est null
        g->pSommet[s1_L][s1_C]->arc=Newarc;//l'arc est entre s1 et s2
        return g;
    }

    else
    {
        pArc temp=g->pSommet[s1_L][s1_C]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->ligne=s2_L;//le sommet adj à arc est s2
        Newarc->colonne=s2_C;//le sommet adj à arc est s2
        Newarc->valeur=1;
        Newarc->arc_suivant=NULL;//l'arv suivant est null
        ///ici on range les arcs en fonction d'avec qui ils connectent leur sommet, on est dans l'ordre croissant des sommets
        temp->arc_suivant=Newarc;
        return g;
    }
}

t_ville * lire_graphe(t_ville* V)
{
    V->circ_eau = CreerGraphe(); // créer le graphe d'ordre sommets
    for( int L = 0; L < 60; L++)
    {
        for(int C = 0; C < 26; C++)
        {
            if(V->tabcases[L][C].type != 0 && V->tabcases[L][C].type != 1)
            {
                ///belekkkk ici ca veut dire la seine il considère c une route
                if(L%2 == 0)
                {
                    //en bas a gauche
                    if(V->tabcases[L+1][C-1].type != 0 && V->tabcases[L+1][C-1].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L+1, C-1);
                    }
                    //en bas a droite
                    if(V->tabcases[L+1][C].type != 0 && V->tabcases[L+1][C].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L+1, C);
                    }
                    //en haut a gauche
                    if(V->tabcases[L-1][C-1].type != 0 && V->tabcases[L-1][C-1].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L-1, C-1);
                    }
                    //en haut a droite
                    if(V->tabcases[L-1][C].type != 0 && V->tabcases[L-1][C].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L-1, C);
                    }
                }
                else
                {
                    //en bas a gauche
                    if(V->tabcases[L+1][C].type != 0 && V->tabcases[L+1][C].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L+1, C);
                    }
                    //en bas a droite
                    if(V->tabcases[L+1][C+1].type != 0 && V->tabcases[L+1][C+1].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L+1, C+1);
                    }
                    //en haut a gauche
                    if(V->tabcases[L-1][C].type != 0 && V->tabcases[L-1][C].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L-1, C);
                    }
                    //en haut a droite
                    if(V->tabcases[L-1][C+1].type != 0 && V->tabcases[L-1][C+1].type != 1)
                    {
                        V->circ_eau = CreerArete(V->circ_eau, L, C, L-1, C+1);
                    }
                }
            }
        }
    }
    return V;
}

Graphe* init(Graphe* g, int dep_L, int dep_C)//initialisation du graphe
{
    for(int L=0; L<60; L++)
    {
        for(int C = 0; C < 26; C++)
        {
            g->pSommet[L][C]->pred_L = -1;//aucun sommet n'admet de prédecesseur
            g->pSommet[L][C]->pred_C = -1;
            g->pSommet[L][C]->couleur = 0;//aucun sommet n'est marqué
            g->pSommet[L][C]->distance = INT_MAX;//les distances sont à "l'infini"
        }
    }
    g->pSommet[dep_L][dep_C]->distance = 0;//le sommet ini est à la distance 0 de lui-même
    g->pSommet[dep_L][dep_C]->pred_L = -3;//son prédecesseur est -3
    g->pSommet[dep_L][dep_C]->pred_C = -3;
    return g;
}

