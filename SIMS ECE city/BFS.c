#include "header.h"

int BFS(t_ville* V,Graphe* ungraph, int dep_L, int dep_C)
{
    int departL = dep_L;
    int departC = dep_C;
    t_maillon* mafileL = NULL;
    t_maillon* mafileC = NULL;
    mafileL = ajoutFileDyna(mafileL, creerFileDyna(departL));
    mafileC = ajoutFileDyna(mafileC, creerFileDyna(departC));
    ungraph = marquage(ungraph,departL, departC);
    int connexe = 0;
    while(mafileL != NULL && mafileC != NULL)
    {
        mafileL = supFileDyna(mafileL, &departL);
        mafileC = supFileDyna(mafileC, &departC);
        pArc temp = ungraph->pSommet[departL][departC]->arc;
        while(temp != NULL)
        {
            if(V->tabcases[temp->ligne][temp->colonne].type == 2 || V->tabcases[temp->ligne][temp->colonne].type == 3 || V->tabcases[temp->ligne][temp->colonne].type == 8)
            {
                connexe = 1;
            }
            if(ungraph->pSommet[temp->ligne][temp->colonne]->couleur != 1)
            {
                mafileL = ajoutFileDyna(mafileL, creerFileDyna(temp->ligne));
                mafileC = ajoutFileDyna(mafileC, creerFileDyna(temp->colonne));
                ungraph = marquage(ungraph, temp->ligne, temp->colonne);
                ungraph->pSommet[temp->ligne][temp->colonne]->pred_L = departL;
                ungraph->pSommet[temp->ligne][temp->colonne]->pred_C = departC;
            }
            temp = temp->arc_suivant;
        }
    }
    return connexe;
}

t_maillon* creerMaillon(int x)
{
    t_maillon* Nouv = (t_maillon*)malloc(sizeof(t_maillon));
    Nouv->nbr = x;
    Nouv->next = NULL;
    return Nouv;
}

t_maillon* creerFileDyna(int x)
{
    t_maillon* Nouv = (t_maillon*)malloc(sizeof(t_maillon));
    Nouv->next = NULL;
    Nouv->nbr = x;
    return Nouv;
}

Graphe* marquage(Graphe* ungraph, int smmtL, int smmtC)
{
    ungraph->pSommet[smmtL][smmtC]->couleur = 1;
    return ungraph;
}

//ajoute un element a la file
t_maillon* ajoutFileDyna(t_maillon* UneFile, t_maillon* Nouv)
{
    if(testFileDynaVide(UneFile) == 1)
        return Nouv;
    else
    {
        t_maillon* tpm = UneFile;
        while(tpm->next != NULL)
            tpm = tpm->next;
        tpm->next = Nouv;
        return UneFile;
    }
}

//suprimer un element
t_maillon* supFileDyna(t_maillon* UneFile, int* depile)
{
    if(testFileDynaVide(UneFile) == 1)
    {
        printf("File vide...\n");
        return UneFile;
    }
    else
    {
        t_maillon* tpm = UneFile->next;
        *depile = UneFile->nbr;
        free(UneFile);
        return tpm;
    }

}

//test si la file est vide
int testFileDynaVide(t_maillon* UneFile)
{
    if(UneFile == NULL)
        return 1;
    else
        return 0;
}
