#include <raylib.h>
#include "graphic.h"

// Fonction de prompt aux utilisateurs
/*
    /!\ Doit être défini dans une fenêtre ! /!\
    Prend en entrée un pointeur vers un message
    Créer un prompt qui affiche le message
    Retourne la valeur convertie en entier
*/
int ask_user(const char *message)
{
    char input[5] = "";
    int letterCount = 0;
    int result = -1;

    // Boucle de lecture
    while (true)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Affichage du message et des instructions
        DrawText(message, 10, 10, 20, BLACK);
        DrawText("Saisir [ENTER] une fois terminé", 10, 50, 20, DARKGRAY);

        // Affiche la saisie
        DrawRectangle(10, 80, 240, 30, LIGHTGRAY);
        DrawText(input, 15, 85, 20, BLACK);

        EndDrawing();

        // Vérifie les événements (si une touche est pressé)
        int key = GetCharPressed();
        while (key > 0)
        { // Index les touches
            if (key >= 32 && key <= 126 && letterCount < 4)
            { // Filtre les touches et ne garde que celles qui sont affichables
                input[letterCount] = (char)key;
                input[letterCount + 1] = '\0'; // Null pour cloturer la chaine de carractère
                letterCount++;
            }
            key = GetCharPressed();
        }

        // Implémentation de la touche Backspace
        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            input[--letterCount] = '\0'; // Retire le dernier élément de la pile
        }

        // Vérifie si la touche ENTER est saisie pour sortir de la boucle
        if (IsKeyPressed(KEY_ENTER))
        {
            result = atoi(input); // Convertie le résultat en entier
            break;
        }
    }

    return result;
}
