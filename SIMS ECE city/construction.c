#include "header.h"

///Si un objets est séléctionné dans la barre de menu et retorun l'objet la référence de l'objet du menu séléctionné
int cliqueChoixMenu( int cliqueX, int cliqueY, t_cases* logo  )
{
    if(mouse_b&1)
    {
        for( int i=0 ; i < 10 ; i++ )
        {
            if( ( cliqueX >= logo[i].colonne && cliqueX <= logo[i].colonne+40 ) && ( cliqueY >= logo[i].ligne && cliqueY <= logo[i].ligne+40 ) )
            {
                for( int k=0 ; k < 10 ; k++ )
                {
                    if( logo[k].colonne == logo[i].colonne && logo[k].ligne == logo[i].ligne )
                        return logo[k].type;
                }
            }
        }
    }
    return -1;
}

void champPorte(BITMAP* buffer, int cliqueX, int cliqueY, BITMAP* fond, int refSelect, t_cases** tabcases )
{
    int pixel = 0;
    int indiceligne = 0;
    int indicecolonne = 0;
    int autor = 1;
    int lim = 0;

    determination_indice(buffer,&indiceligne,&indicecolonne,cliqueX,cliqueY);

    if(refSelect == 4)
    {
        if(cliqueX > 800)
        {
            pixel = getpixel(buffer, cliqueX+80, cliqueY);
        }
        if(cliqueY < 500)
        {
            pixel = getpixel(buffer, cliqueX, cliqueY-20);
        }
        if(cliqueY > 500)
        {
            pixel = getpixel(buffer, cliqueX, cliqueY+20);
        }
        if(cliqueX > 800 && cliqueY < 500)
        {
            pixel = getpixel(buffer, cliqueX+80, cliqueY-20);
        }
        if(cliqueX > 800 && cliqueY > 500)
        {
            pixel = getpixel(buffer, cliqueX+80, cliqueY+20);
        }

    }
    else if(refSelect == 5 || refSelect == 6)
    {
        if(indicecolonne%2 == 0)
        {
            lim = 20;
        }
        else
        {
            lim = 40;
        }
        if(cliqueX > 800)
        {
            pixel = getpixel(buffer, cliqueX+120, cliqueY);
        }
        if(cliqueY < 500)
        {
            pixel = getpixel(buffer, cliqueX, cliqueY-lim);
        }
        if(cliqueY > 500)
        {
            pixel = getpixel(buffer, cliqueX, cliqueY+lim);
        }
        if(cliqueX > 800 && cliqueY < 500)
        {
            pixel = getpixel(buffer, cliqueX+120, cliqueY-lim);
        }
        if(cliqueX > 800 && cliqueY > 500)
        {
            pixel = getpixel(buffer, cliqueX+120, cliqueY+lim);
        }
    }
    else
    {
        pixel = getpixel(buffer, cliqueX, cliqueY);
    }
    int vert = getg(pixel);

    int couleur = 0;
    if(vert == 200 && tabcases[indiceligne][indicecolonne].type == 0)
    {
        if(refSelect != 4)
        {
            couleur = makecol(0,255,0);
        }
        else
        {
            //verif_placement_bat(tabcases,indiceligne,indicecolonne,&autor);
            if(autor == 1)
            {
                couleur = makecol(0,255,0);
            }
            else
            {
                couleur = makecol(255,0,0);
            }
        }
    }
    else
    {
        couleur = makecol(255,0,0);
    }

    circle(fond, mouse_x, mouse_y,5, couleur);
}

