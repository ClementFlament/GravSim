#include <raylib.h>
#include "simulation.h"
#include <stdio.h>

#define SCREEN_WIDTH 1280    // Largeur de la fenêtre
#define SCREEN_HEIGHT 720    // Hauteur de la fenêtre
#define SCALE 0.01          // Facteur d'échelle pour ajuster la taille de l'affichage

#define G 6.674e-11          // Constante de gravité universelle
#define T 1                  // Unité de temps

int main() {
    // Création d'un soleil
    int create_star;
    printf("Voulez-vous créer un soleil ? (1 pour oui / 0 pour non): ");
    scanf("%d", &create_star);

    // Initialisation des planètes
    printf("Saisir le nombre de planètes : ");
    int nbr_planets = 0;
    scanf("%d", &nbr_planets);
    PlanetsList* Galaxy = init_planet(nbr_planets, create_star);

    // Initialisation de Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Simulation Gravitationnelle");

    // Caméra pour la visualisation 3D
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 50.0f, 100.0f }; // Position de la caméra
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     // Cible regardée par la caméra
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         // Orientation verticale
    camera.fovy = 45.0f;                               // Champ de vision vertical
    camera.projection = CAMERA_PERSPECTIVE;            // Projection 3D

    SetTargetFPS(60);

    // Boucle principale 
    while (!WindowShouldClose()) { // Exécution infinie jusqu'à fermeture de la fenêtre

        // Calcul des forces et mise à jour des coordonnées
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

        // Rendu graphique
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Dessin des planètes et du soleil avec échelle
        PlanetsList* Reader = Galaxy;
        while (Reader) {
            float radius = (Reader->p.id == 0) ? 2.0f : 0.5f; // Taille plus grande pour le soleil
            Color color = (Reader->p.id == 0) ? GOLD : BLUE;

            // Dessin des sphères avec échelle appliquée aux coordonnées
            DrawSphere(
                (Vector3){ Reader->p.x * SCALE, Reader->p.y * SCALE, Reader->p.z * SCALE },
                radius, color);


            Reader = Reader->next;
        }

        EndMode3D();

        // Affichage d'informations supplémentaires
        DrawText("3D - Simulateur de Gravité", 10, 10, 20, DARKGRAY);

        DrawFPS(SCREEN_WIDTH - 100, 10);

        EndDrawing();
    }

    // Libération des ressources
    free_planets(Galaxy);
    CloseWindow();

    return 0;
}
