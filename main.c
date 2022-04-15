#include <stdio.h>
#include <stdlib.h>
#include "include/textm.h"

void main()
{
    system("cls");
    showBanner(0 /*For displaying menu banner.*/);

    short int userChoice, loopStop = 0;
    while (loopStop == 0)
    {
        scanf("%hd", &userChoice);
        clearBuffer(); /*For clearing input buffer*/

        switch (userChoice)
        {
        case 1:
            system("cls");
            startEncryptDecrypt(0 /*For encrypting text*/);
            loopStop++;
            break;

        case 2:
            system("cls");
            startEncryptDecrypt(1 /*For decrypting text*/);
            loopStop++;
            break;

        case 3:
            system("cls");
            showLogs(1 /*For clearing logs*/);
            loopStop++;
            break;

        case 4:
            system("cls");
            showLogs(0 /*For viewing logs*/);
            loopStop++;
            break;

        case 5:
            system("cls");
            showSource();
            loopStop++;
            break;

        case 6:
            loopStop++;
            break;

        default:
            printf("\n[INVALID INPUT, PLEASE TRY AGAIN]\nYOUR INPUT IS --> ");
            break;
        }
    }
    showBanner(1 /*For displaying exit banner*/);
}