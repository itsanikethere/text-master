#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

short int charReading;
FILE *filePointer;

void clearBuffer()
{
    int charReading;
    while ((charReading = getchar()) != '\n' && charReading != EOF)
    {
    }
}

void showBanner(short int functionOption)
{
    if (functionOption == 0 /*For displaying menu banner*/)
    {
        filePointer = fopen("src/1_banner.txt", "r");

        charReading = (short int)fgetc(filePointer);
        while (charReading != EOF)
        {
            fputc(charReading, stdout);
            charReading = (short int)fgetc(filePointer);
        }
        fclose(filePointer);
    }
    else if (functionOption == 1 /*For displaying program exit banner*/)
    {
        printf("\n");
        filePointer = fopen("src/2_exit_banner.txt", "r");

        charReading = (short int)fgetc(filePointer);
        while (charReading != EOF)
        {
            fputc(charReading, stdout);
            charReading = (short int)fgetc(filePointer);
        }
        fclose(filePointer);
        getchar();
    }
    else if (functionOption == 2 /*For displaying source banner*/)
    {
        filePointer = fopen("src/3_source_banner.txt", "r");

        charReading = (short int)fgetc(filePointer);
        while (charReading != EOF)
        {
            fputc(charReading, stdout);
            charReading = (short int)fgetc(filePointer);
        }
        fclose(filePointer);
    }
}

void showInstruction(short int functionOption)
{
    if (functionOption == 0 /*For displaying encrypt/decrypt instruction*/)
    {
        filePointer = fopen("src/4_encrypt_decrypt_instruction.txt", "r");

        charReading = (short int)fgetc(filePointer);
        while (charReading != EOF)
        {
            fputc(charReading, stdout);
            charReading = (short int)fgetc(filePointer);
        }
        fclose(filePointer);
    }
    else if (functionOption == 1 /*For displaying clipboard copy instruction*/)
    {
        filePointer = fopen("src/5_clipboard_copy_instruction.txt", "r");

        charReading = (short int)fgetc(filePointer);
        while (charReading != EOF)
        {
            fputc(charReading, stdout);
            charReading = (short int)fgetc(filePointer);
        }
        fclose(filePointer);
    }
}

void showLogs(short int functionOption)
{
    if (functionOption == 0 /*For viewing logs*/)
    {
        if (access("var/logs/logs.txt", F_OK) == 0)
        {
            filePointer = fopen("var/logs/logs.txt", "r");

            if (fgetc(filePointer) == EOF)
            {
                printf("\n-----> NO LOGS TO DISPLAY :( <-----\n");
            }

            charReading = (short int)fgetc(filePointer);
            while (charReading != EOF)
            {
                fputc(charReading, stdout);
                charReading = (short int)fgetc(filePointer);
            }
            fclose(filePointer);

            printf("\n-----> END :) <-----\n");
        }
        else
        {
            printf("\n-----> NO LOGS TO DISPLAY :( <-----\n");
        }
    }
    else if (functionOption == 1 /*For clearing logs*/)
    {
        if (remove("var/logs/logs.txt") == 0)
        {
            printf("\n-----> CLEANING LOGS :) <-----\n");
        }
        else
        {
            printf("\n-----> LOGS ALREADY CLEAN :) <-----\n");
        }
    }
}

void showSource()
{
    showBanner(2 /*For displaying source banner*/);

    printf("\n\n[-----> textm.h HEADER FILE <-----]\n");
    filePointer = fopen("include/textm.h", "r");

    charReading = (short int)fgetc(filePointer);
    while (charReading != EOF)
    {
        fputc(charReading, stdout);
        charReading = (short int)fgetc(filePointer);
    }
    fclose(filePointer);
    printf("\n");

    printf("\n\n[-----> main.c SOURCE FILE <-----]\n");
    filePointer = fopen("main.c", "r");

    charReading = (short int)fgetc(filePointer);
    while (charReading != EOF)
    {
        fputc(charReading, stdout);
        charReading = (short int)fgetc(filePointer);
    }
    fclose(filePointer);
    printf("\n");

    printf("\n-----> END :) <-----\n");
}

void copyToClipboard(char userInput[])
{
    showInstruction(1 /*For displaying clipboard copy instruction*/);

    short int userChoice, loopStop = 0;
    while (loopStop == 0)
    {
        scanf("%hd", &userChoice);
        clearBuffer();

        switch (userChoice)
        {
        case 1:
            filePointer = fopen("var/temp/temp.txt", "w");
            printf("\n-----> CREATING TEMPORARY FILE :) <-----\n");

            fprintf(filePointer, "%s", &userInput[0]);
            fclose(filePointer);

            system("clip < var/temp/temp.txt");
            printf("\n-----> COPYING TEXT TO CLIPBOARD :) <-----\n");

            remove("var/temp/temp.txt");
            printf("\n-----> DELETING TEMPORARY FILE :) <-----\n");

            loopStop++;
            break;

        case 2:
            loopStop++;
            break;

        default:
            printf("\n[INVALID INPUT, PLEASE TRY AGAIN]\nYOUR INPUT IS --> ");
            break;
        }
    }
}

void showOutput(char userInput[], short int functionOption)
{
    char systemTime[100];
    time_t temp = time(0);

    strftime(systemTime, 100, "%d-%m-%Y %H:%M:%S", localtime(&temp));

    filePointer = fopen("var/logs/logs.txt", "a");
    if (functionOption == 0 /*For displaying and logging encryption*/)
    {
        fprintf(filePointer, "\n[ENCRYPTION LOG --> %s]\n[ENCRYPTED TEXT --> %s]\n", &systemTime[0], &userInput[0]);
        fprintf(stdout, "\n[ENCRYPTION DONE --> %s]\n[ENCRYPTED TEXT --> %s]\n\n", &systemTime[0], &userInput[0]);
    }
    else if (functionOption == 1 /*For displaying and logging decryption*/)
    {
        fprintf(filePointer, "\n[DECRYPTION LOG --> %s]\n[DECRYPTED TEXT --> %s]\n", &systemTime[0], &userInput[0]);
        fprintf(stdout, "\n[DECRYPTION DONE --> %s]\n[DECRYPTED TEXT --> %s]\n\n", &systemTime[0], &userInput[0]);
    }
    fclose(filePointer);
    copyToClipboard(userInput);
}

void startEncryptDecrypt(short int functionOption)
{
    showInstruction(0 /*For displaying encryption/decryption instruction*/);

    char userInput[1000], *charPointer = &userInput[0];
    fgets(userInput, 1000, stdin);
    userInput[strcspn(userInput, "\n")] = 0; /*For removing '\n' recorded by fgets while pressing enter*/

    if (functionOption == 0 /*For encrypting text*/)
    {
        while (*charPointer != '\0')
        {
            *charPointer = *charPointer + 3;
            charPointer++;
        }
        showOutput(userInput, 0);
    }
    else if (functionOption == 1)
    {
        while (*charPointer != '\0' /*For decrypting text*/)
        {
            *charPointer = *charPointer - 3;
            charPointer++;
        }
        showOutput(userInput, 1);
    }
}