void suppression(t_ville* V, BITMAP* fond, time_t start)
{
    int indiceligne = 0;
    int indicecolonne = 0;
    int stop = 0;
    int autor = 0;

    time_t end;
    float temps;

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    buffer = creation_buffer(V->tabcases);

    BITMAP* poubelle = load_bitmap("documents/bitmap/props/poubelle.bmp", NULL);
    BITMAP* curseur = load_bitmap("documents/bitmap/map/curseur.bmp", NULL);
    curseur = lave_bitmap2(curseur);
    poubelle = lave_bitmap(poubelle);
    poubelle = blanc_devient_noir(poubelle);

    BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);

    while(stop == 0)
    {

        time(&end);
        temps = difftime(end,start);

        blit(fond, buf, 0,0,0,0,SCREEN_W, SCREEN_H);
        horloge(temps,buf);

        draw_sprite(buf, poubelle,110,475 );
        draw_sprite(buf,curseur, mouse_x-10, mouse_y-10);
        blit(buf, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        clear_bitmap(buf);

        if(mouse_b&1)
        {
            if( mouse_x >= 110 && mouse_x <= 150 && mouse_y >= 475 && mouse_y <= 527 )
            {
                stop = 1;
            }
            int pixel = 0;
            int g = 0;
            pixel = getpixel(buffer, mouse_x, mouse_y);

            g= getg(pixel);
            if(g == 200)
            {
                autor = 1;
            }
            if(autor == 1)
            {
                determination_indice(buffer,&indiceligne,&indicecolonne,mouse_x,mouse_y);
                if(V->tabcases[indiceligne][indicecolonne].type != 0)
                {
                    if(V->tabcases[indiceligne][indicecolonne].type == 4)
                    {
                        V->argent = V->argent -1200;
                        ecriture_case_maisons(V->tabcases,indiceligne,indicecolonne,0);
                    }
                    if(V->tabcases[indiceligne][indicecolonne].type == 1)
                    {
                        V->argent = V->argent - 100;
                    }
                    if(V->tabcases[indiceligne][indicecolonne].type == 2 || V->tabcases[indiceligne][indicecolonne].type == 3)
                    {
                        V->argent = V->argent - 20;
                    }
                    if(V->tabcases[indiceligne][indicecolonne].type == 5)
                    {
                        ecriture_case_centrale(V->tabcases, indiceligne, indicecolonne, 0);
                        V->capa_eau = V->capa_eau - V->tabcases[indiceligne][indicecolonne].capa_eau;
                        V->tabcases[indiceligne][indicecolonne].capa_eau = 0;
                    }
                    if(V->tabcases[indiceligne][indicecolonne].type == 6)
                    {
                        ecriture_case_centrale(V->tabcases, indiceligne, indicecolonne, 0);
                        V->capa_elec = V->capa_elec - V->tabcases[indiceligne][indicecolonne].capa_elec;
                        V->tabcases[indiceligne][indicecolonne].capa_elec = 0;
                    }
                    if(V->tabcases[indiceligne][indicecolonne].type == 7)
                    {
                        ecriture_case_maisons(V->tabcases, indiceligne,indicecolonne,0);
                    }
                    V->tabcases[indiceligne][indicecolonne].type = 0;
                }
                stop = 1;
            }
        }
    }
}

