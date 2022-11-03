#include "header.h"

pSommet* CreerArete(pSommet* sommet,int s1,int s2, int capacit)
{
    if(sommet[s1]->arc==NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;//le sommet adj à arc est s2
        Newarc->capa = capacit;
        Newarc->arc_suivant = NULL;//l'arv suivant est null
        sommet[s1]->arc = Newarc;//l'arc est entre s1 et s2
        return sommet;
    }
    else // Si le sommet a déja un arc
    {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        pArc  temp=sommet[s1]->arc; // Affectation de l'arc déja existant à un arc temporaire
        while(!(temp->arc_suivant==NULL)) // On parcour les arc
        {
            temp=temp->arc_suivant;
        }
        Newarc->sommet=s2; // Affectation de son sommet
        Newarc->capa = capacit;// Affectation de son poid
        Newarc->arc_suivant=NULL;
        ///ici on range les arcs en fonction d'avec qui ils connectent leur sommet, on est dans l'ordre croissant des sommets

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        ///Les sommets sont dans l'ordre croissant, dans le tableau de sommet présent dans la structure graph
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int ordre, s1, s2, capacit;
    char nom;
    if (!ifs)//on blinde
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    fscanf(ifs,"%d\n",&ordre);//
    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets
    graphe->ordre=ordre;
    for(int x = 0; x<ordre; x++)
    {
        fscanf(ifs, "%c", &nom);
        graphe->pSommet[x]->nom = nom;
    }
    graphe->cap = (int**)malloc(ordre* sizeof(int*));
    graphe->flot = (int**)malloc(ordre* sizeof(int*));
    graphe->v = (int*)malloc(ordre * sizeof(int));
    for(int h = 0; h<ordre; h++)
    {
        graphe->cap[h] = (int*)malloc(ordre * sizeof(int));
        graphe->flot[h] = (int*)malloc(ordre * sizeof(int));
    }
    // créer les arêtes du graphe
    for (int i=0; i<ordre; ++i)
    {
        s1 = i;
        graphe->v[i] = 0;
        for(int j = 0; j<ordre; j++)
        {
            s2 = j;
            fscanf(ifs, "%d", &capacit);
            if(capacit != 0)
            {
                graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, capacit);
            }
            graphe->cap[i][j] = capacit;
            graphe->flot[i][j] = 0;
        }
    }

    return graphe;
}

void sourcepuits(int* source, int* puits, Graphe* g)
{
    int test = 0;
    for(int i = 0; i<g->ordre; i++)
    {
        test = 0;
        if(g->pSommet[i]->arc == NULL)
        {
            *puits = g->pSommet[i]->valeur;
        }
        else
        {
            for(int j = 0; j<g->ordre; j++)
            {
                pArc tmp = g->pSommet[j]->arc;
                while(tmp != NULL)
                {
                    if(tmp->sommet == g->pSommet[i]->valeur)
                    {
                        test = 1;
                    }
                    tmp = tmp->arc_suivant;
                }
            }
            if(test == 0)
            {
                *source = g->pSommet[i]->valeur;
            }
        }
    }
}

int dfs(int s, int t, int minimum,Graphe* g)
{
    g->v[s] = 1;
    int sent;

    if (s == t)
    {

        return minimum;
    }
    int a;
    for (int i = 0; i < g->ordre; i++)
    {
        a = g->cap[s][i] - g->flot[s][i];
        if (!g->v[i] && a > 0)
        {

            if(sent = dfs (i, t, min(minimum, a),g))
            {

                g->flot[s][i] += sent;
                g->flot[i][s] -= sent;
                return sent;
            }
        }
    }

    return 0;
}

int min (int x, int y) {
    if(x<y)
        return x;
    else
        return y;

}

int Max(Graphe* g)
{
    int s;
    int t;
    sourcepuits(&s, &t, g);
    int Flot=0;
    int Min;
    while(Min=dfs(s,t,INFINI,g))
    {
        Flot+=Min;
        for(int i=0;i<g->ordre;i++)
        {
            g->v[i]=0;
        }
    }

    return Flot;
}
