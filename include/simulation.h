#ifndef SIMULATION_H
#define SIMULATION_H

// Structure contenant les propriétés d'une planète
typedef struct
{
    int id;            // Nom de la planète
    double x, y, z;    // Position
    double vx, vy, vz; // Vitesse
    double ax, ay, az; // Acceleration
    double mass;       // Masse
} Planet;

// Structure pour créer une liste chainée de planètes
typedef struct _PlanetsList
{
    Planet p;                  // Informations de la planète
    struct _PlanetsList *next; // Prochaine planète
} PlanetsList;

// Structure pour passer des arguments aux threads
typedef struct
{
    PlanetsList *current; // La planète pour laquelle on calcule la force
    PlanetsList *galaxy;  // La liste des planètes
    int start_id;         // Index de début des planètes à traiter
    int end_id;           // Index de fin des planètes à traiter
    double G;             // Constante de gravité
    double T;             // Unité de temps
} ThreadData;

void calc_force(Planet *p1, Planet *p2, double G);         // Calcule l'accélération
void update_coor(Planet *p, int T);                        // Dérive l'accélération en vitesse puis mets à jour les positions
void print_planet_coor(Planet p);                          // Affiche le nom de la planète et ses coordonées
Planet create_planet();                                    // Fonction qui retourne un objet de type Planet
PlanetsList *init_planet(int nbr_planet, int create_star); // Initialise la création des planètes
void free_planets(PlanetsList *element);
void *calc_gravitational_forces(void *arg);

#endif // SIMULATION_H
