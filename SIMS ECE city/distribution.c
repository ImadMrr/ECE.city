#include "header.h"

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

void affichage_info_distribution_eau(t_ville* V, int cliqueX, int cliqueY, BITMAP* fond)
{
    int ind = 0;
    int indice_ligne = 0;
    int indice_colonne = 0;
    int compteur = 0;
    if(mouse_b&2)
    {
        BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
        buffer = creation_buffer(V->tabcases);
        determination_indice(buffer, &indice_ligne,&indice_colonne,cliqueX,cliqueY);
        while(ind != 15)
        {
            if(V->tabcases[indice_ligne][indice_colonne].tabeau[ind].valid == 1)
            {
                textprintf_ex(fond, font, 200, 35 + compteur, makecol(255,255,255), -1, "Provenance : chateau d'eau numero %d - quantite : %d/%d",V->tabcases[V->tabcases[indice_ligne][indice_colonne].tabeau[ind].source_L][V->tabcases[indice_ligne][indice_colonne].tabeau[ind].source_C].num_chateau,V->tabcases[indice_ligne][indice_colonne].tabeau[ind].valeur, V->tabcases[indice_ligne][indice_colonne].nbr_hab  );
                compteur += 10;
            }
            ind += 1;
        }
        destroy_bitmap(buffer);
        if(V->tabcases[indice_ligne][indice_colonne].type == 5)
        {
            textprintf_ex(fond, font, 200, 40, makecol(255,255,255), -1, "Chateau d'eau numero %d", V->tabcases[indice_ligne][indice_colonne].num_chateau);
        }
    }
}

void affichage_info_distribution_elec(t_ville* V,int cliqueX,int  cliqueY, BITMAP* fond)
{
    int indice_ligne = 0;
    int indice_colonne = 0;
    int compteur = 0;
    if(mouse_b&2)
    {
        BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
        buffer = creation_buffer(V->tabcases);
        determination_indice(buffer, &indice_ligne,&indice_colonne,cliqueX,cliqueY);
        if(V->tabcases[indice_ligne][indice_colonne].tabelec.valid == 1)
        {
            textprintf_ex(fond, font, 200, 35 + compteur, makecol(255,255,255), -1, "Provenance : centrale electrique numero %d - quantite : %d/%d",V->tabcases[V->tabcases[indice_ligne][indice_colonne].tabelec.source_L][V->tabcases[indice_ligne][indice_colonne].tabelec.source_C].num_centrale,V->tabcases[indice_ligne][indice_colonne].tabelec.valeur, V->tabcases[indice_ligne][indice_colonne].nbr_hab);
            compteur += 10;
        }
        if(V->tabcases[indice_ligne][indice_colonne].type == 6)
        {
            textprintf_ex(fond, font, 200, 40, makecol(255,255,255), -1, "Centrale electrique numero %d", V->tabcases[indice_ligne][indice_colonne].num_centrale);
        }
        destroy_bitmap(buffer);
    }
}

void pompier(t_ville* V/*, int L, int C*/)
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
                    /*else
                        V->tabcases[L][C].feu = 1;*/
                }
                /*else
                    V->tabcases[L][C].feu = 1;*/
            }
        }
    }
}

void aleatoire_feu(t_ville* V/*, int L, int C*/)
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

