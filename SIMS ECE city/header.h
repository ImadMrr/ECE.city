#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include <sys/stat.h>

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
}t_sommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int or;
    t_sommet*** pSommet;
}Graphe;

typedef struct cases
{
    int ligne;
    int colonne;
    int type;
    int niveau;
    int nbr_hab;
    int capa_eau;
    int capa_elec;
}t_cases;

typedef struct ville
{
    char* nom;
    int mode_de_jeu;
    int argent;
    int habitants;
    int capa_eau;
    int capa_elec;
    Graphe* circ_eau;
    Graphe* circ_elec;
    t_cases** tabcases;
    int nbr_c_eau;
    int nbr_c_elec;
    float temps;
}t_ville;



void initialisation();

void logo();
char* saisie_pseudo();
void menu_principal();
void quitter();
void regle();
int choix_mode();
void horloge(float temps,BITMAP* fond);
void menu_pause(t_ville* V,int* fin,float temps,time_t end, float* temps_pause);

int cliqueChoixMenu( int cliqueX, int cliqueY, t_cases* logo  );
void champPorte(BITMAP* buffer, int cliqueX, int cliqueY, BITMAP* fond, int refSelect, t_cases** tabcases );
void suppression(t_ville* V, BITMAP* fond, time_t start);
void construction_map(t_ville* V, BITMAP* fond, int refSlect, time_t start );
void determination_indice(BITMAP* buffer, int* indiceligne, int* indicecolonne, int cliqueX, int cliqueY);
void ecriture_case_maisons(t_cases** tabcases, int indiceligne, int indicecolonne,int type);
void ecriture_case_centrale(t_cases** tabcases, int indiceligne, int indicecolonne, int type);

void verif_placement_bat(t_cases** tabcases, int indiceligne,int indicecolonne, int* autor);
void verif_placement_centrale(t_cases** tabcases, int indiceligne, int indicecolonne, int* autor);
void info_bat(t_cases** tabcases,int clique_x,int clique_y, BITMAP* fond);

t_cases** chargement_map();
void afficher_map(t_ville* V, BITMAP* fond, int niveau);
t_cases* initialisation_tabLogo();
t_cases** initialisation_outil();
void afficher_outil(t_cases* tablogo,t_cases** tabcasesMenu, BITMAP* fond);
void maps(int type);

BITMAP* lave_bitmap(BITMAP* fond);
BITMAP* lave_bitmap2(BITMAP* fond);
BITMAP* blanc_devient_noir(BITMAP* fond);

BITMAP* dessin_case(int r, int g, int b);
BITMAP* creation_buffer(t_cases** tabcases);

void sauvegarde_general(t_ville* V, float temps);
void sauvegarde_matrice(t_cases** tabcases, char* nom);
void sauvegarde_info_ville(t_ville* V, char* nom, float temps);
void sauvegarde_matrice_niveau(t_cases** tabcases, char* nom);
void sauvegarde_matrice_nbrhabitant(t_cases** tabcases, char* nom);
void sauvegarde_matrice_capacite_eau(t_cases** tabcases, char* nom);
void sauvegarde_matrice_capacite_elec(t_cases** tabcases, char* nom);

char* saisie_sauvegarde();
char* saisie_chargement();

t_ville* init_ville();
t_ville* chargement_info_ville();

void modification_niveau_bat(t_ville* V);


///-----------------------------------------------------

Graphe* CreerGraphe();
t_ville * lire_graphe(t_ville* V);
t_ville* init_ville();
Graphe* init(Graphe* g, int dep_L, int dep_C);
Graphe* CreerArete(Graphe* g,int s1_L,int s1_C,int s2_L,int s2_C);

void djikstra(Graphe* g, int dep_L, int dep_C);

void minimum(Graphe* g, int* imin_L, int* imin_C);
void minimum_eau(t_ville* V, int* imin_L, int* imin_C);

void dist_eau(t_ville* V);


#endif // HEADER_H_INCLUDED