#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

/*
* This function is called when the "help" command is entered.
* It writes a response to the response buffer.
* The argument is the rest of the string after the command name.
*/
int help(char* arg, char* response) {
    while (*arg == ' ') arg++;

    if (strcmp(arg, "calc") == 0) {
        sprintf(response, "Calculates the result of a op b. Usage: calc a op b\n");
    } else if (strcmp(arg, "sort") == 0) {
        sprintf(response, "Sorts a list of numbers. Usage: sort n1 n2 n3 ...\n");
    } else if (strcmp(arg, "") == 0) {
        sprintf(response, "Available commands: help, calc, sort\n");
    } else {
        sprintf(response, "This command does not exist\n");
    }
    return 0;
}

int calc(char* arg, char* response) {
    int a, b;
    char op;
    if (sscanf(arg, "%d %c %d", &a, &op, &b) == 3) {
        switch (op) {
            case '+': sprintf(response, "%d\n", a + b); break;
            case '-': sprintf(response, "%d\n", a - b); break;
            case '*': sprintf(response, "%d\n", a * b); break;
            case '/': 
                if (b != 0) sprintf(response, "%d\n", a / b);
                else strcpy(response, "Error: Division by zero.\n");
                break;
            default: strcpy(response, "Error: Invalid operator.\n");
        }
    } else {
        strcpy(response, "Error: Invalid format. Use: calc a op b\n");
    }
    return 0;
}

int sort(char* arg, char* response) {
    int numbers[100], n = 0;
    char *token = strtok(arg, " ");
    while (token != NULL && n < 100) {
        numbers[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    // Simple bubble sort implementation
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (numbers[i] > numbers[j]) {
                int tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
    }

    strcpy(response, "");
    for (int i = 0; i < n; i++) {
        char num[12];
        sprintf(num, "%d ", numbers[i]);
        strcat(response, num);
    }
    int len = strlen(response);
    if (len > 0) response[len - 1] = '\n'; // Remove trailing space
    return 0;
}

/*
* This function processes the command in the buffer and writes the response to the response buffer.
* It uses the commandFunc array to find the function to call based on the command name.
* The command name is the first word in the buffer, and the rest of the buffer is the argument to the command.
*/
int process(char* buf, char* response) {
    CommandFunc commands[] = {help, calc, sort};
    char* commandNames[] = {"help", "calc", "sort"};
    int numCommands = sizeof(commands) / sizeof(commands[0]);

    for (int i = 0; i < numCommands; i++) {
        int cmdLength = strlen(commandNames[i]);
        if (strncmp(buf, commandNames[i], cmdLength) == 0 && (buf[cmdLength] == ' ' || buf[cmdLength] == '\0')) {
            char* arg = buf + cmdLength;
            while (*arg == ' ') arg++; // skip any spaces after the command
            if (*arg == '\n') *arg = '\0'; // remove newline if present
            return commands[i](arg, response);
        }
    }

    strcpy(response, "Invalid command\n");
    return -1;
}

