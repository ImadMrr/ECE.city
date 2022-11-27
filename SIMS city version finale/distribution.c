#include "header.h"

/// Procedure qui s'occupe de distribuer de l'eau dans la ville
/*
    on regarde dans 1er temps si une maison est bien connex donc pas isolé
    on lance un dijkstra depuis cette maison afin de déterminer la distance qui la sépare des autres sommets
    on retient cette distance
    puis parmis toutes les maisons ayant une distance inférieur a l'infini (donc qui ont trouvées une centrale)
    on cherche quelle est celle qui à la distance la plus courte
    enfin on relance un dijkstra depuis celle ci afin de trouver quelle est la centrale la plus proche pour y effectuer les transferts d'eau
*/

void dist_eau(t_ville* V)
{
    int arr_L, arr_C, restant, ind, deb_L, deb_C;
    for(int L = 0; L<60; L++)
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 4 && V->tabcases[L][C].connex == 1) // c'est une habitation
            {
                ind = 0;
                djikstra(V->circ_eau, L,C);
                minimum_eau(V, &arr_L, &arr_C);
                if(arr_L != -1)
                {
                    V->circ_eau->pSommet[L][C]->distance_fix = V->circ_eau->pSommet[arr_L][arr_C]->distance;
                }
                V->tabcases[L][C].vu = 0;
            }
        }
    }
    while(deb_L != -1)
    {
        minimum_D(V, &deb_L, &deb_C);
        if(deb_L != -1)
        {
            ind = 0;
            djikstra(V->circ_eau, deb_L,deb_C);
            while(V->tabcases[deb_L][deb_C].capa_eau != V->tabcases[deb_L][deb_C].nbr_hab && arr_L != -1)
            {
                minimum_eau(V, &arr_L, &arr_C);
                if(arr_L != -1)
                {
                    restant = V->tabcases[deb_L][deb_C].nbr_hab - V->tabcases[deb_L][deb_C].capa_eau;
                    if(V->tabcases[arr_L][arr_C].capa_eau - restant < 0)
                    {
                        V->tabcases[deb_L][deb_C].capa_eau += V->tabcases[arr_L][arr_C].capa_eau;
                        V->tabcases[deb_L][deb_C].tabeau[ind].valeur = V->tabcases[arr_L][arr_C].capa_eau;
                        V->tabcases[arr_L][arr_C].capa_eau = 0;
                    }
                    else
                    {
                        V->tabcases[deb_L][deb_C].capa_eau = V->tabcases[deb_L][deb_C].nbr_hab;
                        V->tabcases[deb_L][deb_C].tabeau[ind].valeur = restant;
                        V->tabcases[arr_L][arr_C].capa_eau -= restant;
                    }
                    V->tabcases[deb_L][deb_C].tabeau[ind].source_L = arr_L;
                    V->tabcases[deb_L][deb_C].tabeau[ind].source_C = arr_C;
                    V->tabcases[deb_L][deb_C].tabeau[ind].valid = 1;
                    coloration_chemin_eau(V, arr_L, arr_C);
                    ind += 1;

                    V->capa_eau = (V->num_chateau * 5000) - V->habitants; /// Calcul de la capacite restante de la ville
                }
            }
            V->tabcases[deb_L][deb_C].vu = 1;
        }
    }
}

/// Procedure qui s'occupe de distribuer de l'electricite dans la ville
/*
    meme principe que pour la distribution de l'eau sauf pour les calculs réalisé lorsque qu'on trouve la centrale
*/
void dist_elec(t_ville* V)
{
    int arr_L, arr_C, deb_L, deb_C;
    for(int L = 0; L<60; L++)
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 4 && V->tabcases[L][C].connex == 1) // c'est une habitation
            {
                V->tabcases[L][C].vu = 0;
                djikstra(V->circ_eau, L,C);
                minimum_elec(V, &arr_L, &arr_C, L, C);
                if(arr_L != -1)
                {
                    V->circ_eau->pSommet[L][C]->distance_fix = V->circ_eau->pSommet[arr_L][arr_C]->distance;
                }
            }
        }
    }
    do
    {
        minimum_D(V, &deb_L, &deb_C);
        if(deb_L != -1)
        {
            djikstra(V->circ_eau, deb_L,deb_C);
            while(V->tabcases[deb_L][deb_C].capa_elec != V->tabcases[deb_L][deb_C].nbr_hab && arr_L != -1)
            {
                minimum_elec(V, &arr_L, &arr_C, deb_L, deb_C);
                if(arr_L != -1)
                {
                    V->tabcases[deb_L][deb_C].capa_elec = V->tabcases[deb_L][deb_C].nbr_hab;
                    V->tabcases[arr_L][arr_C].capa_elec -= V->tabcases[deb_L][deb_C].nbr_hab;
                    V->tabcases[deb_L][deb_C].tabelec.valeur = V->tabcases[deb_L][deb_C].nbr_hab;
                    V->tabcases[deb_L][deb_C].tabelec.source_L = arr_L;
                    V->tabcases[deb_L][deb_C].tabelec.source_C = arr_C;
                    V->tabcases[deb_L][deb_C].tabelec.valid = 1;
                    coloration_chemin_elec(V, arr_L, arr_C);
                }

                V->capa_elec = (V->num_centrale * 5000) - V->habitants; /// Calcul de la capacite restante de la ville

            }
            V->tabcases[deb_L][deb_C].vu = 1;
        }
    }
    while(deb_L != -1);
}

/// Initialisation des variables utiles a la distribution de l'eau et de l'electricite dans la ville
void re_initialisation(t_ville* V)
{
    for(int i=0; i<60; i++)
    {
        for(int j=0; j<26; j++)
        {
            for(int u = 0; u<15 ; u++)
            {
                V->tabcases[i][j].tabeau[u].valeur = 0;
            }
            if(V->tabcases[i][j].type == 5)
            {
                V->tabcases[i][j].capa_eau = 5000;
            }
            if(V->tabcases[i][j].type == 6)
            {
                V->tabcases[i][j].capa_elec = 5000;
            }
            if(V->tabcases[i][j].type == 4)
            {
                V->tabcases[i][j].capa_eau = 0;
                V->tabcases[i][j].capa_elec = 0;
            }
            V->tabcases[i][j].c_eau = 0;
            V->tabcases[i][j].c_elec = 0;

        }
    }
}

/// Procedure qui regarde si un batiment peut etre protege par les pompiers
/*
    Procedure qui cherche à l'aide de dijkstra la caserne de pompier la plus proche
*/
void pompier(t_ville* V)
{
    int arr_L, arr_C;
    for(int L=0; L< 60; L++)
    {
        for(int C = 0; C< 26; C++)
        {
            if(V->tabcases[L][C].type == 4)
            {
                djikstra(V->circ_eau, L, C);
                minimum_pomp(V, &arr_L, &arr_C);
                if(arr_L != -1)
                {
                    if(V->circ_eau->pSommet[arr_L][arr_C]->distance <= 20)
                        V->tabcases[L][C].feu = 0;
                }
            }
        }
    }
}

/// Procedure qui met en feu un batiment aleatoirement
void aleatoire_feu(t_ville* V)
{
    int alea = 0;
    for(int L= 0; L< 60; L++)
    {
        for(int C = 0; C < 26; C++)
        {
            if(V->tabcases[L][C].type == 4)
            {
                alea = (rand()%100) +1;
                if(alea <= 30)
                    V->tabcases[L][C].feu = 1;
                else
                    V->tabcases[L][C].feu = 0;
            }
        }
    }
}
