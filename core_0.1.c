#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
// gcc -o core.exe core_X.x.c -lSDL2
// sudo ./core.exe

#define PORT 8080
#define SERVER_IP "192.168.4.1" // Default IP for ESP32 in AP mode

/**
 * @brief This file contains the implementation of a function to send a normalized float value to an ESP32 device.
 * 
 * The function `sendFloat` is designed to send a float value to an ESP32 over a socket connection. 
 * It normalizes the float value to a range of -1 to 1 and sends it in a formatted string if the 
 * difference between the new value and the old value exceeds a specified threshold.
 * 
 * @details
 * - The function checks if the absolute difference between the new value and the old value is greater than 0.1.
 * - If the condition is met, it formats the new value into a string with the specified name and normalization.
 * - The normalized value is calculated by dividing the new value by 2^15.
 * - The formatted string is sent to the ESP32 using the provided socket.
 * - The function returns 1 if the value is sent, otherwise it returns 0.
 * 
 * @param old_value (float) The previous float value to compare against.
 * @param new_value (float) The new float value to be sent if the condition is met.
 * @param name (char *) A string representing the name or identifier associated with the value.
 * @param sock (int) The socket descriptor used for sending the data.
 * 
 * @return Returns 1 if the value is sent successfully, otherwise returns 0.
 * 
 * @note The function assumes that the socket connection is already established and valid.
 * 
 * @warning Ensure that the buffer size for `float_data_to_esp` is sufficient to hold the formatted string.
 * 
 * @example
 * float old_val = 0.5;
 * float new_val = 0.7;
 * char *name = "Sensor1";
 * int socket = 3; // Example socket descriptor
 * int result = sendFloat(old_val, new_val, name, socket);
 * if (result) {
 *     printf("Value sent successfully.\n");
 * } else {
 *     printf("No significant change in value.\n");
 * }
 */ 
