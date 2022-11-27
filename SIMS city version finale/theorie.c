#include "header.h"

/// Fonction qui lance un BFS pour la connexite
/*
    meme BFS que lors des TP mais adapte au graphe en matrice
    afin de sauvegarder la ligne et la colone du sommet enfile
    on utilise 2 files
*/
int BFS(t_ville* V,Graphe* ungraph, int dep_L, int dep_C)
{
    int departL = dep_L;
    int departC = dep_C;
    t_maillon* mafileL = NULL;
    t_maillon* mafileC = NULL;//initialisation
    mafileL = ajoutFileDyna(mafileL, creerFileDyna(departL));//ajout si vide
    mafileC = ajoutFileDyna(mafileC, creerFileDyna(departC));//ajout si vide
    ungraph = marquage(ungraph,departL, departC);
    int connexe = 0;
    while(mafileL != NULL && mafileC != NULL)
    {
        mafileL = supFileDyna(mafileL, &departL);
        mafileC = supFileDyna(mafileC, &departC);//suppression
        pArc temp = ungraph->pSommet[departL][departC]->arc;//arc temporaire
        while(temp != NULL)//tant que l'arc temporaire n'est pas nul
        {
            if(V->tabcases[temp->ligne][temp->colonne].type == 2 || V->tabcases[temp->ligne][temp->colonne].type == 3 || V->tabcases[temp->ligne][temp->colonne].type == 8)
            {
                connexe = 1;
            }
            if(ungraph->pSommet[temp->ligne][temp->colonne]->couleur != 1)//s'il n'est pas marqué
            {
                mafileL = ajoutFileDyna(mafileL, creerFileDyna(temp->ligne));
                mafileC = ajoutFileDyna(mafileC, creerFileDyna(temp->colonne));//ajout à la file
                ungraph = marquage(ungraph, temp->ligne, temp->colonne);//on le marque
                ungraph->pSommet[temp->ligne][temp->colonne]->pred_L = departL;
                ungraph->pSommet[temp->ligne][temp->colonne]->pred_C = departC;//MAJ
            }
            temp = temp->arc_suivant;//on passe à l'arc suivant
        }
    }
    return connexe;
}

/// Procedure de djikstra pour controler les distances entre les differents element de la map
/*
    meme dijkstra que lors des TP adapte en matrice
*/
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

t_maillon* creerMaillon(int x)
{
    t_maillon* Nouv = (t_maillon*)malloc(sizeof(t_maillon));
    Nouv->nbr = x;
    Nouv->next = NULL;
    return Nouv;
}

t_maillon* creerFileDyna(int x)
{
    t_maillon* Nouv = (t_maillon*)malloc(sizeof(t_maillon));
    Nouv->next = NULL;
    Nouv->nbr = x;
    return Nouv;
}

Graphe* marquage(Graphe* ungraph, int smmtL, int smmtC)
{
    ungraph->pSommet[smmtL][smmtC]->couleur = 1;
    return ungraph;
}

//ajoute un element a la file
t_maillon* ajoutFileDyna(t_maillon* UneFile, t_maillon* Nouv)
{
    if(testFileDynaVide(UneFile) == 1)
        return Nouv;
    else
    {
        t_maillon* tpm = UneFile;
        while(tpm->next != NULL)
            tpm = tpm->next;
        tpm->next = Nouv;
        return UneFile;
    }
}

//suprimer un element
t_maillon* supFileDyna(t_maillon* UneFile, int* depile)
{
    if(testFileDynaVide(UneFile) == 1)
    {
        printf("File vide...\n");
        return UneFile;
    }
    else
    {
        t_maillon* tpm = UneFile->next;
        *depile = UneFile->nbr;
        free(UneFile);
        return tpm;
    }

}

//test si la file est vide
int testFileDynaVide(t_maillon* UneFile)
{
    if(UneFile == NULL)
        return 1;
    else
        return 0;
}