void construction_map(t_ville* V, BITMAP* fond, int refSlect, time_t start )
{
    int autor=0;

    int indiceligne, indicecolonne;
    int stop = 0;
    int lim = 0;

    time_t end;
    float temps;

    BITMAP* bat1 = load_bitmap("documents/bitmap/map/n-0.bmp", NULL);
    bat1 = lave_bitmap(bat1);

    BITMAP* route2 = load_bitmap("documents/bitmap/map/route2.bmp", NULL);
    BITMAP* route1 = load_bitmap("documents/bitmap/map/route1.bmp", NULL);
    BITMAP* chateau = load_bitmap("documents/bitmap/map/chateau.bmp", NULL);
    BITMAP* pompier = load_bitmap("documents/bitmap/map/pompier.bmp", NULL);
    BITMAP* elec = load_bitmap("documents/bitmap/map/centraleElec.bmp", NULL);
    elec = lave_bitmap2(elec);
    pompier = lave_bitmap2(pompier);
    chateau = lave_bitmap(chateau);

    BITMAP* poubelle = load_bitmap("documents/bitmap/props/poubelle.bmp", NULL);
    poubelle = lave_bitmap(poubelle);
    poubelle = blanc_devient_noir(poubelle);

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    buffer = creation_buffer(V->tabcases);

    BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);


    while(stop == 0)
    {
        time(&end);
        temps = difftime(end,start);

        blit(fond, buf, 0,0,0,0,SCREEN_W, SCREEN_H);

        horloge(temps,buf);

        draw_sprite(buf, poubelle,110,475 );

        if( refSlect != 10 )
        {

            if( refSlect == 4)
            {
                draw_sprite(buf, bat1, mouse_x-10, mouse_y-95);
                champPorte( buffer, mouse_x, mouse_y,buf,refSlect,V->tabcases );
            }

            if( refSlect == 2)
            {
                draw_sprite(buf, route2, mouse_x-10, mouse_y-10);
                champPorte( buffer, mouse_x, mouse_y, buf,refSlect,V->tabcases );
            }

            if( refSlect == 3)
            {
                draw_sprite(buf, route1, mouse_x-10, mouse_y-10);
                champPorte( buffer, mouse_x, mouse_y, buf,refSlect,V->tabcases );
            }
            if(refSlect == 5)
            {
                draw_sprite(buf, chateau, mouse_x-10, mouse_y-50);
                champPorte(buffer, mouse_x,mouse_y, buf,refSlect,V->tabcases);
            }
            if(refSlect == 6)
            {
                draw_sprite(buf, elec, mouse_x-10, mouse_y-97);
                champPorte(buffer, mouse_x,mouse_y, buf,refSlect,V->tabcases);
            }
            if(refSlect == 7)
            {
                draw_sprite(buf, pompier, mouse_x, mouse_y - 90);
                champPorte(buffer, mouse_x, mouse_y, buf,refSlect,V->tabcases);
            }
            blit(buf, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
            clear_bitmap(buf);

            if( (mouse_b & 1)  )
            {
                if( mouse_x >= 110 && mouse_x <= 150 && mouse_y >= 475 && mouse_y <= 527 )
                {
                    stop = 1;
                }
                int pixel = 0;
                int g = 0;
                if(refSlect == 4 || refSlect == 7)
                {
                    if(mouse_x > 800)
                    {
                        pixel = getpixel(buffer, mouse_x+80, mouse_y);
                    }
                    if(mouse_y < 500)
                    {
                        pixel = getpixel(buffer, mouse_x, mouse_y-20);
                    }
                    if(mouse_y > 500)
                    {
                        pixel = getpixel(buffer, mouse_x, mouse_y+20);
                    }
                    if(mouse_x > 800 && mouse_y < 500)
                    {
                        pixel = getpixel(buffer, mouse_x+80, mouse_y-20);
                    }
                    if(mouse_x > 800 && mouse_y > 500)
                    {
                        pixel = getpixel(buffer, mouse_x+80, mouse_y+20);
                    }

                }
                else if(refSlect == 5 || refSlect == 6)
                {
                    if(indicecolonne%2 == 0)
                    {
                        lim = 20;
                    }
                    else
                    {
                        lim = 40;
                    }
                    if(mouse_x > 800)
                    {
                        pixel = getpixel(buffer, mouse_x+120, mouse_y);
                    }
                    if(mouse_y < 500)
                    {
                        pixel = getpixel(buffer, mouse_x, mouse_y-lim);
                    }
                    if(mouse_y > 500)
                    {
                        pixel = getpixel(buffer, mouse_x, mouse_y+lim);
                    }
                    if(mouse_x > 800 && mouse_y < 500)
                    {
                        pixel = getpixel(buffer, mouse_x+120, mouse_y-lim);
                    }
                    if(mouse_x > 800 && mouse_y > 500)
                    {
                        pixel = getpixel(buffer, mouse_x+120, mouse_y+lim);
                    }
                }
                else
                {
                    pixel = getpixel(buffer, mouse_x, mouse_y);
                }

                g= getg(pixel);

                determination_indice(buffer,&indiceligne,&indicecolonne,mouse_x,mouse_y);


                if(g == 200 && V->tabcases[indiceligne][indicecolonne].type == 0)
                {
                    if(  refSlect == 2 )
                    {
                        V->tabcases[indiceligne][indicecolonne].type = 2;
                        V->argent = V->argent - 10;
                        draw_sprite(fond, route2,V->tabcases[indiceligne][indicecolonne].colonne,V->tabcases[indiceligne][indicecolonne].ligne );
                    }
                    if(  refSlect == 3 )
                    {
                        V->tabcases[indiceligne][indicecolonne].type = 3;
                        V->argent = V->argent - 10;
                        draw_sprite(fond,route1, V->tabcases[indiceligne][indicecolonne].colonne, V->tabcases[indiceligne][indicecolonne].ligne);
                    }
                    else if(refSlect == 4 || refSlect == 7)
                    {
                        verif_placement_bat(V->tabcases,indiceligne,indicecolonne,&autor);
                    }
                    else
                    {
                        verif_placement_centrale(V->tabcases,indiceligne,indicecolonne, &autor);
                    }
                }
            }
            if( autor == 1 )
            {
                if(  refSlect == 4 )
                {
                    V->tabcases[indiceligne][indicecolonne].type = 4;
                    V->tabcases[indiceligne][indicecolonne].niveau = 0;
                    time(&V->tabcases[indiceligne][indicecolonne].debut);
                    ecriture_case_maisons(V->tabcases,indiceligne,indicecolonne,9);
                    V->argent = V->argent - 1000;
                }
                if(refSlect == 5)
                {
                    V->tabcases[indiceligne][indicecolonne].type = 5;
                    ecriture_case_centrale(V->tabcases,indiceligne,indicecolonne,9);
                    V->tabcases[indiceligne][indicecolonne].capa_eau = 5000;
                    V->capa_eau = V->capa_eau + V->tabcases[indiceligne][indicecolonne].capa_eau;
                    V->argent = V->argent - 100000;
                    V->tabcases[indiceligne][indicecolonne].num_chateau  = V->num_chateau + 1;
                    V->num_chateau += 1;
                }
                if(refSlect == 6)
                {
                    V->tabcases[indiceligne][indicecolonne].type = 6;
                    ecriture_case_centrale(V->tabcases,indiceligne,indicecolonne,9);
                    V->tabcases[indiceligne][indicecolonne].capa_elec = 5000;
                    V->capa_elec = V->capa_elec + V->tabcases[indiceligne][indicecolonne].capa_elec;
                    V->argent = V->argent - 100000;
                    V->tabcases[indiceligne][indicecolonne].num_centrale  = V->num_centrale + 1;
                    V->num_centrale += 1;
                }
                if(refSlect == 7)
                {
                    V->tabcases[indiceligne][indicecolonne].type = 7;
                    ecriture_case_maisons(V->tabcases,indiceligne,indicecolonne,9);
                    V->argent = V->argent - 50000;
                }

                stop = 1;

                /// On réinitialise toutes les autorisations :
                autor=0;
                refSlect=-1;
            }
        }
    }

}

