#include "header.h"

void initialisation()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1400,800,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    BITMAP* curseur_souris = load_bitmap("documents/bitmap/props/souris.bmp", NULL); // utilisation d'une autre souris que de la souris de base
    set_mouse_sprite(curseur_souris);
    show_mouse(screen);
    destroy_bitmap(curseur_souris);

    install_sound(DIGI_AUTODETECT, MIDI_NONE,0);
}

t_ville* init_ville()
{
    t_ville* V = (t_ville*)malloc(sizeof(t_ville));
    V->nom = saisie_pseudo();
    V->mode_de_jeu = choix_mode();
    V->tabcases = chargement_map();
    V->argent = 500000;
    V->habitants = 0;
    V->capa_eau = 0;
    V->capa_elec = 0;
    V->nbr_c_eau = 0;
    V->nbr_c_elec = 0;
    V->temps = 0;
    V->num_chateau = 0;
    V->num_centrale = 0;
    return V;
}

t_cases** chargement_map()
{
    FILE* fichier = NULL;

    fichier = fopen("documents/map.txt", "r+");
    if(fichier == NULL)
    {
        printf("Erreur d ouverture fichier map \n");
        exit(-1);
    }

    t_cases** tabcases;
    tabcases = (t_cases**)malloc(60*sizeof(t_cases*));
    int ligne = 80;
    int colonne = 0;

    for(int i = 0; i < 60 ; i++)
    {

        if(i%2 == 0)
            colonne = 250;
        else
            colonne = 270;
        tabcases[i] = (t_cases*)malloc(26*sizeof(t_cases));

        for(int j = 0; j < 26 ; j++)
        {
            tabcases[i][j].colonne = colonne;
            tabcases[i][j].ligne = ligne;
            tabcases[i][j].nbr_hab = 0;
            tabcases[i][j].capa_eau = 0;
            tabcases[i][j].capa_elec = 0;
            tabcases[i][j].besoin_eau = 0;
            tabcases[i][j].niveau = 0;
            tabcases[i][j].num_chateau = 0;
            tabcases[i][j].num_centrale = 0;
            tabcases[i][j].temps_save = 0;
            tabcases[i][j].temps = 0;
            tabcases[i][j].alea = 0;
            tabcases[i][j].ruine = 0;
            tabcases[i][j].protec = 0;
            tabcases[i][j].feu = 0;
            colonne = colonne +40;
            fscanf(fichier, "%d", &tabcases[i][j].type);
        }
        ligne = ligne +10;
    }
    fclose(fichier);
    return tabcases;
}

///Initialise toutes les coordonnées des emplacements des structuress
t_cases* initialisation_tabLogo()
{
    t_cases* tablogo = (t_cases*)malloc(10*sizeof(t_cases));

    ///Batiment 1:
    tablogo[0].ligne=200;
    tablogo[0].colonne=65;
    tablogo[0].type=4;

    /// route 3:
    tablogo[1].ligne=280;
    tablogo[1].colonne=75;
    tablogo[1].type=8;

    ///chateau d'eau :
    tablogo[2].ligne = 345;
    tablogo[2].colonne = 40;
    tablogo[2].type = 5;

    ///centrale electrique
    tablogo[3].ligne = 330;
    tablogo[3].colonne = 110;
    tablogo[3].type = 6;

    ///pompier
    tablogo[4].ligne = 410;
    tablogo[4].colonne = 75;
    tablogo[4].type = 7;

    /// croix:
    tablogo[5].ligne=480;
    tablogo[5].colonne=40;
    tablogo[5].type=10;

    return tablogo;
}

t_cases** initialisation_outil()
{
    t_cases** tabcasesMenu;
    tabcasesMenu = (t_cases**)malloc(24*sizeof(t_cases*));
    int ligne = 20;
    int colonne = 0;

    for(int i = 0; i < 24; i++)
    {
        colonne = 0;
        tabcasesMenu[i] = (t_cases*)malloc(11*sizeof(t_cases));

        for(int j = 0; j < 11 ; j++)
        {
            tabcasesMenu[i][j].colonne = colonne;
            tabcasesMenu[i][j].ligne = ligne;
            colonne = colonne +10;
        }

        ligne = ligne +20;
    }

    return tabcasesMenu;
}
