#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

/*
void centreCase( int valx, int valy)
{
    int recup1,recup2;

    recup1=valx;recup2=valy;

     for(int i=0;i<SCREEN_W;i++)
        {
            if(i%20==0)
                {
                    if( recup1>= recup1+i && recup2<= recup2+i )
                        {

                        }
                }
        }
}*/




int main()
{


///Initialisation ALLEGRO

    allegro_init() ;
    install_mouse();
    install_keyboard();
    set_color_depth(desktop_color_depth());

    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,730,0,0))!=0)
    {
            allegro_message("prb gfx mode");
            allegro_exit();
            exit(EXIT_FAILURE);
    }

    show_mouse(screen);


 ///Creation d'une bitmap pour eviter les clignotements
    BITMAP* tempoMap = load_bitmap("map.bmp",NULL); ///création du buffer : même image que la map principale

    BITMAP* map=load_bitmap("map.bmp",NULL);

    if(map==NULL)
                {
                    allegro_message("ERREUR D OUVERTURE MAP !");
                }


    int violet=makecol(238, 130, 238);
    int jaune=makecol(255, 255, 0);
    int rouge=makecol(255, 0, 0);


   while ( !key[KEY_ESC] )
    {

    blit(tempoMap, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    blit(map, tempoMap, 0, 0, 0, 0, SCREEN_W, SCREEN_H);



    for(int i=0;i<SCREEN_W;i++)
        {
            if(i%50==0)
                textprintf_ex(map,font,0+i,0, makecol(255, 255, 0),-1,"%d", i );

        }

    for(int i=0;i<SCREEN_H;i++)
        {
            if(i%50==0)
                textprintf_ex(map,font,0,0+i, makecol(255, 255, 0),-1,"%d", i );

        }


     for(int i=0;i<SCREEN_H;i++)
        {
            if(i%20==0)
                line(map, 0, 350+i, 350+i, 0, violet);
        }


    for(int i=0;i<SCREEN_W;i++)
        {
            if(i%20==0)
                line(map, 0, 450-i, 280+i, SCREEN_H, violet);
        }


    /// 4 équations de droites : qui sont les droites qui limites notre plateau
    if( (mouse_y >= -1*mouse_x+450 ) && (mouse_y >= 1*mouse_x-450 )  && (mouse_y <= -1*mouse_x+1150 ) && (mouse_y <= 1*mouse_x+450 ) )
        {
            if( mouse_b & 1)
                circle(map, mouse_x, mouse_y, 2, jaune);
        }





    textprintf_ex(tempoMap,font,200,100, rouge,-1,"X : %d && Y : %d", mouse_x, mouse_y );
    //rest(20);   ///temps d'attente




















    ///rect(map, 0, 450, 0+20, 450+20, jaune); on peut pas afficher des losange (carré isométrique) avec rect()









    }

    return 0;
}
END_OF_MAIN() ;
