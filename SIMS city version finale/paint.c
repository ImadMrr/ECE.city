#include "header.h"

/// Procedure qui gere la musique du jeu
void musique()
{
    SAMPLE* audio = load_sample("documents/sons/son.wav");
    if(audio == NULL)
    {
        printf("Erreur d'ouverture fichier audio\n");
    }

    play_sample(audio, 1000,128,1000,60);

}

/// Fonction qui passe le noir d'une bitmap en magenta
BITMAP* lave_bitmap(BITMAP* fond)
{
    int pixel =0;
    int red, blue,green;
    for(int x=0; x<fond->w; x++)
    {
        for(int y=0; y<fond->h ; y++)
        {
            pixel = getpixel(fond, x,y);
            red = getr(pixel);
            blue = getb(pixel);
            green = getg(pixel);
            if( red < 25 && blue < 25 && green < 25 )
            {
                putpixel(fond, x, y, makecol(255,0,255));
            }
        }
    }
    return fond;
}

/// Fonction qui passe le blanc d'une bitmap en magenta
BITMAP* lave_bitmap2(BITMAP* fond)
{
    int pixel =0;
    int red, blue,green;
    for(int x=0; x<fond->w; x++)
    {
        for(int y=0; y<fond->h ; y++)
        {
            pixel = getpixel(fond, x,y);
            red = getr(pixel);
            blue = getb(pixel);
            green = getg(pixel);
            if( red > 230 && blue > 230 && green > 230 )
            {
                putpixel(fond, x, y, makecol(255,0,255));
            }
        }
    }
    return fond;
}

/// Fonction qui passe le blanc d'une bitmap en noir
BITMAP* blanc_devient_noir(BITMAP* fond)
{
    int pixel =0;
    int red, blue,green;
    for(int x=0; x<fond->w; x++)
    {
        for(int y=0; y<fond->h ; y++)
        {
            pixel = getpixel(fond, x,y);
            red = getr(pixel);
            blue = getb(pixel);
            green = getg(pixel);
            if( red > 200 && blue > 200 && green > 200 )
            {
                putpixel(fond, x, y, makecol(0,0,0));
            }
        }
    }
    return fond;
}

/// Fonction qui dessine un losange correspondant a une case
BITMAP* dessin_case(int r, int g, int b) // 3 parametres r,g, b important
{
    BITMAP* losange = load_bitmap("documents/bitmap/map/herbe.bmp", NULL);
    for(int x=0; x < losange->w; x++)
    {
        for(int y = 0; y < losange->h ; y++)
        {
            ///Vérification des coordonnées  -----------------------------------------------------------///
            if(x == 0 || x == 1 || x == 38 || x == 39 )
            {
                if(y == 9 || y == 10)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 2 || x == 3 || x == 36 || x == 37)
            {
                if(y >= 8 && y <= 11)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 4 || x == 5 || x == 34 || x == 35)
            {
                if(y >= 7 && y<= 12)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 6 || x == 7 || x == 32 || x == 33)
            {
                if(y>= 6 && y <= 13)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 8 || x == 9 || x == 30 || x == 31)
            {
                if(y>=5 && y<=14)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 10 || x == 11 || x == 28 || x == 29)
            {
                if(y >=4 && y<=15)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 12 || x == 13 || x == 26 || x == 27)
            {
                if(y>=3 && y <= 16)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 14 || x == 15 || x == 24 || x == 25)
            {
                if(y>=2 && y <=17)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x == 16 || x == 17 || x == 22 || x == 23)
            {
                if(y>=1 && y<=18)
                {
                    putpixel(losange, x, y, makecol(r,g,b));
                }
            }

            if(x >= 18 && x <=21)
            {
                putpixel(losange, x, y, makecol(r,g,b));
            }

        }
    }
    return losange;
}

/// Fonction qui creer un buffer invisible permettant de retrouver les indices de la matrice
BITMAP* creation_buffer(t_cases** tabcases)
{
    BITMAP* fond = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* losange = load_bitmap("documents/bitmap/map/herbe.bmp", NULL);

    int r =0;
    int b = 0;
    int g = 200;

    for(int i = 0 ; i<60 ; i++ )
    {
        r = 0;
        for(int j =0; j<26; j++)
        {
            losange = dessin_case(r,g,b); // incrementation de r, g, b pour retrouver les indices
            r = r+1;
            draw_sprite(fond,losange, tabcases[i][j].colonne, tabcases[i][j].ligne);
        }
        b = b +1;
    }
    return fond;
}

/// Fonction non-utilise qui dessine un plus petit losange dans le grand pour afficher le chemin emprunte par les distributions d'eau et d'electricite
BITMAP* dessin_chemin_losange(BITMAP* losange, int couleur)
{
    for(int x = 0; x < losange->w; x++)
    {
        for(int y=0; y < losange->h; y++)
        {
            ///Vérification des coordonnées  -----------------------------------------------------------///
            if( x == 5 || x == 34 )
            {
                if(y == 10)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x == 6 || x == 7 || x == 32 || x == 33)
            {
                if( y == 10)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x == 8 || x == 9 || x == 30 || x == 31)
            {
                if(y>=9 && y<=11)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x == 10 || x == 11 || x == 28 || x == 29)
            {
                if(y >=8 && y<=12)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x == 12 || x == 13 || x == 26 || x == 27)
            {
                if(y>=7 && y <= 13)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x == 14 || x == 15 || x == 24 || x == 25)
            {
                if(y>=6 && y <=14)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x == 16 || x == 17 || x == 22 || x == 23)
            {
                if(y>=5 && y<=15)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

            if(x >= 18 && x <=21)
            {
                if(y >= 4 && y <= 16)
                {
                    putpixel(losange, x, y, couleur);
                }
            }

        }
    }
    return losange;
}

/// Procedure non-utilise qui marque les cases parcourues par la distribution d'eau
void coloration_chemin_eau(t_ville* V, int arriveeL, int arriveeC)
{
    int tpmL = 0;
    int tpmC = 0;
    int x;
    if(V->tabcases[arriveeL][arriveeC].type == 2 || V->tabcases[arriveeL][arriveeC].type == 3)
    {
        V->tabcases[arriveeL][arriveeC].c_eau = 9;
    }
    tpmL = arriveeL;//valeur temporaire
    tpmC = arriveeC;//valeur temporaire
    while(tpmL != -3)
    {
        if(V->tabcases[arriveeL][arriveeC].type == 2 || V->tabcases[arriveeL][arriveeC].type == 3)
        {
            V->tabcases[arriveeL][arriveeC].c_eau = 9;
        }
        x = V->circ_eau->pSommet[tpmL][tpmC]->pred_L;
        tpmC = V->circ_eau->pSommet[tpmL][tpmC]->pred_C;
        tpmL = x;
    }
}

/// Procedure non-utilise qui marque les cases parcourues par la distribution d'electricite
void coloration_chemin_elec(t_ville* V, int arriveeL, int arriveeC)
{
    int tpmL = 0;
    int tpmC = 0;
    int x;
    V->tabcases[arriveeL][arriveeC].c_elec = 9;
    tpmL = arriveeL;//valeur temporaire
    tpmC = arriveeC;//valeur temporaire
    while(tpmL != -3)
    {
        if(V->circ_eau->pSommet[tpmL][tpmC]->pred_L != -3)//jusqu'au sommet de départ
        {
            V->tabcases[tpmL][tpmC].c_elec = 9;
        }
        x = V->circ_eau->pSommet[tpmL][tpmC]->pred_L;
        tpmC = V->circ_eau->pSommet[tpmL][tpmC]->pred_C;
        tpmL = x;
    }
}
