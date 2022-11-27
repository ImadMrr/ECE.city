#include "header.h"

/// Procedure qui affiche un logo pendant 3 secondes
void logo()
{
    BITMAP* fond;
    fond = load_bitmap("documents/bitmap/fonds/fond logo.bmp", NULL);
    blit(fond, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
    textprintf_ex(screen, font, 1100, 750, makecol(255,255,255), -1, "chargement");
    rest(1000);
    textprintf_ex(screen, font, 1200, 750, makecol(255,255,255), -1, ".");
    rest(1000);
    textprintf_ex(screen, font, 1220, 750, makecol(255,255,255), -1, ".");
    rest(1000);
    textprintf_ex(screen, font, 1240, 750, makecol(255,255,255), -1, ".");
    rest(1000);
    destroy_bitmap(fond);
}

/// Fonction qui permet la saisie d'un pseudo
char* saisie_pseudo()
{
    BITMAP* fond;
    fond = load_bitmap("documents/bitmap/fonds/fond pseudo.bmp", NULL);
    char* pseudo;
    int touche, touche1, touche2;
    int i=0;
    char masaisie[21]; // stockage de la totalité de la saisie
    char lastsaisie[2];    // stockage la derniere touche saisie
    masaisie[20]=0;
    lastsaisie[1]=0;
    clear_keybuf();
    rectfill(fond,430,60,855,120,makecol(0,0,0));
    textprintf_ex(fond, font, 450, 70, makecol(255,255,255),0,"SAISIR VOTRE NOM DE MAIRE : (entree pour valider)");
    /* affichage curseur */
    textprintf_ex(fond,font,450+8*(i+1),100,makecol(255,255,255),0,"_");

    while(!key[KEY_ENTER] && !key[KEY_ENTER_PAD])
    {
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        touche=readkey();
        touche1=touche & 0xFF; // code ASCII
        touche2=touche >> 8;   // scancode
        // selection des touches (la selection est totalement arbitraire)
        if (( touche1>31 && touche1<58) || ( touche1>64 && touche1<123))
        {
            if (i>=20)
                i=20;
            else
            {
                masaisie[i]=touche1;
                lastsaisie[0]=touche1;
                masaisie[i+1]=0;
                /*  on affiche la touche saisie */
                textprintf_ex(fond,font,450+8*i,100,makecol(255,255,255),0,"%s",lastsaisie);
                i++;
                textprintf_ex(fond,font,450+8*i,100,makecol(255,255,255),0,"_");
            }
        }
        // si effacement
        if ( touche2==KEY_BACKSPACE )
        {
            i--;
            if ( i<0 )
                i=0;
            textprintf_ex(fond,font,450+8*i,100,makecol(255,255,255),0,"_");
            textprintf_ex(fond,font,450+8*(i+1),100,makecol(255,255,255),0," ");
        }
        // si validation
        if ( (touche2==KEY_ENTER_PAD) || (touche2==KEY_ENTER) )
        {
            textprintf_ex(fond,font,450+8*i,100,makecol(0,0,0),-1," ");
            if (i==0)
                masaisie[0]=32; // space
            masaisie[i+1]=0;
        }
    }
    pseudo = (char*)malloc((strlen(masaisie)+1)*sizeof(char));
    if(pseudo != NULL)
    {
        strcpy(pseudo, masaisie);
    }
    clear_keybuf();
    clear_bitmap(fond);
    destroy_bitmap(fond);
    return pseudo;
}

/// Procedure qui affiche un menu principal qui presente plusieurs option de jeu
void menu_principal()
{
    install_mouse();
    BITMAP* fond = load_bitmap("documents/bitmap/fonds/fond menu principal.bmp", NULL);
    int stop = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;

    while(stop == 0)
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_ex(fond, font, 400,200,makecol(0,0,0),-1, "MENU PRINCIPAL");

        ///Vérification des coordonnées du clique
        if(mouse_x < 280 || mouse_x > 460 || mouse_y < 285 || mouse_y > 320 )
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 300, 300, couleur1, -1, "Regle du jeu");
        rect(fond, 280,285,460,320,couleur1);

        ///Vérification des coordonnées du clique
        if(mouse_x < 280 || mouse_x > 460 || mouse_y < 355 || mouse_y > 390)
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 300, 370, couleur2, -1, "Nouvelle partie");
        rect(fond, 280,355,460,390,couleur2);

        ///Vérification des coordonnées du clique
        if(mouse_x < 280 || mouse_x > 460 || mouse_y < 425 || mouse_y > 460)
        {
            couleur3 = makecol(0,0,0);
        }
        else
        {
            couleur3 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 300, 440, couleur3, -1, "Charger une partie");
        rect(fond, 280,425,460,460,couleur3);

        ///Vérification des coordonnées du clique
        if(mouse_x < 280 || mouse_x > 460 || mouse_y < 495 || mouse_y > 530)
        {
            couleur4 = makecol(0,0,0);
        }
        else
        {
            couleur4 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 300, 510, couleur4, -1, "Quitter le jeu");
        rect(fond, 280,495,460,530,couleur4);

        ///Envoie vers les différentes options :

        ///Vers règles du jeu
        if(couleur1 == makecol(0,112,113) && mouse_b&1)
        {
            regle();
        }
        ///Vers nouvelles partis
        if(couleur2 == makecol(0,112,113) && mouse_b&1)
        {
            maps(0);
        }
        ///Vers partis sauvegardé
        if(couleur3 == makecol(0,112,113) && mouse_b&1)
        {
            maps(1);
        }
        ///Quitter le jeu
        if(couleur4 == makecol(0,112,113) && mouse_b&1)
        {
            quitter();
            stop = 2;
        }
    }
    destroy_bitmap(fond);
}

