#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINI 9999

/* Structure d'un arc*/
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int valeur;
    int capa;
    int flow;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    int nom;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int ordre;
    pSommet* pSommet;
    int** cap;
    int** flot;
    int* v;
} Graphe;

void afficher_successeurs(pSommet * sommet, int num);

void graphe_afficher(Graphe* g);

// créer le graphe
Graphe* CreerGraphe(int ordre);

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int capacit);

int dfs(int s, int t, int minimum,Graphe* g);
int min (int x, int y);
int Max(Graphe* g);

void sourcepuits(int* source, int* puits, Graphe* g);


#endif // GRAPHE_H_INCLUDED
