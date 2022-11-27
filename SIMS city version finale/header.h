#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include <sys/stat.h>
#include <limits.h>


/* Structure d'un arc*/
struct Arc
{
    int ligne;
    int colonne;
    int valeur;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
typedef struct ssommet
{
    struct Arc* arc;
    int ligne;
    int colonne;
    int couleur;
    int pred_L;
    int pred_C;
    int distance;
    int distance_fix;
}t_sommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int or;
    t_sommet*** pSommet;
}Graphe;

typedef struct provennance
{
    int valeur;
    int source_L;
    int source_C;
    int valid;
}t_prov;

/// Structure de notre matrice de case utilisee partout
typedef struct cases
{
    int ligne;
    int colonne;
    int type;
    time_t debut;
    time_t fin;
    int temps;
    int temps_save;
    int niveau;
    int nbr_hab;
    int capa_eau;
    int capa_elec;
    t_prov tabeau[15];
    t_prov tabelec;
    int num_chateau;
    int num_centrale;
    int vu;
    int alea;
    int c_eau;
    int c_elec;
    int feu;
    int ruine;
    int connex;
}t_cases;

/// Structure ville utilisee partout
typedef struct ville
{
    char* nom;
    int mode_de_jeu;
    int argent;
    int habitants;
    int capa_eau;
    int capa_elec;
    Graphe* circ_eau;
    t_cases** tabcases;
    float temps;
    int num_chateau;
    int num_centrale;
}t_ville;

// structure maillon, utile pour notre liste dynamique
typedef struct maillon
{
    int nbr;
    struct maillon* next;
}t_maillon;

/// initialisation allegro
void initialisation();

/// SOUS-PROGRAMME DE MENU
void logo();
char* saisie_pseudo();
void menu_principal();
void quitter();
void regle();
int choix_mode();
void horloge(float temps,BITMAP* fond);
void menu_pause(t_ville* V,int* fin,float temps,time_t end, float* temps_pause);

/// SOUS-PROGRAMME DE CONSTRUCTION
int cliqueChoixMenu( int cliqueX, int cliqueY, t_cases* logo  );
void champPorte(BITMAP* buffer, int cliqueX, int cliqueY, BITMAP* fond, int refSelect, t_cases** tabcases );
void suppression(t_ville* V, BITMAP* fond, time_t start);
void construction_map(t_ville* V, BITMAP* fond, int refSlect, time_t start );
void determination_indice(BITMAP* buffer, int* indiceligne, int* indicecolonne, int cliqueX, int cliqueY);
void ecriture_case_maisons(t_cases** tabcases, int indiceligne, int indicecolonne,int type);
void ecriture_case_centrale(t_cases** tabcases, int indiceligne, int indicecolonne, int type);
void verif_placement_bat(t_cases** tabcases, int indiceligne,int indicecolonne, int* autor);
void verif_placement_centrale(t_cases** tabcases, int indiceligne, int indicecolonne, int* autor);

/// SOUS-PROGRAMME D'AFFICHAGE SUR LA MAP
void info_bat(t_cases** tabcases,int clique_x,int clique_y, BITMAP* fond);
void afficher_map(t_ville* V, BITMAP* fond, int niveau);
void afficher_outil(t_cases* tablogo,t_cases** tabcasesMenu, BITMAP* fond);
void affichage_info_distribution_eau(t_ville* V, int cliqueX, int cliqueY, BITMAP* fond);
void affichage_info_distribution_elec(t_ville* V,int cliqueX,int  cliqueY, BITMAP* fond);

/// SOUS-PROGRAMME DE GESTION DES CYCLES DE JEU
void fin_de_cycle(t_ville* V, BITMAP* fond);
void cycle_feu(float temps, t_ville* V);
void modif_niveau_bat_communiste(t_ville* V, int i, int j);
void modif_niveau_bat_capitaliste(t_ville* V, int i, int j);

/// SOUS-PROGRAMME D'INITIALISATION DU JEU
t_cases** chargement_map();
t_cases* initialisation_tabLogo();
t_cases** initialisation_outil();
t_ville* init_ville();

///SOUS-PROGRAMME DE DISTRIBUTION A CHAQUE CYCLE
void dist_eau(t_ville* V);
void dist_elec(t_ville* V);
void pompier(t_ville* V);
void aleatoire_feu(t_ville* V);
void controle_feu(t_ville* V);
void re_initialisation(t_ville* V);

/// SOUS-PROGRAMME DE SAUVEGARDE ET DE CHARGEMENT
void sauvegarde_general(t_ville* V, float temps);
void sauvegarde_matrice(t_cases** tabcases, char* nom);
void sauvegarde_info_ville(t_ville* V, char* nom, float temps);
void sauvegarde_matrice_niveau(t_cases** tabcases, char* nom);
void sauvegarde_matrice_temps(t_cases** tabcases, char* nom);
void sauvegarde_matrice_alea(t_cases** tabcases, char* nom);
char* saisie_sauvegarde();
char* saisie_chargement();
t_ville* chargement_info_ville();

/// SOUS-PROGRAMME DE DESSIN ALLEGRO
BITMAP* lave_bitmap(BITMAP* fond);
BITMAP* lave_bitmap2(BITMAP* fond);
BITMAP* blanc_devient_noir(BITMAP* fond);
BITMAP* dessin_case(int r, int g, int b);
BITMAP* creation_buffer(t_cases** tabcases);
void coloration_chemin_eau(t_ville* V, int arriveeL, int arriveeC);
void coloration_chemin_elec(t_ville* V, int arriveeL, int arriveeC);
BITMAP* dessin_chemin_losange(BITMAP* losange, int couleur);

/// SOUS-PROGRAMME DE THEORIE DES GRAPHES
void djikstra(Graphe* g, int dep_L, int dep_C);
int BFS(t_ville* V,Graphe* ungraph, int dep_L, int dep_C);
void minimum(Graphe* g, int* imin_L, int* imin_C);
void minimum_eau(t_ville* V, int* imin_L, int* imin_C);
void minimum_D(t_ville* V, int* imin_L, int* imin_C);
void minimum_elec(t_ville* V, int* imin_L, int* imin_C, int deb_L, int deb_C);
void minimum_pomp(t_ville* V, int* imin_L, int* imin_C);
t_maillon* creerMaillon(int x);
t_maillon* creerFileDyna(int x);
Graphe* marquage(Graphe* ungraph, int smmtL, int smmtC);
t_maillon* ajoutFileDyna(t_maillon* UneFile, t_maillon* Nouv);
t_maillon* supFileDyna(t_maillon* UneFile, int* depile);
int testFileDynaVide(t_maillon* UneFile);


/// SOUS-PROGRAMME DE GESTION DU JEU
void maps(int type);
void musique();
void jeu();

/// SOUS-PROGRAMME DE CREATION DE GRAPHES
Graphe* CreerGraphe();
t_ville * lire_graphe(t_ville* V);
Graphe* init(Graphe* g, int dep_L, int dep_C);
Graphe* CreerArete(Graphe* g,int s1_L,int s1_C,int s2_L,int s2_C);


#endif // HEADER_H_INCLUDED