/// Procedure qui affiche une fenetre de fin de jeu pendant 3 secondes
void quitter()
{
    BITMAP* fond = load_bitmap("documents/bitmap/fonds/fond quitter.bmp", NULL);
    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    textprintf_ex(screen, font, 600,750,makecol(0,0,0),-1,"AU REVOIR");
    rest(1000);
    textprintf_ex(screen, font, 610 + text_length(font, "AU REVOIR"), 750, makecol(0,0,0), -1, ".");
    rest(1000);
    textprintf_ex(screen, font, 620 + text_length(font, "AU REVOIR"), 750, makecol(0,0,0), -1, ".");
    rest(1000);
    textprintf_ex(screen, font, 630 + text_length(font, "AU REVOIR"), 750, makecol(0,0,0), -1, ".");
    rest(1000);
    destroy_bitmap(fond);
}

/// Procedure qui affiche les regles du jeu
void regle()
{
    BITMAP* fond = load_bitmap("documents/bitmap/fonds/fond regles.bmp", NULL);
    while(!(mouse_b&2))
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
    }
    destroy_bitmap(fond);
}

/// Fonction qui affiche une fenetre de choix de mode et retourne le choix
int choix_mode()
{
    int choix = 0;

    BITMAP* fond = load_bitmap("documents/bitmap/fonds/fond choix mode.bmp", NULL);
    int stop = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    while(stop == 0)
    {
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_ex(fond, font, 600, 60, makecol(255,255,255), -1, "CHOISSISSEZ UN MODE DE JEU");

        ///Vérification des coordonnées du clique
        if(mouse_x < 200 || mouse_x > 345 || mouse_y < 110 || mouse_y > 145)
        {
            couleur1 = makecol(255,255,255);
        }
        else
        {
            couleur1 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 215, 125, couleur1, -1, "MODE COMMUNISTE");
        rect(fond, 200, 110, 345, 145, couleur1);

        ///Vérification des coordonnées du clique
        if(mouse_x < 1050 || mouse_x > 1210 || mouse_y < 110 || mouse_y >145)
        {
            couleur2 = makecol(255,255,255);
        }
        else
        {
            couleur2 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 1065,125, couleur2, -1, "MODE CAPITALISTE");
        rect(fond, 1050, 110,1210, 145,couleur2);

        ///Envoie voir les différents choix
        if(couleur1 == makecol(0,112,113) && mouse_b&1)
        {
            choix = 1;
            stop = 2;
        }

        if(couleur2 == makecol(0,112,113) && mouse_b&1)
        {
            choix = 2;
            stop =2;
        }
    }
    destroy_bitmap(fond);
    return choix;
}

