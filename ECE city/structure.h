#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef struct ville
{
    int argent;
    int hab;
    int cap_eau;
    int cap_elec;
    float temps;
    Graphe* eau;
    Graphe* elec;

}t_ville;

typedef struct cases_
{
    int ligne;
    int colonne;
    int cases;
}t_cases;

#endif // STRUCTURE_H_INCLUDED
