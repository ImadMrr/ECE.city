#include "header.h"

void dist_eau(t_ville* V)
{
    int arr_L, arr_C, compteur = 0, restant;
    for(int L = 0; L<60; L++)
    {
        for(int C = 0; C<26; C++)
        {
            if(V->tabcases[L][C].type == 4) // c'est une habitation
            {
                while(V->tabcases[L][C].capa_eau != V->tabcases[L][C].nbr_hab || compteur < V->nbr_c_eau)
                {
                    djikstra(V->circ_eau, L,C);
                    minimum_eau(V, &arr_L, &arr_C);
                    if(arr_L != -1)
                    {
                        restant = V->tabcases[L][C].nbr_hab - V->tabcases[L][C].capa_eau;
                        if(V->tabcases[arr_L][arr_C].capa_eau - restant < 0)
                        {
                            V->tabcases[L][C].capa_eau += V->tabcases[arr_L][arr_C].capa_eau;
                            V->tabcases[arr_L][arr_C].capa_eau = 0;
                        }
                        else
                        {
                            V->tabcases[L][C].capa_eau = V->tabcases[L][C].nbr_hab;
                            V->tabcases[arr_L][arr_C].capa_eau -= restant;
                        }
                    }
                    compteur += 1;
                    printf("%d capa centrale %d/%d\n", V->tabcases[arr_L][arr_C].capa_eau, arr_L, arr_C);
                }
                printf("%d\n", V->tabcases[L][C].capa_eau);
            }
            compteur = 0;
        }
    }

}
