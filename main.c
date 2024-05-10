#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

int main()
{
    /* Variable Declaration */

    FILE* ptrR;
    int nRead;
    int totCylinder, currPosi, prevPosi;
    int input;
    char quit[] = "QUIT";
    char file[11]; // Assume the input file name is no longer than 10 characters


    do
    {
        int i = 0;
        int rqCylinderList[100];
        int totRequest = 0;

        /* Get input file from the user*/
        printf("\n Disk Scheduler Simulation <Input file>  : ");
        scanf("%s",file);

        if(!( strcmp(quit,file) == 0 ) )
        {
                /* Open the File Reader */
            ptrR = fopen( file, "r");

            if( ptrR == NULL )
            {
                perror(" Error opening the File!!");
            }
            else
            {
                nRead = fscanf(ptrR, "%d %d %d", &totCylinder, &currPosi, &prevPosi);

                /* When Successfully read the main requirements*/
                if( nRead == 3 )
                {
                    while(!feof(ptrR))
                    {
                        fscanf(ptrR, "%d", &input);
                        rqCylinderList[i]= input;
                        i++;
                        totRequest++;
                    }

                }

                /* Error Checking while Reading file */
                if( ferror(ptrR) )
                {
                    perror("Error reading from file\n");
                }

                /* Close the File Reader*/
                fclose(ptrR);
                ptrR = NULL;


                printf("\n For %s: ", file);

                firstComeFirstServe(currPosi,rqCylinderList,totRequest);
                shortestSeekTimeFirst(totRequest,rqCylinderList,currPosi);
                scan(totCylinder,currPosi,prevPosi,totRequest,rqCylinderList);
                cScan(totCylinder,currPosi,prevPosi,totRequest,rqCylinderList);
                look(totCylinder,currPosi,prevPosi,totRequest,rqCylinderList);
                cLook(totCylinder,currPosi,prevPosi,totRequest,rqCylinderList);

                printf("\n\n"); /* Give space*/

            }

        }
        else
        {
            printf("\n The App is Exiting. \n");
        }

    }
    while( !( strcmp(quit,file) == 0 ) ); /* loop until user enters QUIT */

    return 0;
}