void determination_indice(BITMAP* buffer, int* indiceligne, int* indicecolonne, int cliqueX, int cliqueY)
{
    int pixel = 0;
    pixel = getpixel(buffer, cliqueX, cliqueY);
    *indiceligne = getb(pixel);
    *indicecolonne = getr(pixel);
}

void ecriture_case_maisons(t_cases** tabcases, int indiceligne, int indicecolonne,int type)
{
    tabcases[indiceligne][indicecolonne+1].type = type;
    tabcases[indiceligne][indicecolonne+2].type = type;

    if(indiceligne%2 == 0)
    {
        tabcases[indiceligne+1][indicecolonne].type = type;
        tabcases[indiceligne+1][indicecolonne+1].type = type;

        tabcases[indiceligne-1][indicecolonne].type = type;
        tabcases[indiceligne-1][indicecolonne+1].type = type;
    }
    else
    {
        tabcases[indiceligne+1][indicecolonne+1].type = type;
        tabcases[indiceligne+1][indicecolonne+2].type = type;

        tabcases[indiceligne-1][indicecolonne+1].type = type;
        tabcases[indiceligne-1][indicecolonne+2].type = type;
    }

    tabcases[indiceligne+2][indicecolonne+1].type = type;
    tabcases[indiceligne-2][indicecolonne+1].type = type;
}

