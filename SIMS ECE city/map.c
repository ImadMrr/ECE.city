#include "header.h"

void afficher_map(t_ville* V, BITMAP* fond, int niveau)
{
    if(V->mode_de_jeu== 1)
    {
        textprintf_ex(fond, font, 30, 20, makecol(255,255,255),-1, "MODE COMMUNISTE");
    }
    if(V->mode_de_jeu == 2)
    {
        textprintf_ex(fond, font, 30, 20, makecol(255,255,255),-1, "MODE CAPITALISTE");
    }
    textprintf_ex(fond, font, 650, 20, makecol(255,255,255),-1, " VILLE DE : %s", V->nom);
    BITMAP* ground = NULL;
    BITMAP* eau = NULL;

    BITMAP* bat = NULL;
    BITMAP* bat2 = NULL;

    BITMAP* route1 = NULL;
    BITMAP* route2 = NULL;

    BITMAP* niv1 = NULL;
    BITMAP* niv2 = NULL;

    BITMAP* pause = load_bitmap("documents/bitmap/props/pause.bmp", NULL);
    BITMAP* argent = load_bitmap("documents/bitmap/props/argent.bmp", NULL);
    BITMAP* habitant = load_bitmap("documents/bitmap/props/habitant.bmp", NULL);
    BITMAP* capa_eau = load_bitmap("documents/bitmap/props/eau.bmp", NULL);
    BITMAP* capa_elec = load_bitmap("documents/bitmap/props/elec.bmp", NULL);
    capa_elec = lave_bitmap2(capa_elec);
    capa_eau = lave_bitmap2(capa_eau);
    argent = lave_bitmap2(argent);
    pause = lave_bitmap(pause);
    habitant = lave_bitmap2(habitant);

    draw_sprite(fond, argent, 40,50);
    textprintf_ex(fond, font, 80, 60, makecol(0,0,0),-1, "%d", V->argent);
    draw_sprite(fond, habitant, 40,80);
    textprintf_ex(fond, font, 80, 90, makecol(0,0,0),-1,"%d", V->habitants);
    draw_sprite(fond, capa_eau, 40,125);
    textprintf_ex(fond, font, 80, 135, makecol(0,0,0),-1,"%d", V->capa_eau);
    draw_sprite(fond, capa_elec, 38,155);
    textprintf_ex(fond, font, 80, 165, makecol(0,0,0),-1,"%d", V->capa_elec);

    draw_sprite(fond, pause, 1350,5);


    eau = load_bitmap("documents/bitmap/map/eau.bmp", NULL);

    if(niveau == 0)
    {
        ground = load_bitmap("documents/bitmap/map/herbe.bmp", NULL);

        bat = load_bitmap("documents/bitmap/map/bat2.bmp", NULL);
        bat = lave_bitmap2(bat);
        bat2 = load_bitmap("documents/bitmap/map/bat1.bmp", NULL);

        route1 = load_bitmap("documents/bitmap/map/route1.bmp", NULL);
        route2 = load_bitmap("documents/bitmap/map/route2.bmp", NULL);

        niv1 = load_bitmap("documents/bitmap/map/affiche1niv0.bmp", NULL);
        niv2 = load_bitmap("documents/bitmap/map/affiche2niv0.bmp", NULL);

        niv1 = lave_bitmap(niv1);
        niv2 = lave_bitmap(niv2);
        draw_sprite(fond, niv2,415,200 );
        draw_sprite(fond, niv1,330,140 );
    }

    if(niveau == -1)
    {
        ground = load_bitmap("documents/bitmap/map/niv-1.bmp", NULL);
        route1 = load_bitmap("documents/bitmap/map/eauniv1.bmp", NULL);
        route2 = load_bitmap("documents/bitmap/map/eauniv1.bmp", NULL);
        bat = load_bitmap("documents/bitmap/map/batsous-sol.bmp", NULL);

        niv2 = load_bitmap("documents/bitmap/map/affiche2niv1.bmp", NULL);

        niv2 = lave_bitmap(niv2);
        draw_sprite(fond, niv2,330,140 );
    }

    if(niveau == -2)
    {
        ground = load_bitmap("documents/bitmap/map/niv-2.bmp", NULL);
        route1 = load_bitmap("documents/bitmap/map/elec.bmp", NULL);
        route2 = load_bitmap("documents/bitmap/map/elec.bmp", NULL);
        bat = load_bitmap("documents/bitmap/map/batsous-sol.bmp", NULL);
    }


    for(int k=0; k<60; k++)
    {
        for(int m = 0; m<26; m++)
        {
            if(V->tabcases[k][m].type == 0)
            {
                draw_sprite(fond, ground, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 1)
            {
                draw_sprite(fond, eau, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
        }
    }
    for(int k=0; k<60; k++)
    {
        for(int m = 0; m<26; m++)
        {
            if(V->tabcases[k][m].type == 2)
            {
                draw_sprite(fond, route2, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 3)
            {
                draw_sprite(fond, route1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 4)
            {
                if(V->tabcases[k][m].niveau == 0)
                {
                    draw_sprite(fond, bat, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                }
                if(V->tabcases[k][m].niveau == 1)
                {
                    draw_sprite(fond, bat2, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                }
            }
        }
    }
    destroy_bitmap(ground);
    destroy_bitmap(eau);
    destroy_bitmap(route1);
    destroy_bitmap(route2);
    destroy_bitmap(bat);
    destroy_bitmap(bat2);
    destroy_bitmap(niv1);
    destroy_bitmap(niv2);
    destroy_bitmap(pause);
    destroy_bitmap(argent);
    destroy_bitmap(habitant);
}

void afficher_outil(t_cases* tablogo,t_cases** tabcasesMenu, BITMAP* fond)
{
    BITMAP* groundChoix = load_bitmap("documents/bitmap/map/fond outil2.bmp", NULL);
    BITMAP* logoBat1 = load_bitmap("documents/bitmap/map/logobat.bmp", NULL);

    BITMAP* route2 = load_bitmap("documents/bitmap/map/route2.bmp", NULL);

    BITMAP* route1 = load_bitmap("documents/bitmap/map/route1.bmp", NULL);
    BITMAP* croix = load_bitmap("documents/bitmap/map/croix.bmp", NULL);

    draw_sprite(fond,groundChoix, 20,40);
    ///Affichage du logo bat1:
    draw_sprite(fond, logoBat1, tablogo[0].colonne, tablogo[0].ligne);

    ///Affichage du logo bat2:
    draw_sprite(fond, route2, tablogo[1].colonne, tablogo[1].ligne);

    ///Affichage du logo route:
    draw_sprite(fond, route1, tablogo[2].colonne, tablogo[2].ligne);

    ///Affichage du logo croix:
    draw_sprite(fond, croix, tablogo[9].colonne, tablogo[9].ligne);

    destroy_bitmap(logoBat1);
    destroy_bitmap(route1);
    destroy_bitmap(route2);
    destroy_bitmap(croix);
}


void maps(int type)  /// 0 : nouvelle partie | 1 : partie charge
{
    t_ville* V = NULL;
    if(type == 0)
    {
        V = init_ville();
    }
    if(type == 1)
    {
        V = chargement_info_ville();
    }

    t_cases** tabcasesmenu = initialisation_outil();
    t_cases* tablogo = initialisation_tabLogo();

    BITMAP* fond = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP* fond2 = load_bitmap("documents/bitmap/fonds/fond logo.bmp", NULL);

    int niveau = 0;
    time_t start,end;
    time_t debut_cycle,fin_cycle;
    float temps;
    float temps_cycle;
    float temps_pause = 0;
    time(&start);
    int refSelect = -1;

    int fin = 0;
    time(&debut_cycle);
    while(fin == 0)
    {
        refSelect = -1;
        refSelect = cliqueChoixMenu(mouse_x,mouse_y,tablogo);
        time(&end);


        temps = difftime(end, start ) + V->temps - temps_pause;

        horloge(temps,fond2);

        draw_sprite(fond,fond2, 0,0);
        afficher_outil(tablogo,tabcasesmenu,fond);
        if(mouse_x > 1350 && mouse_x < 1390 && mouse_y > 5 && mouse_y < 45 && mouse_b&1)
        {
            menu_pause(V,&fin, temps,end, &temps_pause);
        }
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
        info_bat(V->tabcases,mouse_x,mouse_y,fond);
        afficher_map(V,fond,niveau);
        if(refSelect != -1 && niveau == 0)
        {
            if(refSelect != 10)
            {
                construction_map(V,fond, refSelect, start);
            }
            else
            {
                suppression(V,fond, start);
            }
        }
        blit(fond,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        clear_bitmap(fond);

        time(&fin_cycle);
        temps_cycle = difftime(fin_cycle, debut_cycle);
        if(temps_cycle == 15)
        {
            modification_niveau_bat(V);
            time(&debut_cycle);
        }
    }
    destroy_bitmap(fond2);
    destroy_bitmap(fond);
}
