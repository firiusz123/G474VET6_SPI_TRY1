/*
 * Magnet.c
 *
 *  Created on: Jul 31, 2024
 *      Author: firiusz
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to handle the MAGNET command and send a response
char* handleMagnetCommand(const char *command) {
    int number;
    char response[32]; // Ensure this buffer is large enough to hold the response

    // Define the expected format of the command string
    const char *expectedFormat = "MAGNET#%d$";

    // Check if the command matches the expected format and extract the number
    int ret = sscanf(command, expectedFormat, &number);

    // Allocate memory for the response
    char *responseStr = (char *)malloc(32); // Allocate sufficient memory for the response
    if (responseStr == NULL) {
        return NULL; // Allocation failed
    }

    if (ret <= 4 && ret >= 0) { // Successfully extracted the number
        // Format the response
        snprintf(responseStr, 32, "MAGNET#%d#OK$", number);
    } else {
        // Failed to extract the number, prepare an error response
        snprintf(responseStr, 32, "MAGNET#ERROR$");
    }

    return responseStr;
}

