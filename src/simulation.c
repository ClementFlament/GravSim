#include "simulation.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Fonction de calcul des forces
/* 
    Prends en entrée deux struct Planet et la constante de gavité
    Calcul la distance entre p1 et p2
    Calcul de la force de gravité en fonction de la distance entre p1 et p2 et leurs masses
    Retourne en passant par des pointeurs l'accélération que vvont subir les deux planètes en entrées
*/
void calc_force(Planet *p1, Planet *p2, double G) {
    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance > 1e-5) {
        double force = (G * p1->mass * p2->mass) / (distance * distance);

        p1->ax += force * dx / distance / p1->mass;
        p1->ay += force * dy / distance / p1->mass;
        p2->ax -= force * dx / distance / p2->mass;
        p2->ay -= force * dy / distance / p2->mass;
    }
}

// Fonction de mise à jour des coordonnées
/* 
    Prends en entrée une struct Planet et l'unité de temps
    Calcul la vitesse en faisant l'intégrale de l'accélération par rapport au temps
    Calcul les coordonnées en faisant l'intégrale de la vitesse par rapport au temps
    Retourne en passant par des pointeurs les nouvelles positions de la planète en entrée
*/
void update_coor(Planet *p, int T) {

    p->vx += p->ax * T;
    p->vy += p->ay * T;

    p->x += p->vx * T;
    p->y += p->vy * T;

    p->ax = 0;
    p->ay = 0;
}

// Print quelques informations dans le terminal
void print_planet_coor(Planet p) {
    printf("Planet ID : %d \nX : %f\nY : %f\nVX : %f\nVY : %f\n\n",
           p.id, p.x, p.y, p.vx, p.vy);
}

// Fonction de création aléatoire de planètes
/* 
    Prends en entrée un ID
    Défini des valeurs aléatoires ou prédéfini
    Affecte à la structure les valeurs choisis
    Retourne une structure de type Planet
*/
Planet create_planet(int i) {

    Planet planet = {
        .id = i,
        .x = rand() % 1000,
        .y = rand() % 1000,
        .mass = (rand() % 1000) * 1e8,
    };
    print_planet_coor(planet);

    return planet;
}

//Fonction de création de la galaxie
/*
    Une galaxie est une liste de planète

    Prend en entrée un entier contenant le nombre de planètes
    Créer une liste chainée d'éléments contenant une structure Planet et un pointeur vers le prochain élément
    Retourne le premier élément de la liste
*/
PlanetsList* init_planet(int nbr_planets) {
    PlanetsList* FirstPlanet = (PlanetsList*)malloc(sizeof(PlanetsList));
    PlanetsList* planetN = FirstPlanet;

    for (int i = 0; i < nbr_planets; i++) {
        planetN->p = create_planet(i);
            if (i < nbr_planets - 1) {
                planetN->next = (PlanetsList*)malloc(sizeof(PlanetsList));
                planetN = planetN->next;
            } else {
                planetN->next = NULL;  
            }
    }

    return FirstPlanet;
}

//Fonction de libération de mémoire
/*
    Prend en entrée une structure PlanetList
    Pour chaque élément, libère l'espace mémoire
    Libère la mémoire alloué dynamiquement
*/
void free_planets(PlanetsList* element) {
    while (element != NULL) {
        PlanetsList* temp = element;
        element = element->next;
        free(temp);
    }
}