/// Procedure qui affiche une horloge en fonction du temps
void horloge(float temps, BITMAP* fond)
{
    BITMAP* horl = load_bitmap("documents/bitmap/props/horloge.bmp", NULL);
    BITMAP* rolex = load_bitmap("documents/bitmap/props/logorolex.bmp", NULL);
    rolex = lave_bitmap2(rolex);
    BITMAP* aiguillesec = load_bitmap("documents/bitmap/props/aiguille sec.bmp", NULL);
    aiguillesec = lave_bitmap2(aiguillesec);
    BITMAP* aiguillemin = load_bitmap("documents/bitmap/props/aiguille min.bmp", NULL);
    aiguillemin = lave_bitmap2(aiguillemin);
    BITMAP* aiguilleheur = load_bitmap("documents/bitmap/props/aiguille heure.bmp", NULL);
    aiguilleheur = lave_bitmap2(aiguilleheur);
    float rotation1 = 0;
    float rotation2 = 0;
    float rotation3 = 0;

    // produit en croix pour avoir une bonne rotation
    rotation1 = (temps *256)/60;
    rotation2 = ((temps/60) * 256) /60;
    rotation3 = ((temps / 3600) * 256) / 12;

    ///Affichage de l'horloge
    draw_sprite(horl, rolex, 35,48);

    ///Rotation de l'aiguille seconde
    rotate_sprite(horl,aiguillesec,0,0, itofix(rotation1));

    ///Rotation de l'aiguille minute
    rotate_sprite(horl,aiguillemin,0,0, itofix(rotation2));

    ///Rotation de l'aiguille heure
    rotate_sprite(horl,aiguilleheur,0,0, itofix(rotation3));

    ///Affichage du fond de l'horloge
    draw_sprite(fond, horl, 10,610);

    destroy_bitmap(horl);
    destroy_bitmap(aiguillesec);
    destroy_bitmap(aiguillemin);
    destroy_bitmap(aiguilleheur);
}

/// Procedure qui affiche un menu pause avec differentes option
void menu_pause(t_ville* V, int* fin,float temps, time_t end, float* temps_pause)
{
    time_t pause;
    BITMAP* fond = load_bitmap("documents/bitmap/fonds/fond menu pause.bmp", NULL);
    int stop = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;

    while(stop == 0)
    {
        time(&pause);
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);

        textprintf_ex(fond, font, 650, 80, makecol(255,255,255), -1, "MENU PAUSE");

        ///Vérification des coordonnées du clique
        if(mouse_x < 385 || mouse_x > 650 || mouse_y < 185 || mouse_y > 220)
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 400, 200, couleur1, -1, "Regles du jeu");
        rect(fond, 385, 185, 650, 220, couleur1);

        ///Vérification des coordonnées du clique
        if(mouse_x < 385 || mouse_x > 650 || mouse_y < 235 || mouse_y > 270)
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 400, 250, couleur2, -1, "Sauvegarder la partie en cours");
        rect(fond, 385, 235,650,270, couleur2);

        ///Vérification des coordonnées du clique
        if(mouse_x < 385 || mouse_x > 650 || mouse_y < 285 || mouse_y > 320)
        {
            couleur3 = makecol(0,0,0);
        }
        else
        {
            couleur3 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 400, 300, couleur3, -1, "Continuer la partie en cours");
        rect(fond, 385, 285, 650, 320, couleur3);

        ///Vérification des coordonnées du clique
        if(mouse_x < 385 || mouse_x > 650 || mouse_y < 335 || mouse_y > 370)
        {
            couleur4 = makecol(0,0,0);
        }
        else
        {
            couleur4 = makecol(0,112,113);
        }
        textprintf_ex(fond, font, 400, 350, couleur4, -1, "Quitter le partie en cours");
        rect(fond, 385, 335, 650,370,couleur4);

        ///Envoie voir les différents choix :

         ///Regles du jeux
        if(couleur1 == makecol(0,112,113) && mouse_b&1)
        {
            regle();
        }
        ///Saubegarde
        if(couleur2 == makecol(0,112,113) && mouse_b&1)
        {
            sauvegarde_general(V,temps);
        }
        ///Arret du jeu
        if(couleur3 == makecol(0,112,113) && mouse_b&1)
        {
            stop = 1;
        }
        if(couleur4 == makecol(0,112,113) && mouse_b&1)
        {
            stop = 1;
            *fin = 1;
        }
    }
    *temps_pause = difftime(pause,end);
    destroy_bitmap(fond);
}
