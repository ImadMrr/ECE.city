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

    BITMAP* route1 = NULL;
    BITMAP* route2 = NULL;
    BITMAP* route3 = NULL;

    BITMAP* niv1 = NULL;
    BITMAP* niv2 = NULL;

    BITMAP* m0 = NULL;

    BITMAP* r0t1 = NULL;
    BITMAP* r0t2 = NULL;
    BITMAP* r0t3 = NULL;

    BITMAP* m1t1 = NULL;
    BITMAP* m1t2 = NULL;
    BITMAP* m1t3 = NULL;

    BITMAP* m2t1 = NULL;
    BITMAP* m2t2 = NULL;
    BITMAP* m2t3 = NULL;

    BITMAP* m3t1 = NULL;
    BITMAP* m3t2 = NULL;
    BITMAP* m3t3 = NULL;

    BITMAP* m4t1 = NULL;
    BITMAP* m4t2 = NULL;
    BITMAP* m4t3 = NULL;

    BITMAP* pompier = NULL;

    BITMAP* chateau = NULL;
    BITMAP* elec = NULL;

    BITMAP* pause = load_bitmap("documents/bitmap/props/pause.bmp", NULL);
    BITMAP* argent = load_bitmap("documents/bitmap/props/argent.bmp", NULL);
    BITMAP* habitant = load_bitmap("documents/bitmap/props/habitant.bmp", NULL);
    BITMAP* capa_eau = load_bitmap("documents/bitmap/props/eau.bmp", NULL);
    BITMAP* capa_elec = load_bitmap("documents/bitmap/props/elec.bmp", NULL);
    BITMAP* feu = load_bitmap("documents/bitmap/props/feu.bmp", NULL);
    BITMAP* pomp = load_bitmap("documents/bitmap/props/pompier.bmp", NULL);
    feu = lave_bitmap2(feu);
    pomp = lave_bitmap2(pomp);
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

        chateau = load_bitmap("documents/bitmap/map/chateau.bmp", NULL);
        chateau = lave_bitmap(chateau);

        route1 = load_bitmap("documents/bitmap/map/route1.bmp", NULL);
        route2 = load_bitmap("documents/bitmap/map/route2.bmp", NULL);
        route3 = load_bitmap("documents/bitmap/map/route3.bmp", NULL);

        niv1 = load_bitmap("documents/bitmap/map/affiche1niv0.bmp", NULL);
        niv2 = load_bitmap("documents/bitmap/map/affiche2niv0.bmp", NULL);

        elec = load_bitmap("documents/bitmap/map/centraleElec.bmp", NULL);
        elec = lave_bitmap2(elec);


        m0 = load_bitmap("documents/bitmap/map/n-0.bmp", NULL);
        m0 = lave_bitmap(m0);

        r0t1 = load_bitmap("documents/bitmap/map/r-1.1.bmp", NULL);
        r0t2 = load_bitmap("documents/bitmap/map/r-1.2.bmp", NULL);
        r0t3 = load_bitmap("documents/bitmap/map/r-1.3.bmp", NULL);

        m1t1 = load_bitmap("documents/bitmap/map/n-1.1.bmp", NULL);
        m1t2 = load_bitmap("documents/bitmap/map/n-1.2.bmp", NULL);
        m1t3 = load_bitmap("documents/bitmap/map/n-1.3.bmp", NULL);


        m2t1 = load_bitmap("documents/bitmap/map/n-2.1.bmp", NULL);
        m2t2 = load_bitmap("documents/bitmap/map/n-2.2.bmp", NULL);
        m2t3 = load_bitmap("documents/bitmap/map/n-2.3.bmp", NULL);

        m3t1 = load_bitmap("documents/bitmap/map/n-3.1.bmp", NULL);
        m3t2 = load_bitmap("documents/bitmap/map/n-3.2.bmp", NULL);
        m3t3 = load_bitmap("documents/bitmap/map/n-3.3.bmp", NULL);

        m4t1 = load_bitmap("documents/bitmap/map/n-4.1.bmp", NULL);
        m4t2 = load_bitmap("documents/bitmap/map/n-4.2.bmp", NULL);
        m4t3 = load_bitmap("documents/bitmap/map/n-4.3.bmp", NULL);

        m4t1 = lave_bitmap(m4t1);
        m4t2 = lave_bitmap(m4t2);
        m4t3 = lave_bitmap(m4t3);

        pompier = load_bitmap("documents/bitmap/map/pompier.bmp", NULL);
        pompier=lave_bitmap2(pompier);


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
        route3 = load_bitmap("documents/bitmap/map/eauniv1.bmp", NULL);
        bat = load_bitmap("documents/bitmap/map/batsous-sol.bmp", NULL);
        pompier = load_bitmap("documents/bitmap/map/batsous-sol.bmp", NULL);

        chateau = load_bitmap("documents/bitmap/map/chateausoussol.bmp", NULL);
        chateau = lave_bitmap2(chateau);
        elec = load_bitmap("documents/bitmap/map/chateausoussol.bmp", NULL);
        elec = lave_bitmap2(elec);

        niv2 = load_bitmap("documents/bitmap/map/affiche2niv1.bmp", NULL);

        niv2 = lave_bitmap(niv2);
        draw_sprite(fond, niv2,330,140 );
    }

    if(niveau == -2)
    {
        ground = load_bitmap("documents/bitmap/map/niv-2.bmp", NULL);
        route1 = load_bitmap("documents/bitmap/map/elec.bmp", NULL);
        route2 = load_bitmap("documents/bitmap/map/elec.bmp", NULL);
        route3 = load_bitmap("documents/bitmap/map/elec.bmp", NULL);
        bat = load_bitmap("documents/bitmap/map/batsous-sol.bmp", NULL);

        chateau = load_bitmap("documents/bitmap/map/chateausoussol.bmp", NULL);
        chateau = lave_bitmap2(chateau);
        elec = load_bitmap("documents/bitmap/map/chateausoussol.bmp", NULL);
        elec = lave_bitmap2(elec);
        pompier = load_bitmap("documents/bitmap/map/batsous-sol.bmp", NULL);
    }


    for(int k=0; k<60; k++)
    {
        for(int m = 0; m<26; m++)
        {
            if( V->tabcases[k][m].alea ==0 )
            {
                V->tabcases[k][m].alea =  rand() % (3 - 1 + 1) + 1;
            }

            if(V->tabcases[k][m].type == 0)
            {
                draw_sprite(fond, ground, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 1)
            {
                draw_sprite(fond, eau, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 2)
            {
                draw_sprite(fond, route2, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 3)
            {
                draw_sprite(fond, route1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            if(V->tabcases[k][m].type == 8)
            {
                draw_sprite(fond, route3, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne);
            }
            /*if(V->tabcases[k][m].feu == 1 && V->tabcases[k][m].protec == 1)
            {
                draw_sprite(fond, pomp, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne+50);
            }*/
        }
    }
    for(int k=0; k<60; k++)
    {
        for(int m = 0; m<26; m++)
        {
            if(V->tabcases[k][m].type == 4)
            {
                if(niveau == 0)
                {
                    ///------------------------NIVEAU 0 : TERRAIN VAGUE

                    if(V->tabcases[k][m].niveau == 0)
                    {
                        if(V->tabcases[k][m].ruine == 0)
                        {
                            draw_sprite(fond, m0, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-85);
                            //draw_sprite(fond, feu, V->tabcases[k][m].colonne-10, V->tabcases[k][m].ligne-40);
                        }
                        else
                        {
                            if(V->tabcases[k][m].alea == 1)
                            {
                                draw_sprite(fond, r0t1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-40);
                            }
                            if(V->tabcases[k][m].alea == 2)
                            {
                                draw_sprite(fond, r0t2, V->tabcases[k][m].colonne+8, V->tabcases[k][m].ligne-52);
                            }
                            if(V->tabcases[k][m].alea == 3)
                            {
                                draw_sprite(fond, r0t3, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-50);
                            }
                        }
                    }

                    ///---------------------------NIVEAU 1 : CABANE

                    if(V->tabcases[k][m].niveau == 1)
                    {
                        if(V->tabcases[k][m].alea == 1 )
                        {
                            draw_sprite(fond, m1t1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-40);
                        }
                        if(V->tabcases[k][m].alea == 2 )
                        {
                            draw_sprite(fond, m1t2, V->tabcases[k][m].colonne+8, V->tabcases[k][m].ligne-62);
                        }
                        if(V->tabcases[k][m].alea == 3 )
                        {
                            draw_sprite(fond, m1t3, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-50);
                        }
                    }

                    ///---------------------------NIVEAU 2 : MAISON

                    if(V->tabcases[k][m].niveau == 2)
                    {
                        if(V->tabcases[k][m].alea == 1 )
                        {
                            draw_sprite(fond, m2t1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-60);
                        }
                        if(V->tabcases[k][m].alea == 2 )
                        {
                            draw_sprite(fond, m2t2, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-75);
                        }
                        if(V->tabcases[k][m].alea == 3 )
                        {
                            draw_sprite(fond, m2t3, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);

                        }
                    }

                    ///---------------------------NIVEAU 3 : IMMEUBLE

                    if(V->tabcases[k][m].niveau == 3)
                    {
                        if(V->tabcases[k][m].alea == 1 )
                        {
                            draw_sprite(fond, m3t1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                        }
                        if(V->tabcases[k][m].alea == 2 )
                        {
                            draw_sprite(fond, m3t2, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                        }
                        if(V->tabcases[k][m].alea == 3 )
                        {
                            draw_sprite(fond, m3t3, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-90);
                        }
                    }

                    ///---------------------------NIVEAU 4 : GRATTE-CIEL

                    if(V->tabcases[k][m].niveau == 4)
                    {
                        if(V->tabcases[k][m].alea == 1 )
                        {
                            draw_sprite(fond, m4t1, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-140);
                        }
                        if(V->tabcases[k][m].alea == 2 )
                        {
                            draw_sprite(fond, m4t2, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-175);
                        }
                        if(V->tabcases[k][m].alea == 3 )
                        {
                            draw_sprite(fond, m4t3, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-130);
                        }
                    }
                    if(V->tabcases[k][m].feu == 1)
                    {
                        draw_sprite(fond, feu, V->tabcases[k][m].colonne-10, V->tabcases[k][m].ligne-40);
                    }

                }

                else
                {
                    draw_sprite(fond, bat, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                }

            }
            if(niveau == 0)
            {
                if(V->tabcases[k][m].type == 5)
                {
                    draw_sprite(fond, chateau,V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-44);
                }
                if(V->tabcases[k][m].type == 6)
                {
                    draw_sprite(fond, elec, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                }
                if(V->tabcases[k][m].type == 7)
                {
                    draw_sprite(fond, pompier, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-75);
                }
            }
            if(niveau == -1 || niveau == -2)
            {
                if(V->tabcases[k][m].type == 5)
                {
                    draw_sprite(fond, chateau,V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-110);
                }
                if(V->tabcases[k][m].type == 6)
                {
                    draw_sprite(fond, elec, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-110);
                }
                if(V->tabcases[k][m].type == 7)
                {
                    draw_sprite(fond, pompier, V->tabcases[k][m].colonne, V->tabcases[k][m].ligne-80);
                }
            }
        }
    }
    destroy_bitmap(ground);
    destroy_bitmap(eau);
    destroy_bitmap(route1);
    destroy_bitmap(route2);
    destroy_bitmap(bat);
    destroy_bitmap(niv1);
    destroy_bitmap(niv2);
    destroy_bitmap(pause);
    destroy_bitmap(argent);
    destroy_bitmap(habitant);
    destroy_bitmap(chateau);
}

void afficher_outil(t_cases* tablogo,t_cases** tabcasesMenu, BITMAP* fond)
{
    BITMAP* groundChoix = load_bitmap("documents/bitmap/map/fond outil2.bmp", NULL);
    BITMAP* logoBat1 = load_bitmap("documents/bitmap/map/logobat.bmp", NULL);
    logoBat1 = lave_bitmap2(logoBat1);

    BITMAP* route3 = load_bitmap("documents/bitmap/map/route3.bmp", NULL);


    BITMAP* logochat = load_bitmap("documents/bitmap/map/logochateau.bmp", NULL);
    logochat = lave_bitmap(logochat);

    BITMAP* logocentrale = load_bitmap("documents/bitmap/map/logoelec.bmp", NULL);
    logocentrale = lave_bitmap2(logocentrale);

    BITMAP* logopompier = load_bitmap("documents/bitmap/map/logopompier.bmp", NULL);
    logopompier = lave_bitmap2(logopompier);

    BITMAP* croix = load_bitmap("documents/bitmap/map/croix.bmp", NULL);

    draw_sprite(fond,groundChoix, 20,40);
    ///Affichage du logo bat1:
    draw_sprite(fond, logoBat1, tablogo[0].colonne, tablogo[0].ligne);

    ///Affichage du logo bat2:
    draw_sprite(fond, route3, tablogo[1].colonne, tablogo[1].ligne);

    ///Affichage du logo route:
    draw_sprite(fond, logochat, tablogo[2].colonne, tablogo[2].ligne);


    draw_sprite(fond, logocentrale, tablogo[3].colonne, tablogo[3].ligne);

    draw_sprite(fond, logopompier, tablogo[4].colonne, tablogo[4].ligne);

    draw_sprite(fond, croix, tablogo[5].colonne, tablogo[5].ligne);

    destroy_bitmap(logoBat1);
    destroy_bitmap(route3);
    destroy_bitmap(croix);
    destroy_bitmap(logocentrale);
    destroy_bitmap(logopompier);
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
    while(fin == 0)
    {
        refSelect = -1;
        refSelect = cliqueChoixMenu(mouse_x,mouse_y,tablogo);
        time(&end);

        fin_de_cycle(V,fond2);

        temps = difftime(end, start) + V->temps - temps_pause;

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
        cycle_feu(temps, V);
        printf("%d\n", (int)temps%15);
        afficher_map(V,fond,niveau);
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
        if(niveau == -1)
        {
            affichage_info_distribution_eau(V, mouse_x, mouse_y, fond);
        }
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
