#include "header.h"

void djikstra(Graphe* g, int dep_L, int dep_C)
{
    int stop = 0, imin_L, imin_C;
    g = init(g, dep_L, dep_C);
    while(stop == 0)//condition d'arrêt
    {
        minimum(g, &imin_L, &imin_C);//on cherche le sommet à la distance la plus petite du sommet initial
        if(imin_L != -1)
        {
            g->pSommet[imin_L][imin_C]->couleur = 1;//on marque le sommet
            pArc tmp = g->pSommet[imin_L][imin_C]->arc;//arc temporaire
            while(tmp != NULL)//tant que l'arc temporaire est différent de nul
            {
                if(g->pSommet[imin_L][imin_C]->distance + tmp->valeur < g->pSommet[tmp->ligne][tmp->colonne]->distance)
                {
                    //si la distance et le poids de l'arc sont inférieurs à l'arc
                    g->pSommet[tmp->ligne][tmp->colonne]->distance = g->pSommet[imin_L][imin_C]->distance + tmp->valeur;//on met à jour la distance
                    g->pSommet[tmp->ligne][tmp->colonne]->pred_L = g->pSommet[imin_L][imin_C]->ligne;//on note le prédecesseur
                    g->pSommet[tmp->ligne][tmp->colonne]->pred_C = g->pSommet[imin_L][imin_C]->colonne;//on note le prédecesseur
                }
                tmp = tmp->arc_suivant;//on passe à l'arc suivant
            }
        }
        else
            stop = 1;//condition d'arrêt
    }
}

void minimum(Graphe* g, int* imin_L, int* imin_C)//on cherche la distance minimum
{
    int lemin = INT_MAX;//le sommet qui est le plus près du sommet de départ
    for(int L = 0; L<60; L++)//on parcourt tout le graphe
    {
        for(int C = 0; C<26; C++)
        {
            if(g->pSommet[L][C]->couleur ==0 && g->pSommet[L][C]->distance < lemin)//si le sommet n'est pas marqué et que sa distance est inférieure a l'infini
            {
                lemin = g->pSommet[L][C]->distance;//le sommet qui est le plus près du sommet de départ=i
                *imin_L=L;
                *imin_C=C;
            }
        }
    }
    if(lemin == INT_MAX)
    {
        *imin_C = -1;
        *imin_L = -1;
    }
}

void minimum_eau(t_ville* V, int* imin_L, int* imin_C)//on cherche la distance minimum
{
    int lemin = INT_MAX;//le sommet qui est le plus près du sommet de départ
    for(int L = 0; L<60; L++)//on parcourt tout le graphe
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 5 && V->circ_eau->pSommet[L][C]->distance < lemin && V->tabcases[L][C].capa_eau != 0)//si le sommet n'est pas marqué et que sa distance est inférieure a l'infini
            {
                lemin = V->circ_eau->pSommet[L][C]->distance;//le sommet qui est le plus près du sommet de départ=i
                *imin_L=L;
                *imin_C=C;
            }
        }
    }
    if(lemin == INT_MAX)
    {
        *imin_C = -1;
        *imin_L = -1;
    }
}

void minimum_D(t_ville* V, int* imin_L, int* imin_C)//on cherche la distance minimum
{
    int lemin = INT_MAX;//le sommet qui est le plus près du sommet de départ
    for(int L = 0; L<60; L++)//on parcourt tout le graphe
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 4 && V->circ_eau->pSommet[L][C]->distance_fix < lemin && V->tabcases[L][C].vu != 1)//si le sommet n'est pas marqué et que sa distance est inférieure a l'infini
            {
                lemin = V->circ_eau->pSommet[L][C]->distance_fix;//le sommet qui est le plus près du sommet de départ=i
                *imin_L=L;
                *imin_C=C;
            }
        }
    }
    if(lemin == INT_MAX)
    {
        *imin_C = -1;
        *imin_L = -1;
    }
}

void minimum_elec(t_ville* V, int* imin_L, int* imin_C, int deb_L, int deb_C)//on cherche la distance minimum
{
    int lemin = INT_MAX;//le sommet qui est le plus près du sommet de départ
    for(int L = 0; L<60; L++)//on parcourt tout le graphe
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 6 && V->circ_eau->pSommet[L][C]->distance < lemin && (V->tabcases[L][C].capa_elec - V->tabcases[deb_L][deb_C].nbr_hab) >= 0)//si le sommet n'est pas marqué et que sa distance est inférieure a l'infini
            {
                lemin = V->circ_eau->pSommet[L][C]->distance;//le sommet qui est le plus près du sommet de départ=i
                *imin_L=L;
                *imin_C=C;
            }
        }
    }
    if(lemin == INT_MAX)
    {
        *imin_C = -1;
        *imin_L = -1;
    }
}

void minimum_pomp(t_ville* V, int* imin_L, int* imin_C)//on cherche la distance minimum
{
    int lemin = INT_MAX;//le sommet qui est le plus près du sommet de départ
    for(int L = 0; L<60; L++)//on parcourt tout le graphe
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 7 && V->circ_eau->pSommet[L][C]->distance < lemin)//si le sommet n'est pas marqué et que sa distance est inférieure a l'infini
            {
                lemin = V->circ_eau->pSommet[L][C]->distance;//le sommet qui est le plus près du sommet de départ=i
                *imin_L=L;
                *imin_C=C;
            }
        }
    }
    if(lemin == INT_MAX)
    {
        *imin_C = -1;
        *imin_L = -1;
    }
}
