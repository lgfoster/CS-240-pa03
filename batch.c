/**
 * @file main.c
 * @author Luke Foster -- fost4403@vandals.uidaho.edu
 * @brief Assignment 3. This program is designed to emulate a batch function in the operating system.
 *        The program opens a file passed as an argument and it will then execute up to 4 children processes using
 *        the arguments found in the file. If the number of children processes drops below 4, the parent will attempt 
 *        to generate more children.
 * @version 0.1
 * @date 2023-02-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct WORD {
    int loc, len;
} WORD;

int makeArg(char s[], char **args[]);

int findLength(char *scanPtr);

int main(int argNum, char *argvMain[])
{
    char **argv, str[256];
    int argc, i, numExe = 0;
    pid_t pid, status, pidW;

    if(argNum != 2)
    {
        return -1;
    }

    FILE *fp = fopen(argvMain[1], "r");

    if(fp == NULL)
    {
        return -1;
    }

    while(!feof(fp))
    {
        fgets(str, 256, fp);

        str[strcspn(str, "\n")] = 0; /* Remove the \n added by fgets */

        argc = makeArg(str, &argv);

        if(argc == -1)
        {
            printf("Error parsing tokens! Closing program...\n");
            exit(1);
        }

        pid = fork();
        numExe++;

        if(pid < 0)
        {
            exit(1);
        }
        else if(pid != 0) /* Parent process */
        {
            if(numExe == 4) /* Wait for a child to finish if 4 are running */
            {
                pidW = wait(&status);
                numExe--;
            }
        }
        else if(pid == 0) /* Child process */
        { 
            if(execvp(argv[0], argv) < 0)
            {
                exit(1); 
            }
        }

        for(i = 0; i < argc; i++) /* Free memory on arguments */
        {
            free(argv[i]);
        }
        
        free(argv);
    }

    while((pidW = wait(&status)) > 0 ); /* Wait for all children to finish */

    return 0;
}


/**
 * @brief This function creates tokens in memory using an pointer to an array of char pointers
 * 
 * @param s String to be parsed and broken into tokens
 * @param args pointer to array of char pointers. Used to store the arguments found
 * @return int Number of arguments found
 */
int makeArg(char s[], char ***args)
{
    int numTokens = 0, length = 0, location = 0;

    char delims[] = " \t\0";
    char delimSemi[] = " \t\0;";

    WORD words[] = malloc(sizeof(WORD) * 5);

    char *scanPtr = &s[0];

    while (*scanPtr != '\0') /* Find number of tokens passed with s[] */
    {
        if(*scanPtr != ' ' && *scanPtr != '\t')
        {
            numTokens++;

            while((*scanPtr != ' ' && *scanPtr != '\t') && *scanPtr != '\0')
            {
                scanPtr++;
            }
        }
        else
        {
            scanPtr++;
        }
    }

    if(numTokens == 0)
    {
        return -1;
    }

    scanPtr = &s[0]; /* Reset scanner */

    *args = (char **) calloc(numTokens + 1, sizeof(char *)); /* Allocate space for char * and NULL */

    int lenToken, argNum = 0;

    while(*scanPtr != '\0') /* Create c-strings */
    {
        if(*scanPtr != ' ' && *scanPtr != '\t')
        {
            lenToken = findLength(scanPtr);

            (*args)[argNum] = malloc(sizeof(char) * (lenToken));

            strncpy((*args)[argNum], scanPtr, lenToken);
            (*args)[argNum][lenToken - 1] = '\0';

            argNum++;
        }

        while((*scanPtr != ' ' && *scanPtr != '\t') && *scanPtr != '\0')
        {
            scanPtr++;
        }


        if(*scanPtr != '\0') /* Move one more space*/
            scanPtr++;
    }

    return numTokens;
}

/**
 * @brief Determines the length of the found token
 * 
 * @param scanPtr Scanner pointing at current element in the string 
 * @return int Length of the token found
 */
int findLength(char *scanPtr)
{   
    int lenToken = 1;

    char *lengthPtr = scanPtr;

    while((*lengthPtr != ' ' && *lengthPtr != '\t') && *lengthPtr != '\0')
    {
        lengthPtr++;
        lenToken++;
    }

    return lenToken;
}
