#include "simulation.h"
#include "graphic.h"
#include <stdio.h>
#include <raylib.h>


#define SCREEN_WIDTH 1280    // Largeur de la fenêtre
#define SCREEN_HEIGHT 720    // Hauteur de la fenêtre
#define SCALE 0.01          // Facteur d'échelle pour ajuster la taille de l'affichage

#define G 6.674e-11          // Constante de gravité universelle
#define T 1                  // Unité de temps

int main() {
    int create_star = 0;
    int nbr_planets = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Configuration de la simulation");


    // Demande aux utilisateurs des informations concernant la simulation dans une fenêtre graphique et créer la liste de planètes
    create_star = ask_user("Voulez-vous créer un soleil ? (1 pour oui / 0 pour non): ");
    nbr_planets = ask_user("Saisir le nombre de planètes: ");
    PlanetsList *Galaxy = init_planet(nbr_planets, create_star);

    CloseWindow();



    // Initialisation de Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D - GravSim");

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

            // Réinitialisation de l'accélération
            Reader->p.ax = 0;
            Reader->p.ay = 0;
            Reader->p.az = 0;
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
