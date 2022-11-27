#include "header.h"

/// Procedure qui gere la totalite du jeu avec une boucle infini
void maps(int type)  /// 0 : nouvelle partie | 1 : partie charge
{
    t_ville* V = NULL;
    if(type == 0)
    {
        V = init_ville(); /// initialisation des variables
    }
    if(type == 1)
    {
        V = chargement_info_ville(); /// recuperation des anciennes variables
        V = lire_graphe(V);
    }

    t_cases** tabcasesmenu = initialisation_outil();
    t_cases* tablogo = initialisation_tabLogo();

    BITMAP* fond = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP* fond2 = load_bitmap("documents/bitmap/fonds/fond logo.bmp", NULL);

    int niveau = 0;
    time_t start,end;
    float temps;
    float temps_pause = 0;
    time(&start);
    int refSelect = -1;

    int fin = 0;

    ///Boucle de jeu infinis :
    while(fin == 0)
    {
        ///La variable refSlect contient le type de l'objet sélectionné : si = -1 rien selectionné
        refSelect = -1;
        refSelect = cliqueChoixMenu(mouse_x,mouse_y,tablogo);
        time(&end);

        ///Gestion du temps et des cycles :
        fin_de_cycle(V,fond2);

        ///Gestion du temps :
        temps = difftime(end, start) + V->temps - temps_pause;

        ///Affichages de l'horloge :
        horloge(temps,fond2);

        draw_sprite(fond,fond2, 0,0);
        ///Affichage de la barre à outils :
        afficher_outil(tablogo,tabcasesmenu,fond);

        /// Si clique sur pause :
        if(mouse_x > 1350 && mouse_x < 1390 && mouse_y > 5 && mouse_y < 45 && mouse_b&1)
        {
            menu_pause(V,&fin, temps,end, &temps_pause);
        }

        ///gestion des types avec les boutons 1,2 et 3 :
        if(key[KEY_0_PAD])
        {
            niveau = 0;
        }
        if(key[KEY_1_PAD])
        {
            niveau = -1;
        }
        if(key[KEY_2_PAD])
        {
            niveau = -2;
        }
        ///Gestion du cycle de feu :
        cycle_feu(temps, V);

        ///Affichage de la map :
        afficher_map(V,fond,niveau);

        ///Si on est au niveau0 :
        if(niveau == 0)
        {
            info_bat(V->tabcases,mouse_x,mouse_y,fond);
            if(refSelect != -1)
            {
                if(refSelect != 10)
                {
                    construction_map(V,fond, refSelect, start);
                }
                else
                {
                    suppression(V,fond, start);
                }
                V = lire_graphe(V);
            }
        }

        ///Si on est au niveau-1 :
        if(niveau == -1)
        {
            affichage_info_distribution_eau(V, mouse_x, mouse_y, fond);
        }

        ///Si on est au niveau-2 :
        if(niveau == -2)
        {
            affichage_info_distribution_elec(V, mouse_x,mouse_y,fond);
        }
        re_initialisation(V);
        dist_eau(V);
        dist_elec(V);
        blit(fond,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        clear_bitmap(fond);
    }
    destroy_bitmap(fond2);
    destroy_bitmap(fond);
}

/// Procedure qui lance le jeu
void jeu()
{
    initialisation();
    srand(time(NULL));
    musique();
    logo();
    menu_principal();
}
