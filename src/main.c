#include <raylib.h>
#include "simulation.h"
#include <stdio.h>

#define G 6.674e-11	// Constante de gravité universelle
#define T 1			// Unité de temps

int main() {

    // Création d'un soleil 
    int create_star;
	printf("Voulez vous créer un soleil ? (1 pour oui / 0 pour non)\n");
    scanf("%d", &create_star);

    // Initialisation les planètes 
	printf("Saisir le nombre de planète : ");
	int nbr_planets = 0;
	scanf("%d", &nbr_planets);
    PlanetsList* Galaxy = init_planet(nbr_planets, create_star);

	// Initialisation le nombre d'itération
	printf("Saisir le nombre d'itérations à calculer : ");
	int nbr_iteration = 0;
	scanf("%d", &nbr_iteration);

    // Boucle principale de simulation
    for (int i = 0; i != nbr_iteration; i++) {

        // Calcul des nouvelles forces et mise à jour des coordonnées
		PlanetsList* Current = Galaxy;
        while (Current) {
            PlanetsList* GalaxyReader = Galaxy;
            while (GalaxyReader) {
                if (Current != GalaxyReader) {
                    calc_force(&Current->p, &GalaxyReader->p, G);
                }
                GalaxyReader = GalaxyReader->next;
            }
            update_coor(&Current->p, T);
            Current = Current->next;
        }

        // Affichage et réinitialisation de l'accélération pour chaque point
        PlanetsList* Reader = Galaxy;
        while (Reader) {
            print_planet_coor(Reader->p);
            Reader = Reader->next;
        }

    }

    free_planets(Galaxy);
    return 0;
}