int sendFloat(float old_value, float new_value, char *name, int sock) {
    float sensibility = 0.05;
    int max_value = pow(2,15);
    
    // si la differance entre avant et apres est superieur à 5% du max
    if (abs(new_value - old_value) > sensibility*max_value) {
        char float_data_to_esp[50];
        sprintf(float_data_to_esp, "%s:%.2f\n", name, new_value/max_value); // normaliser de 1 à -1 avec 2 chiffre sign
        printf("%s", float_data_to_esp);
        send(sock, float_data_to_esp, strlen(float_data_to_esp), 0);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/**
 * @brief Handles button press events from an SDL controller and sends corresponding data to an ESP device.
 * 
 * This function processes SDL controller button press events and sends a specific string
 * to the ESP device over a socket connection, depending on the button pressed.
 * 
 * @param event (type: SDL_Event) The SDL event containing information about the button press.
 * @param sock (int) The socket descriptor used for sending the data.
 * 
 * The function supports the following buttons:
 * - SDL_CONTROLLER_BUTTON_A: Sends "CroixP\n" (Cross button pressed).
 * - SDL_CONTROLLER_BUTTON_B: Sends "RondP\n" (Circle button pressed).
 * - SDL_CONTROLLER_BUTTON_X: Sends "CarreP\n" (Square button pressed).
 * - SDL_CONTROLLER_BUTTON_Y: Sends "TriangleP\n" (Triangle button pressed).
 * - SDL_CONTROLLER_BUTTON_BACK: Sends "SelectP\n" (Select button pressed).
 * - SDL_CONTROLLER_BUTTON_START: Sends "StartP\n" (Start button pressed).
 * - SDL_CONTROLLER_BUTTON_LEFTSHOULDER: Sends "L1P\n" (L1 button pressed).
 * - SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: Sends "R1P\n" (R1 button pressed).
 * - SDL_CONTROLLER_BUTTON_LEFTSTICK: Sends "L3P\n" (L3 button pressed).
 * - SDL_CONTROLLER_BUTTON_RIGHTSTICK: Sends "R3P\n" (R3 button pressed).
 * - SDL_CONTROLLER_BUTTON_DPAD_UP: Sends "HautP\n" (D-pad up pressed).
 * - SDL_CONTROLLER_BUTTON_DPAD_DOWN: Sends "BasP\n" (D-pad down pressed).
 * - SDL_CONTROLLER_BUTTON_DPAD_LEFT: Sends "GaucheP\n" (D-pad left pressed).
 * - SDL_CONTROLLER_BUTTON_DPAD_RIGHT: Sends "DroitP\n" (D-pad right pressed).
 * - SDL_CONTROLLER_BUTTON_GUIDE: Sends "PsP\n" (PS button pressed).
 * - SDL_CONTROLLER_BUTTON_MISC1: Sends "TouchpadP\n" (Touchpad button pressed).
 * 
 * If the PS button (SDL_CONTROLLER_BUTTON_GUIDE) is pressed, the application is stopped.
 * 
 * @note The function uses the `send` function to transmit data over a socket.
 *       Ensure the `sock` variable is properly initialized and connected before calling this function.
 */
int press_button(SDL_Event event, int sock) {
    char *data_to_esp = "";
    switch (event.cbutton.button){
        case SDL_CONTROLLER_BUTTON_A : // Bouton Croix appuyé
            data_to_esp = "CroixP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_B : // Bouton Rond appuyé
            data_to_esp = "RondP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_X : // Bouton Carré appuyé
            data_to_esp = "CarreP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_Y : // Bouton Triangle appuyé
            data_to_esp = "TriangleP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_BACK : // Bouton Select appuyé
            data_to_esp = "SelectP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_START : // Bouton Start appuyé
            data_to_esp = "StartP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER : // Bouton L1 appuyé
            data_to_esp = "L1P\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER : // Bouton R1 appuyé
            data_to_esp = "R1P\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK : // Bouton L3 appuyé
            data_to_esp = "L3P\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK : // Bouton R3 appuyé
            data_to_esp = "R3P\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP : // Bouton haut appuyé
            data_to_esp = "HautP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN : // Bouton bas appuyé
            data_to_esp = "BasP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT : // Bouton gauche appuyé
            data_to_esp = "GaucheP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT : // Bouton droit appuyé
            data_to_esp = "DroitP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_GUIDE : // Bouton PS appuyé
            data_to_esp = "PsP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            // Stoppe l'application
            break;
        case SDL_CONTROLLER_BUTTON_MISC1 : // Bouton Touchpad appuyé
            data_to_esp = "TouchpadP\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        
        default:
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

/**
 * @brief Handles joystick events and processes input from the controller's axes.
 * 
 * This function processes SDL joystick events and maps the input values from 
 * the controller's axes to corresponding variables. It also sends the processed 
 * values to a specified socket using the `sendFloat` function.
 * 
 * @param event (type: SDL_Event) The SDL event containing joystick axis data.
 * @param sock (int) The socket descriptor used for sending the data.
 * 
 * The function handles the following axes:
 * - SDL_CONTROLLER_AXIS_LEFTX: Left joystick horizontal axis.
 * - SDL_CONTROLLER_AXIS_LEFTY: Left joystick vertical axis.
 * - SDL_CONTROLLER_AXIS_RIGHTX: Right joystick horizontal axis.
 * - SDL_CONTROLLER_AXIS_RIGHTY: Right joystick vertical axis.
 * - SDL_CONTROLLER_AXIS_TRIGGERLEFT: Left trigger axis.
 * - SDL_CONTROLLER_AXIS_TRIGGERRIGHT: Right trigger axis.
 * 
 * For each axis, the function:
 * - Converts the axis value to a float.
 * - Sends the value to a socket with a specific identifier using `sendFloat`.
 * - Updates the corresponding variable with the new value.
 * 
 * If the axis does not match any of the handled cases, the function does nothing.
 */
int joystick(SDL_Event event, int sock) {
    float left_joy_x_value = 0.0;
    float left_joy_y_value = 0.0;
    float right_joy_x_value = 0.0;
    float right_joy_y_value = 0.0;
    float press_L2_value = 0.0;
    float press_R2_value = 0.0;
    float value_LX, value_LY, value_RX, value_RY, value_L2, value_R2;
    
    switch (event.caxis.axis){
    case SDL_CONTROLLER_AXIS_LEFTX: // Joystick gauche X
        value_LX = (float)(event.caxis.value);
        sendFloat(left_joy_x_value, value_LX, "JGX", sock);
        break;
    case SDL_CONTROLLER_AXIS_LEFTY: // Joystick gauche Y
        value_LY = (float)(event.caxis.value);
        sendFloat(left_joy_y_value, value_LY, "JGY", sock);
        break;
    case SDL_CONTROLLER_AXIS_RIGHTX: // Joystick droit X
        value_RX = (float)(event.caxis.value);
        sendFloat(right_joy_x_value, value_RX, "JDX", sock);
        break;
    case SDL_CONTROLLER_AXIS_RIGHTY: // Joystick droit Y
        value_RY = (float)(event.caxis.value);
        sendFloat(right_joy_y_value, value_RY, "JDY", sock);
        break;
    case SDL_CONTROLLER_AXIS_TRIGGERLEFT: // Gâchette gauche
        value_L2 = (float)(event.caxis.value);
        sendFloat(press_L2_value, value_L2, "GG", sock);
        press_L2_value = value_L2;
        break;
    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT: // Gachette droite
        value_R2 = (float)(event.caxis.value);
        sendFloat(press_R2_value, value_R2, "GD", sock);
        press_R2_value = value_R2;
        break;
    default:
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Handles the release of buttons on an SDL controller and sends corresponding data to an ESP device.
 *
 * This function processes SDL controller button release events and sends a specific string
 * to the ESP device over a socket connection, indicating which button was released.
 *
 * @param event (type: SDL_Event) The SDL event containing information about the button release.
 * @param sock (int) The socket descriptor used for sending the data.
 * 
 * The function supports the following buttons:
 * - SDL_CONTROLLER_BUTTON_A: Sends "CroixR\n" for the A button release.
 * - SDL_CONTROLLER_BUTTON_B: Sends "RondR\n" for the B button release.
 * - SDL_CONTROLLER_BUTTON_X: Sends "CarreR\n" for the X button release.
 * - SDL_CONTROLLER_BUTTON_Y: Sends "TriangleR\n" for the Y button release.
 * - SDL_CONTROLLER_BUTTON_BACK: Sends "SelectR\n" for the Back button release.
 * - SDL_CONTROLLER_BUTTON_START: Sends "StartR\n" for the Start button release.
 * - SDL_CONTROLLER_BUTTON_LEFTSHOULDER: Sends "L1R\n" for the Left Shoulder button release.
 * - SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: Sends "R1R\n" for the Right Shoulder button release.
 * - SDL_CONTROLLER_BUTTON_LEFTSTICK: Sends "L3R\n" for the Left Stick button release.
 * - SDL_CONTROLLER_BUTTON_RIGHTSTICK: Sends "R3R\n" for the Right Stick button release.
 * - SDL_CONTROLLER_BUTTON_DPAD_UP: Sends "HautR\n" for the D-Pad Up button release.
 * - SDL_CONTROLLER_BUTTON_DPAD_DOWN: Sends "BasR\n" for the D-Pad Down button release.
 * - SDL_CONTROLLER_BUTTON_DPAD_LEFT: Sends "GaucheR\n" for the D-Pad Left button release.
 * - SDL_CONTROLLER_BUTTON_DPAD_RIGHT: Sends "DroiteR\n" for the D-Pad Right button release.
 * - SDL_CONTROLLER_BUTTON_GUIDE: Sends "PsR\n" for the Guide button release.
 * - SDL_CONTROLLER_BUTTON_MISC1: Sends "TouchpadR\n" for the Touchpad button release.
 *
 * If the button is not recognized, the function does nothing.
 *
 * @note The function uses the `send` function to transmit data over a socket.
 *       Ensure the socket (`sock`) and the `data_to_esp` variable are properly initialized
 *       before calling this function.
 */
int release_button(SDL_Event event, int sock) {
    char *data_to_esp = "";
    switch (event.cbutton.button){
        case SDL_CONTROLLER_BUTTON_A : // Bouton Croix relâché
            data_to_esp = "CroixR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_B : // Bouton Rond relâché
            data_to_esp = "RondR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_X : // Bouton Carré relâché
            data_to_esp = "CarreR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_Y : // Bouton Triangle relâché
            data_to_esp = "TriangleR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_BACK : // Bouton Select relâché
            data_to_esp = "SelectR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_START : // Bouton Start relâché
            data_to_esp = "StartR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER : // Bouton L1 relâché
            data_to_esp = "L1R\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER : // Bouton R1 relâché
            data_to_esp = "R1R\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK : // Bouton L3 relâché
            data_to_esp = "L3R\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK : // Bouton R3 relâché
            data_to_esp = "R3R\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP : // Bouton haut relâché
            data_to_esp = "HautR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN : // Bouton bas relâché
            data_to_esp = "BasR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT : // Bouton gauche relâché
            data_to_esp = "GaucheR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT : // Bouton droit relâché
            data_to_esp = "DroiteR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        case SDL_CONTROLLER_BUTTON_GUIDE : // Bouton PS relâché
            data_to_esp = "PsR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            // close(sock);
            // exit(0);
            break;
        case SDL_CONTROLLER_BUTTON_MISC1 : // Bouton Touchpad relâché
            data_to_esp = "TouchpadR\n";
            send(sock, data_to_esp, strlen(data_to_esp), 0);
            break;
        default:
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
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
    printf("Manette detecter : %s\nConnexion à l'ESP32...\n", SDL_GameControllerName(controller));
    
    // Initialisation de la connexion avec l'ESP32
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erreur de creation socket\n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    
    // Convertit l'adresse IP V4 et V6 en forme binaire
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("Address invalid/ Address non supportee\n");
        return -1;
    }
    
    // Connect à l'ESP32
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Echouée\n");
        return -1;
    }
    printf("Connexion établie avec l'ESP32 !\n");
    
    
    SDL_GameControllerRumble(controller, 0.5, 1, 500); // Fait vibrer la manette
    SDL_GameControllerSetLED(controller, 0x00, 0xFF, 0x00); // Allume la LED de la manette en vert
    
    // Boucle principale
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_CONTROLLERAXISMOTION: // Mouvement des joystick
                joystick(event, sock);
                break;
            
            case SDL_CONTROLLERBUTTONDOWN: // Boutons appuyés
                press_button(event, sock);
                break;
            
            case SDL_CONTROLLERBUTTONUP: // Boutons relâchés
                release_button(event, sock);
                break;
            
            case SDL_QUIT: // Quitte l'application
                printf("SDL_QUIT trigger\n");
                running = 0;
                break;
            }
        }
    }
    
    // Fermeture et nettoyage
    printf("sortie du programme\n");
    SDL_GameControllerClose(controller);
    SDL_Quit();
    return 0;
}