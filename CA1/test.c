
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){

    /* constant alpha squared, the area of the domain */
    const float alphSqrd     = 0.01;
    const float deltX, deltY = 0.0002;
    const float timeStep     = 0.0000009;
    const int   maxTimeSteps = 1000;

    int h, i, j;

    /* 2D Array of Temperature Values */
    //float *T = (float *)malloc(500 * 500 * sizeof(float));

    float **T;

    T=(float **) malloc(500*sizeof(float *));

    for(i=0;i<500;i++)
        T[i]=(float *) malloc(500*sizeof(float));

    float dTdt;

    /* initialise temperature values */
    printf("Initialising 2D array...");

    for (i=0; i<500; i++){
        for (j=0; j<500; j++){
            if (150<=i && i<350 && 150<=j && j<350){
                T[i][j] = 50;
            } else {
                T[i][j] = 20;
            }
            printf("%f ",T[i][j]);
        }
        printf("\n");
    }

    return 0;
}

