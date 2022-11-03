#include "header.h"

void initialisation()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    show_mouse(screen);
}

void chargement_map()
{
    t_cases** tabcases;
    BITMAP* zero;
    FILE* fichier;
    fichier = fopen("map.txt", "r+");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture fichier\n");
        exit(-1);
    }
    tabcases = (t_cases**)malloc(45*sizeof(t_cases*));
    int colonne = 0;
    int ligne = 0;
    for(int i = 0; i < 45 ; i++)
    {
        colonne = 0;
        tabcases[i] = (t_cases*)malloc(35*sizeof(t_cases));
        for(int j = 0; j < 35 ; j++)
        {
            tabcases[i][j].colonne = colonne;
            tabcases[i][j].ligne = ligne;
            colonne = colonne +20;
            fscanf(fichier, "%d", &tabcases[i][j].cases);
        }
        ligne = ligne +20;
    }
    zero = load_bitmap("0.bmp", NULL);
    BITMAP* fond= create_bitmap(SCREEN_W,SCREEN_H);
    for(int k=0; k<45; k++)
    {
        for(int m = 0; m<35; m++)
        {
            if(tabcases[k][m].cases == 0)
            {
                draw_sprite(fond, zero, tabcases[k][m].ligne, tabcases[k][m].colonne);
            }
        }
    }
    while(!key[KEY_ESC])
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    }
    printf("%d", tabcases[45][35].ligne);
}

