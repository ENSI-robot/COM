#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
// gcc -o manette.exe manette.c -lSDL2
// sudo ./manette.exe


int printJoystick(unsigned char old_value, unsigned char new_value, char *name, char axis) {
    if (abs(new_value - old_value) > 4) {
        printf("Joystick %s - axis %c : %d\n", name, axis, new_value);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    
    printf("Recherche de manettes...\n");
    
    // Vérifie si une manette est connectée
    if (SDL_NumJoysticks() < 1) {
        printf("Aucune manette détectée.\n");
        SDL_Quit();
        return -1;
    }
    
    // Ouvre la  manette
    SDL_GameController *controller = SDL_GameControllerOpen(0);
    if (controller == NULL) {
        printf("Impossible d'ouvrir la manette : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    printf("Manette détectée : %s\n", SDL_GameControllerName(controller));
    
    // Boucle principale
    int running = 1;
    unsigned char left_x_value = 128;
    unsigned char left_y_value = 128;
    unsigned char right_x_value = 128;
    unsigned char right_y_value = 128;
    unsigned char value_LX, value_LY, value_RX, value_RY, press_L2, press_R2;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_CONTROLLERAXISMOTION: // Mouvement des joysticks
                switch (event.caxis.axis){
                case SDL_CONTROLLER_AXIS_LEFTX:
                    value_LX = (unsigned char)((event.caxis.value + 32768) * 255 / 65535);
                    printJoystick(left_x_value, value_LX, "gauche", 'X');
                    break;
                case SDL_CONTROLLER_AXIS_LEFTY:
                    value_LY = (unsigned char)((event.caxis.value + 32768) * 255 / 65535);
                    printJoystick(left_y_value, value_LY, "gauche", 'Y');
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTX:
                    value_RX = (unsigned char)((event.caxis.value + 32768) * 255 / 65535);
                    printJoystick(right_x_value, value_RX, "droit", 'X');
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTY:
                    value_RY = (unsigned char)((event.caxis.value + 32768) * 255 / 65535);
                    printJoystick(right_y_value, value_RY, "droit", 'Y');
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                    press_L2 = (unsigned char)(event.caxis.value * 255 / 32767);
                    printf("Gachette gauche : %d\n", press_L2);
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                    press_R2 = (unsigned char)(event.caxis.value * 255 / 32767);
                    printf("Gachette droite : %d\n", press_R2);
                    break;
                default:
                    break;
                }
                break;
            
            case SDL_CONTROLLERBUTTONDOWN: // Boutons appuyés
                switch (event.cbutton.button){
                case SDL_CONTROLLER_BUTTON_A :
                    printf("Bouton 'Croix' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_B :
                    printf("Bouton 'Rond' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_X :
                    printf("Bouton 'Carré' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_Y :
                    printf("Bouton 'Triangle' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_BACK :
                    printf("Bouton 'Select' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_START :
                    printf("Bouton 'Start' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER :
                    printf("Bouton 'L1' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER :
                    printf("Bouton 'R1' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSTICK :
                    printf("Bouton 'L3' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSTICK :
                    printf("Bouton 'R3' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP :
                    printf("Bouton 'Haut' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN :
                    printf("Bouton 'Bas' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT :
                    printf("Bouton 'Gauche' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT :
                    printf("Bouton 'Droite' appuyé.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_GUIDE :
                    printf("Bouton 'PS' appuyé.\n");
                    exit(0);
                    break;
                case SDL_CONTROLLER_BUTTON_MISC1 :
                    printf("Bouton 'Touchpad' appuyé.\n");
                    break;
                
                default:
                    break;
                }
                break;
            case SDL_CONTROLLERBUTTONUP: // Boutons relâchés
                switch (event.cbutton.button){
                case SDL_CONTROLLER_BUTTON_A :
                    printf("Bouton 'Croix' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_B :
                    printf("Bouton 'Rond' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_X :
                    printf("Bouton 'Carré' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_Y :
                    printf("Bouton 'Triangle' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_BACK :
                    printf("Bouton 'Select' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_START :
                    printf("Bouton 'Start' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER :
                    printf("Bouton 'L1' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER :
                    printf("Bouton 'R1' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSTICK :
                    printf("Bouton 'L3' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSTICK :
                    printf("Bouton 'R3' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP :
                    printf("Bouton 'Haut' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN :
                    printf("Bouton 'Bas' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT :
                    printf("Bouton 'Gauche' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT :
                    printf("Bouton 'Droite' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_GUIDE :
                    printf("Bouton 'PS' relâché.\n");
                    break;
                case SDL_CONTROLLER_BUTTON_MISC1 :
                    printf("Bouton 'Touchpad' relâché.\n");
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT: // Quitte l'application
                running = 0;
                break;
            }
        }
    }
    
    // Fermeture et nettoyage
    SDL_GameControllerClose(controller);
    SDL_Quit();
    return 0;
}
