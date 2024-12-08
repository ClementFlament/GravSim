#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct {
    int id;   // Nom de la planète
    double x, y, z;     // Position
    double vx, vy, vz;   // Vitesse
    double ax, ay, az;   // Acceleration
    double mass;     // Masse
} Planet;

typedef struct _PlanetsList{
    Planet p;       // Informations de la planète
    struct _PlanetsList *next;   // Prochaine planète
} PlanetsList;

void calc_force(Planet *p1, Planet *p2, double G); // Calcule l'accélération
void update_coor(Planet *p, int T); // Dérive l'accélération en vitesse puis mets à jour les positions
void print_planet_coor(Planet p); // Affiche le nom de la planète et ses coordonées
Planet create_planet(); // Fonction qui retourne un objet de type Planet
PlanetsList* init_planet(int nbr_planet, int create_star); // Initialise la création des planètes
void free_planets(PlanetsList* element);

#endif // SIMULATION_H
