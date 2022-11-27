#include "header.h"

/// Procedure qui affiche le nombre d'habitant et le niveau d'un batiment si clique droit
void info_bat(t_cases** tabcases,int clique_x,int clique_y, BITMAP* fond)
{

    int indiceligne,indicecolonne;

    ///Si clique droit :
    if(mouse_b&2)
    {
        BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
        buffer = creation_buffer(tabcases);
        determination_indice(buffer,&indiceligne,&indicecolonne,clique_x,clique_y);

        ///Vérification du type :
        if(tabcases[indiceligne][indicecolonne].type == 4)
        {
            textprintf_ex(fond, font, 200, 40,makecol(255,255,255),-1,"Habitant : %d", tabcases[indiceligne][indicecolonne].nbr_hab);
            textprintf_ex(fond, font, 200, 50,makecol(255,255,255),-1,"Niveau : %d", tabcases[indiceligne][indicecolonne].niveau);
        }
        destroy_bitmap(buffer);
    }
}

/// Procedure qui affiche la provenance de l'eau si clique droit sur une maison et le numero du chateau d'eau si clique droit dessus
void affichage_info_distribution_eau(t_ville* V, int cliqueX, int cliqueY, BITMAP* fond)
{
    int ind = 0;
    int indice_ligne = 0;
    int indice_colonne = 0;
    int compteur = 0;

    ///Si clique droit :
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

        ///Vérification du type :
        if(V->tabcases[indice_ligne][indice_colonne].type == 5)
        {
            textprintf_ex(fond, font, 200, 40, makecol(255,255,255), -1, "Chateau d'eau numero %d", V->tabcases[indice_ligne][indice_colonne].num_chateau);
        }
    }
}

/// Procedure qui affiche la provenance de l'electricite si clique droit sur une maison et le numero de la centrale electrique si clique droit dessus
void affichage_info_distribution_elec(t_ville* V,int cliqueX,int  cliqueY, BITMAP* fond)
{
    int indice_ligne = 0;
    int indice_colonne = 0;
    int compteur = 0;

    ///Vérification du type :
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

        ///Vérification du type :
        if(V->tabcases[indice_ligne][indice_colonne].type == 6)
        {
            textprintf_ex(fond, font, 200, 40, makecol(255,255,255), -1, "Centrale electrique numero %d", V->tabcases[indice_ligne][indice_colonne].num_centrale);
        }
        destroy_bitmap(buffer);
    }
}

/// Procedure qui affiche la bar a outil
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
    ///Affichage du logo bat:
    draw_sprite(fond, logoBat1, tablogo[0].colonne, tablogo[0].ligne);

    ///Affichage du logo route
    draw_sprite(fond, route3, tablogo[1].colonne, tablogo[1].ligne);

    ///Affichage du logo chateau d'eau
    draw_sprite(fond, logochat, tablogo[2].colonne, tablogo[2].ligne);

    ///Affichage du logo centrale élec :
    draw_sprite(fond, logocentrale, tablogo[3].colonne, tablogo[3].ligne);

    ///Affichage du logo pompier:
    draw_sprite(fond, logopompier, tablogo[4].colonne, tablogo[4].ligne);

    ///Affichage du logo croix:
    draw_sprite(fond, croix, tablogo[5].colonne, tablogo[5].ligne);

    destroy_bitmap(logoBat1);
    destroy_bitmap(route3);
    destroy_bitmap(croix);
    destroy_bitmap(logocentrale);
    destroy_bitmap(logopompier);
}

/// Procedure qui affiche la map en permanenece en temps reelle en fonction de ses differents parametre
void afficher_map(t_ville* V, BITMAP* fond, int niveau)
{
    // en fonction du mode
    if(V->mode_de_jeu== 1)
    {
        textprintf_ex(fond, font, 30, 20, makecol(255,255,255),-1, "MODE COMMUNISTE");
    }
    if(V->mode_de_jeu == 2)
    {
        textprintf_ex(fond, font, 30, 20, makecol(255,255,255),-1, "MODE CAPITALISTE");
    }
    textprintf_ex(fond, font, 650, 20, makecol(255,255,255),-1, " VILLE DE : %s", V->nom);

    /// INITIALISATION DE TOUT LES BITMAPS ----------------------------------------------------------------------------///
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


    // affichage des infos globale de la ville
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

    /// CHARGEMENT DES BITMAPS EN FONCTION DU NIVEAU DE SOL ---------------------------------------------------///
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


    /// Premier parcours de la matrice pour afficher le sol
    for(int k=0; k<60; k++)
    {
        for(int m = 0; m<26; m++)
        {
            if( V->tabcases[k][m].alea ==0 )
            {
                ///Aléatoire qui définit la BITMAP qu'on affichera
                V->tabcases[k][m].alea =  rand() % (3 - 1 + 1) + 1;
            }

            ///Affichage ddes BITMPAS selon le type :
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
        }
    }
    /// Deuxieme parcours de la matrice pour afficher les batiments qui passent au dessus du sol
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

                    ///Selon la valeur de l'aléatoire afficher une BITMAP différentes
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

                    ///Selon la valeur de l'aléatoire afficher une BITMAP différentes
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

                    ///Selon la valeur de l'aléatoire afficher une BITMAP différentes
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

                    ///Selon la valeur de l'aléatoire afficher une BITMAP différentes
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