void verif_placement_bat(t_cases** tabcases, int indiceligne,int indicecolonne, int* autor)
{
    if(tabcases[indiceligne][indicecolonne].type == 0)
    {
        if(tabcases[indiceligne][indicecolonne+1].type == 0 && tabcases[indiceligne][indicecolonne+2].type == 0)
        {
            if(tabcases[indiceligne+2][indicecolonne+1].type == 0 && tabcases[indiceligne-2][indicecolonne+1].type == 0)
            {
                if(indiceligne%2 == 0)
                {
                    if(tabcases[indiceligne+1][indicecolonne].type == 0 && tabcases[indiceligne+1][indicecolonne+1].type == 0 && tabcases[indiceligne-1][indicecolonne].type == 0 && tabcases[indiceligne-1][indicecolonne+1].type == 0)
                    {
                        *autor = 1;
                    }
                    else
                    {
                        *autor = 0;
                    }
                }
                else
                {
                    if(tabcases[indiceligne+1][indicecolonne+1].type == 0 && tabcases[indiceligne+1][indicecolonne+2].type == 0 && tabcases[indiceligne-1][indicecolonne+1].type == 0 && tabcases[indiceligne-1][indicecolonne+2].type == 0)
                    {
                        *autor = 1;
                    }
                    else
                    {
                        *autor = 0;
                    }
                }
            }
            else
            {
                *autor = 0;
            }
        }
        else
        {
            *autor = 0;
        }
    }
    else
    {
        *autor = 0;
    }
}

void verif_placement_centrale(t_cases** tabcases, int indiceligne, int indicecolonne, int* autor)
{
    if(tabcases[indiceligne][indicecolonne].type == 0)
    {
        if(tabcases[indiceligne][indicecolonne+1].type == 0 && tabcases[indiceligne][indicecolonne+2].type == 0 && tabcases[indiceligne][indicecolonne+3].type == 0)
        {
            if(indiceligne%2 == 0)
            {
                if(tabcases[indiceligne-1][indicecolonne].type == 0 && tabcases[indiceligne-1][indicecolonne+1].type == 0 && tabcases[indiceligne-1][indicecolonne+2].type == 0 && tabcases[indiceligne+1][indicecolonne].type == 0 && tabcases[indiceligne+1][indicecolonne+1].type == 0 && tabcases[indiceligne+1][indicecolonne+2].type == 0)
                {
                    if(tabcases[indiceligne-2][indicecolonne+1].type == 0 && tabcases[indiceligne-2][indicecolonne+2].type == 0 && tabcases[indiceligne+2][indicecolonne+1].type == 0 && tabcases[indiceligne+2][indicecolonne+2].type == 0 )
                    {
                        if(tabcases[indiceligne-3][indicecolonne+1].type == 0 && tabcases[indiceligne+3][indicecolonne+1].type == 0)
                        {
                            *autor = 1;
                        }
                        else
                        {
                            *autor = 0;
                        }
                    }
                    else
                    {
                        *autor = 0;
                    }
                }
                else
                {
                    *autor = 0;
                }
            }
            else
            {
                if(tabcases[indiceligne-1][indicecolonne+1].type == 0 && tabcases[indiceligne-1][indicecolonne+2].type == 0 && tabcases[indiceligne-1][indicecolonne+3].type == 0 && tabcases[indiceligne+1][indicecolonne+1].type == 0 && tabcases[indiceligne+1][indicecolonne+2].type == 0 && tabcases[indiceligne+1][indicecolonne+3].type == 0)
                {
                    if(tabcases[indiceligne-2][indicecolonne+1].type == 0 && tabcases[indiceligne-2][indicecolonne+2].type == 0 && tabcases[indiceligne+2][indicecolonne+1].type == 0 && tabcases[indiceligne+2][indicecolonne+2].type == 0 )
                    {
                        if(tabcases[indiceligne-3][indicecolonne+2].type == 0 && tabcases[indiceligne+3][indicecolonne+2].type == 0)
                        {
                            *autor = 1;
                        }
                        else
                        {
                            *autor = 0;
                        }
                    }
                    else
                    {
                        *autor = 0;
                    }
                }
                else
                {
                    *autor = 0;
                }
            }
        }
        else
        {
            *autor = 0;
        }
    }
    else
    {
        *autor = 0;
    }
}

