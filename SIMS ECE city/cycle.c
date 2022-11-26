#include "header.h"

void modif_niveau_bat_communiste(t_ville* V, int i, int j)
{
    int* tab_hab = (int*)malloc( 5* sizeof(int));
    tab_hab[0] = 0;
    tab_hab[1] = 10;
    tab_hab[2] = 50;
    tab_hab[3] = 100;
    tab_hab[4] = 1000;
    int test = 0;
    if(V->tabcases[i][j].type == 4 && V->tabcases[i][j].niveau < 4 && V->tabcases[i][j].capa_eau == V->tabcases[i][j].nbr_hab && V->tabcases[i][j].capa_elec == V->tabcases[i][j].nbr_hab) /// autre condition d'amelioration
    {
        V->tabcases[i][j].niveau += 1;
        V->tabcases[i][j].nbr_hab = tab_hab[V->tabcases[i][j].niveau];
        V->tabcases[i][j].besoin_eau = tab_hab[V->tabcases[i][j].niveau];
        V->habitants = V->habitants + V->tabcases[i][j].nbr_hab - tab_hab[V->tabcases[i][j].niveau-1];
        test = 1;
    }
    if(V->tabcases[i][j].type == 4 && V->tabcases[i][j].niveau > 0 && (V->tabcases[i][j].capa_eau < V->tabcases[i][j].nbr_hab || V->tabcases[i][j].capa_elec < V->tabcases[i][j].nbr_hab) && test == 0)
    {
        if(V->tabcases[i][j].niveau == 0)
        {
            V->tabcases[i][j].ruine = 1;
        }
        V->tabcases[i][j].niveau -= 1;
        V->tabcases[i][j].nbr_hab = tab_hab[V->tabcases[i][j].niveau];
        V->habitants = V->habitants + V->tabcases[i][j].nbr_hab - tab_hab[V->tabcases[i][j].niveau+1];
    }
    free(tab_hab);
}

void modif_niveau_bat_capitaliste(t_ville* V, int i, int j)
{
    int* tab_hab = (int*)malloc( 5* sizeof(int));
    tab_hab[0] = 0;
    tab_hab[1] = 10;
    tab_hab[2] = 50;
    tab_hab[3] = 100;
    tab_hab[4] = 1000;
    if(V->tabcases[i][j].type == 4 && V->tabcases[i][j].niveau < 4) /// autre condition d'amelioration
    {
        V->tabcases[i][j].niveau += 1;
        V->tabcases[i][j].nbr_hab = tab_hab[V->tabcases[i][j].niveau];
        V->tabcases[i][j].besoin_eau = tab_hab[V->tabcases[i][j].niveau];
        V->habitants = V->habitants + V->tabcases[i][j].nbr_hab - tab_hab[V->tabcases[i][j].niveau-1];
    }
    free(tab_hab);
}

void fin_de_cycle(t_ville* V)
{
    int connexe = 0;
    for(int i= 0; i<60; i++)
    {
        for(int j=0; j<26; j++)
        {
            if(V->tabcases[i][j].type == 4)
            {
                time(&V->tabcases[i][j].fin);
                V->tabcases[i][j].temps = difftime(V->tabcases[i][j].fin, V->tabcases[i][j].debut) - V->tabcases[i][j].temps_save;
            }
            if(V->tabcases[i][j].temps == 1 && V->tabcases[i][j].type == 4)
            {
                aleatoire_feu(V,i,j);
            }
            if(V->tabcases[i][j].temps == 15 && V->tabcases[i][j].type == 4)
            {
                pompier(V,i,j);
            }
            if(V->tabcases[i][j].temps > 15 && V->tabcases[i][j].type == 4)
            {
                time(&V->tabcases[i][j].debut);
                V->argent = V->argent + (V->tabcases[i][j].nbr_hab * 10);
                V->circ_eau = init(V->circ_eau, i,j);
                connexe = BFS(V,V->circ_eau,i,j);
                if(connexe == 0)
                {
                    V->tabcases[i][j].niveau = 0;
                    V->tabcases[i][j].nbr_hab = 0;
                    if(V->tabcases[i][j].niveau == 0)
                    {
                        V->tabcases[i][j].ruine = 1;
                    }
                }
                else if(V->mode_de_jeu == 2)
                {
                    modif_niveau_bat_capitaliste(V, i,j);
                }
                else
                {
                    modif_niveau_bat_communiste(V, i, j);
                }
            }
        }
    }

}

