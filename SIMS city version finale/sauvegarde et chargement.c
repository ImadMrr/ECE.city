#include "header.h"

/// Fonction qui cree un premier chemin de parcours de fichier
char* creation_chemin_sauvegarde(char* nom)
{
    char* trajet ;
    trajet = (char*)malloc( (strlen(nom) + strlen("documents/sauvegarde/") + 1) * sizeof(char) );
    strcpy(trajet,"documents/sauvegarde/");
    strcat(trajet,nom);
    return trajet;
}

/// Procedure qui met en place les differentes sauvegarde importante
void sauvegarde_general(t_ville* V, float temps)
{
    char* nom = saisie_sauvegarde();
    char* trajet = creation_chemin_sauvegarde(nom);
    sauvegarde_matrice(V->tabcases,trajet);
    sauvegarde_info_ville(V, trajet,temps);
    sauvegarde_matrice_niveau(V->tabcases, trajet);
    sauvegarde_matrice_temps(V->tabcases, trajet);
    sauvegarde_matrice_alea(V->tabcases, trajet);
}

/// Procedure qui sauvegarde le type de chaque case de la matrice
void sauvegarde_matrice(t_cases** tabcases, char* nom)
{
    char tpm1[500];

    int resultat = 0;

    resultat = mkdir(nom);
    if(resultat == -1)
    {
        printf("Erreur de creation de repertoire\n");
        exit(-1);
    }
    char* trajet2 = (char*)malloc((strlen("/matrice.txt") + 1) * sizeof(char));
    strcpy(tpm1, nom);
    strcpy(trajet2, "/matrice.txt");

    strcat(tpm1, trajet2);

    FILE* fichier = NULL;
    fichier = fopen(tpm1, "w");
    if(fichier == NULL)
    {
        printf("Erreur de creation ou d'ouverture fichier\n");
        exit(-1);
    }

    for(int i=0; i<60;i++)
    {
        for(int j = 0; j<26; j++)
        {
            fprintf(fichier, "%d ", tabcases[i][j].type);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

/// Procedure qui sauvegarde les informations importantes de la ville
void sauvegarde_info_ville(t_ville* V, char* nom, float temps)
{
    char tpm[500];
    strcpy(tpm, nom);
    char* trajet = (char*)malloc((strlen("/ville.txt")+1 )* sizeof(char));
    strcpy(trajet, "/ville.txt");
    strcat(tpm, trajet);

    FILE* fichier = NULL;
    fichier = fopen(tpm, "w");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture ou de creation fichier ville texte\n");
        exit(-1);
    }
    fprintf(fichier, "%d", V->mode_de_jeu);
    fprintf(fichier, "\n");
    fprintf(fichier, "%f", temps);
    fprintf(fichier, "\n");
    fprintf(fichier, "%s", V->nom);
    fprintf(fichier, "\n");

    fprintf(fichier, "%d", V->argent);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", V->habitants);
    fprintf(fichier, "\n");

    fprintf(fichier, "%d", V->capa_eau);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", V->capa_elec);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", V->num_chateau);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", V->num_centrale);
    fprintf(fichier, "\n");
    fclose(fichier);
}

/// Procedure qui sauvegarde le niveau de chaque batiment de la matrice
void sauvegarde_matrice_niveau(t_cases** tabcases, char* nom)
{
    char tpm[500];
    strcpy(tpm, nom);
    char* trajet = (char*)malloc((strlen("/niveau.txt")+1 )* sizeof(char));
    strcpy(trajet, "/niveau.txt");
    strcat(tpm, trajet);

    FILE* fichier = NULL;
    fichier = fopen(tpm, "w");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture ou de creation fichier niveau texte\n");
        exit(-1);
    }
    for(int i=0; i<60;i++)
    {
        for(int j = 0; j<26; j++)
        {
            fprintf(fichier, "%d ", tabcases[i][j].niveau);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

/// Procedure qui sauvegarde le temps de chaque batiment de la matrice
void sauvegarde_matrice_temps(t_cases** tabcases, char* nom)
{
    char tpm[500];
    strcpy(tpm, nom);
    char* trajet = (char*)malloc((strlen("/temps.txt")+1 )* sizeof(char));
    strcpy(trajet, "/temps.txt");
    strcat(tpm, trajet);

    FILE* fichier = NULL;
    fichier = fopen(tpm, "w");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture ou de creation fichier habitant texte\n");
        exit(-1);
    }
    for(int i=0; i<60;i++)
    {
        for(int j = 0; j<26; j++)
        {
            fprintf(fichier, "%d ", tabcases[i][j].temps);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

/// Procedure qui sauvegarde l'aleatoire de chaque batiment de la matrice
void sauvegarde_matrice_alea(t_cases** tabcases, char* nom)
{
    char tpm[500];
    strcpy(tpm, nom);
    char* trajet = (char*)malloc((strlen("/alea.txt")+1 )* sizeof(char));
    strcpy(trajet, "/alea.txt");
    strcat(tpm, trajet);

    FILE* fichier = NULL;
    fichier = fopen(tpm, "w");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture ou de creation fichier capaeau texte\n");
        exit(-1);
    }
    for(int i=0; i<60;i++)
    {
        for(int j = 0; j<26; j++)
        {
            fprintf(fichier, "%d ", tabcases[i][j].alea);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

/// Fonction qui initialise en chargeant depuis des fichiers texte la matrice et la ville
t_ville* chargement_info_ville()
{
    t_ville* V = (t_ville*)malloc(sizeof(t_ville));

    /// CREATION DES CHEMINS DE PARCOURS DE DOSSIER -------------------------------------------///
    char* trajet1 = saisie_chargement();
    char* nom = creation_chemin_sauvegarde(trajet1);
    char tpm[500];
    char tpm2[500];
    char tpm3[500];
    char tpm4[500];
    char tpm5[500];

    strcpy(tpm, nom);
    strcpy(tpm2, nom);
    strcpy(tpm3, nom);
    strcpy(tpm4, nom);
    strcpy(tpm5, nom);

    char* trajet = (char*)malloc((strlen("/ville.txt")+1 )* sizeof(char));
    strcpy(trajet, "/ville.txt");
    strcat(tpm, trajet);

    char* trajet2 = (char*)malloc((strlen("/matrice.txt")+1 )* sizeof(char));
    strcpy(trajet2, "/matrice.txt");
    strcat(tpm2, trajet2);

    char* trajet3 = (char*)malloc((strlen("/niveau.txt")+1 )* sizeof(char));
    strcpy(trajet3, "/niveau.txt");
    strcat(tpm3, trajet3);

    char* trajet4 = (char*)malloc((strlen("/temps.txt")+1 )* sizeof(char));
    strcpy(trajet4, "/temps.txt");
    strcat(tpm4, trajet4);

    char* trajet5 = (char*)malloc((strlen("/alea.txt")+1 )* sizeof(char));
    strcpy(trajet5, "/alea.txt");
    strcat(tpm5, trajet5);

    // recuperation des infos de la ville
    FILE* fichier = NULL;
    fichier = fopen(tpm, "r+");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture du fichier ville texte\n");
        exit(-1);
    }
    fscanf(fichier, "%d\n", &V->mode_de_jeu);
    fscanf(fichier, "%f\n", &V->temps);
    fscanf(fichier, "%s\n", V->nom);

    fscanf(fichier, "%d\n", &V->argent);
    fscanf(fichier, "%d\n", &V->habitants);
    printf("test\n");

    fscanf(fichier, "%d\n", &V->capa_eau);
    fscanf(fichier, "%d\n", &V->capa_elec);

    printf("test\n");
    fscanf(fichier, "%d\n", &V->num_chateau);
    fscanf(fichier, "%d\n", &V->num_centrale);
    fclose(fichier);

    // recuperation du type de chaque case
    FILE* fichier2 = NULL;
    fichier2 = fopen(tpm2, "r+");
    if(fichier2 == NULL)
    {
        printf("Erreur d'ouverture du fichier matrice texte\n");
        exit(-1);
    }
    int ligne = 80;
    int colonne = 0;

    V->tabcases = (t_cases**)malloc(60* sizeof(t_cases*));

    for(int i = 0; i<60; i++)
    {
        if(i%2 == 0)
            colonne = 250;
        else
            colonne = 270;
        V->tabcases[i] = (t_cases*)malloc(26 * sizeof(t_cases));
        for(int j=0; j<26; j++)
        {
            V->tabcases[i][j].colonne = colonne;
            V->tabcases[i][j].ligne = ligne;
            V->tabcases[i][j].nbr_hab = 0;
            V->tabcases[i][j].capa_eau = 0;
            V->tabcases[i][j].capa_elec = 0;
            V->tabcases[i][j].niveau = 0;
            V->tabcases[i][j].num_chateau = 0;
            V->tabcases[i][j].num_centrale = 0;
            V->tabcases[i][j].temps_save = 0;
            V->tabcases[i][j].temps = 0;
            V->tabcases[i][j].alea = 0;
            V->tabcases[i][j].ruine = 0;
            colonne = colonne +40;
            fscanf(fichier2, "%d", &V->tabcases[i][j].type);
        }
        ligne = ligne +10;
    }
    fclose(fichier2);

    // recuperation du niveau de chaque batiment
    FILE* fichier3 = NULL;
    fichier3 = fopen(tpm3, "r+");
    if(fichier3 == NULL)
    {
        printf("Erreur d'ouverture du fichier niveau texte\n");
        exit(-1);
    }

    for(int i = 0; i<60; i++)
    {
        for(int j=0; j<26; j++)
        {
            fscanf(fichier3, "%d", &V->tabcases[i][j].niveau);
            if(V->tabcases[i][j].niveau == 0)
            {
                V->tabcases[i][j].nbr_hab = 0;
            }
            if(V->tabcases[i][j].niveau == 1)
            {
                V->tabcases[i][j].nbr_hab = 10;
            }
            if(V->tabcases[i][j].niveau == 2)
            {
                V->tabcases[i][j].nbr_hab = 50;
            }
            if(V->tabcases[i][j].niveau == 3)
            {
                V->tabcases[i][j].nbr_hab = 100;
            }
            if(V->tabcases[i][j].niveau == 4)
            {
                V->tabcases[i][j].nbr_hab = 1000;
            }
        }
    }
    fclose(fichier3);

    // recuperation du temps de chaque batiment
    FILE* fichier4 = NULL;
    fichier4 = fopen(tpm4, "r+");
    if(fichier4 == NULL)
    {
        printf("Erreur d'ouverture du fichier temps texte\n");
        exit(-1);
    }

    for(int i = 0; i<60; i++)
    {
        for(int j=0; j<26; j++)
        {
            fscanf(fichier4,"%d", &V->tabcases[i][j].temps_save);
        }
    }
    fclose(fichier4);

    // recuperation de l'aleatoire de chaque batiment
    FILE* fichier5 = NULL;
    fichier5 = fopen(tpm5, "r+");
    if(fichier5 == NULL)
    {
        printf("Erreur d'ouverture du fichier alea texte\n");
        exit(-1);
    }

    for(int i = 0; i<60; i++)
    {
        for(int j=0; j<26; j++)
        {
            fscanf(fichier5, "%d", &V->tabcases[i][j].alea);
        }
    }
    fclose(fichier5);

    return V;
}

/// Fonction qui permet la saisie d'un nom de sauvegarde de partie
char* saisie_sauvegarde()
{
    BITMAP* fond;
    fond = load_bitmap("documents/bitmap/fonds/fond sauvegarde.bmp", NULL);
    char* pseudo;
    int touche, touche1, touche2;
    int i=0;
    char masaisie[21]; // stockage de la totalité de la saisie
    char lastsaisie[2];    // stockage la derniere touche saisie
    masaisie[20]=0;
    lastsaisie[1]=0;
    clear_keybuf();
    rectfill(fond,200,60,660,120,makecol(0,0,0));
    textprintf_ex(fond, font, 210, 70, makecol(255,255,255),0,"DONNER UN NOM A VOTRE SAUVEGARDE : (entree pour valider)");
    /* affichage curseur */
    textprintf_ex(fond,font,210+8*(i+1),100,makecol(255,255,255),0,"_");

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
                textprintf_ex(fond,font,210+8*i,100,makecol(255,255,255),0,"%s",lastsaisie);
                i++;
                textprintf_ex(fond,font,210+8*i,100,makecol(255,255,255),0,"_");
            }
        }
        // si effacement
        if ( touche2==KEY_BACKSPACE )
        {
            i--;
            if ( i<0 )
                i=0;
            textprintf_ex(fond,font,210+8*i,100,makecol(255,255,255),0,"_");
            textprintf_ex(fond,font,210+8*(i+1),100,makecol(255,255,255),0," ");
        }
        // si validation
        if ( (touche2==KEY_ENTER_PAD) || (touche2==KEY_ENTER) )
        {
            textprintf_ex(fond,font,210+8*i,100,makecol(0,0,0),-1," ");
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

/// Fonction qui permet la saisie d'un nom de partie pour la charger
char* saisie_chargement()
{
    BITMAP* fond;
    fond = load_bitmap("documents/bitmap/fonds/fond chargement.bmp", NULL);
    char* pseudo;
    int touche, touche1, touche2;
    int i=0;
    char masaisie[21]; // stockage de la totalité de la saisie
    char lastsaisie[2];    // stockage la derniere touche saisie
    masaisie[20]=0;
    lastsaisie[1]=0;
    clear_keybuf();
    rectfill(fond,430,60,880,120,makecol(0,0,0));
    textprintf_ex(fond, font, 450, 70, makecol(255,255,255),0,"SAISIR LE NOM DE VOTRE PARTIE : (entree pour valider)");
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