void ecriture_case_centrale(t_cases** tabcases, int indiceligne, int indicecolonne, int type)
{
    tabcases[indiceligne][indicecolonne+1].type = type;
    tabcases[indiceligne][indicecolonne+2].type = type;
    tabcases[indiceligne][indicecolonne+3].type = type;

    if(indiceligne%2 == 0)
    {
        tabcases[indiceligne-1][indicecolonne].type = type;
        tabcases[indiceligne-1][indicecolonne+1].type = type;
        tabcases[indiceligne-1][indicecolonne+2].type = type;
        tabcases[indiceligne+1][indicecolonne].type = type;
        tabcases[indiceligne+1][indicecolonne+1].type = type;
        tabcases[indiceligne+1][indicecolonne+2].type = type;

        tabcases[indiceligne-2][indicecolonne+1].type = type;
        tabcases[indiceligne-2][indicecolonne+2].type = type;
        tabcases[indiceligne+2][indicecolonne+1].type = type;
        tabcases[indiceligne+2][indicecolonne+2].type = type;

        tabcases[indiceligne-3][indicecolonne+1].type = type;
        tabcases[indiceligne+3][indicecolonne+1].type = type;
    }
    else
    {
        tabcases[indiceligne-1][indicecolonne+1].type = type;
        tabcases[indiceligne-1][indicecolonne+2].type = type;
        tabcases[indiceligne-1][indicecolonne+3].type = type;
        tabcases[indiceligne+1][indicecolonne+1].type = type;
        tabcases[indiceligne+1][indicecolonne+2].type = type;
        tabcases[indiceligne+1][indicecolonne+3].type = type;

        tabcases[indiceligne-2][indicecolonne+1].type = type;
        tabcases[indiceligne-2][indicecolonne+2].type = type;
        tabcases[indiceligne+2][indicecolonne+1].type = type;
        tabcases[indiceligne+2][indicecolonne+2].type = type;

        tabcases[indiceligne-3][indicecolonne+2].type = type;
        tabcases[indiceligne+3][indicecolonne+2].type = type;
    }
}

void info_bat(t_cases** tabcases,int clique_x,int clique_y, BITMAP* fond)
{

    int indiceligne,indicecolonne;
    if(mouse_b&2)
    {
        BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
        buffer = creation_buffer(tabcases);
        determination_indice(buffer,&indiceligne,&indicecolonne,clique_x,clique_y);
        if(tabcases[indiceligne][indicecolonne].type == 4)
        {
            textprintf_ex(fond, font, 200, 40,makecol(255,255,255),-1,"Habitant : %d", tabcases[indiceligne][indicecolonne].nbr_hab);
            textprintf_ex(fond, font, 200, 50,makecol(255,255,255),-1,"Niveau : %d", tabcases[indiceligne][indicecolonne].niveau);
        }
        destroy_bitmap(buffer);
    }

}


