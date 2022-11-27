#include "header.h"

/// Modification du niveau des batiments conforme au mode communiste
void modif_niveau_bat_communiste(t_ville* V, int i, int j)
{
    int* tab_hab = (int*)malloc( 5* sizeof(int));
    tab_hab[0] = 0;
    tab_hab[1] = 10;
    tab_hab[2] = 50;
    tab_hab[3] = 100;
    tab_hab[4] = 1000;
    int test = 0;
    // amelioration
    if(V->tabcases[i][j].type == 4 && V->tabcases[i][j].niveau < 4 && V->tabcases[i][j].capa_eau == V->tabcases[i][j].nbr_hab && V->tabcases[i][j].capa_elec == V->tabcases[i][j].nbr_hab) /// autre condition d'amelioration
    {
        V->tabcases[i][j].niveau += 1;
        V->tabcases[i][j].nbr_hab = tab_hab[V->tabcases[i][j].niveau];
        V->habitants = V->habitants + V->tabcases[i][j].nbr_hab - tab_hab[V->tabcases[i][j].niveau-1];
        test = 1;
    }
    // regression
    if(V->tabcases[i][j].type == 4 && V->tabcases[i][j].niveau > 0 && (V->tabcases[i][j].capa_eau < V->tabcases[i][j].nbr_hab || V->tabcases[i][j].capa_elec < V->tabcases[i][j].nbr_hab) && test == 0)
    {
        if(V->tabcases[i][j].niveau == 0)
        {
            V->tabcases[i][j].ruine = 1; // gestion des ruines
        }
        V->tabcases[i][j].niveau -= 1;
        V->tabcases[i][j].nbr_hab = tab_hab[V->tabcases[i][j].niveau];
        V->habitants = V->habitants + V->tabcases[i][j].nbr_hab - tab_hab[V->tabcases[i][j].niveau+1];
    }
    free(tab_hab);
}

/// Modification du niveau des batiments conforme au mode capitaliste
void modif_niveau_bat_capitaliste(t_ville* V, int i, int j)
{
    int* tab_hab = (int*)malloc( 5* sizeof(int));
    tab_hab[0] = 0;
    tab_hab[1] = 10;
    tab_hab[2] = 50;
    tab_hab[3] = 100;
    tab_hab[4] = 1000;
    // amelioration
    if(V->tabcases[i][j].type == 4 && V->tabcases[i][j].niveau < 4) /// autre condition d'amelioration
    {
        V->tabcases[i][j].niveau += 1;
        V->tabcases[i][j].nbr_hab = tab_hab[V->tabcases[i][j].niveau];
        V->habitants = V->habitants + V->tabcases[i][j].nbr_hab - tab_hab[V->tabcases[i][j].niveau-1];
    }
    free(tab_hab);
}

/// Procedure qui controle les fins de cycle de chaque batiment et agis en consequence
void fin_de_cycle(t_ville* V, BITMAP* fond)
{
    int connexe = 0;
    for(int i= 0; i<60; i++)
    {
        for(int j=0; j<26; j++)
        {
            if(V->tabcases[i][j].type == 4)
            {
                // gestion du temps
                time(&V->tabcases[i][j].fin);
                V->tabcases[i][j].temps = difftime(V->tabcases[i][j].fin, V->tabcases[i][j].debut) - V->tabcases[i][j].temps_save;
            }
            if(V->tabcases[i][j].temps > 15 && V->tabcases[i][j].type == 4)
            {
                time(&V->tabcases[i][j].debut); // re-initialisation du temps
                V->argent = V->argent + (V->tabcases[i][j].nbr_hab * 10);
                V->circ_eau = init(V->circ_eau, i,j);
                connexe = BFS(V,V->circ_eau,i,j);
                V->tabcases[i][j].connex = connexe;
                if(connexe == 0) // si connexe a une route
                {
                    V->tabcases[i][j].niveau = 0;
                    ///
                    V->habitants = V->habitants - V->tabcases[i][j].nbr_hab;
                    ///
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

/// Procedure qui controle la fin de cycle des cycle de feu et agis en consequence
void cycle_feu(float temps, t_ville* V)
{
    int repet = 0;
    if((int)temps%15 == 0 && repet == 0)
    {
        repet = 1;
        aleatoire_feu(V); // mise en feu
        pompier(V);
    }
    if((int)temps%15 == 14)
    {
        pompier(V); // protection ou non
        controle_feu(V);
    }
}

/// Procedure qui incremente la variable feu si besoin
void controle_feu(t_ville* V)
{
    for(int L= 0; L<60; L++)
    {
        for(int C = 0; C < 26; C++)
        {
            if(V->tabcases[L][C].type == 4)
            {
                if(V->tabcases[L][C].feu == 1)
                {
                    V->tabcases[L][C].niveau = 0;
                    V->tabcases[L][C].ruine = 1;
                    ///
                    V->habitants = V->habitants - V->tabcases[L][C].nbr_hab;
                    V->tabcases[L][C].nbr_hab = 0;
                    ///
                }
            }
        }
    }
}
