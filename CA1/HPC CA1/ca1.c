#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>


int main(){


    const float alphSqrd     = 0.01;      // constant alpha squared, the area of the domain
    const float deltX        = 0.0002;    // delta X
    const float deltY        = 0.0002;    // delta Y
    const float timeStep     = 0.0000009; // time step
    const int   maxTimeSteps = 10000;     // number of iterations/time steps
    const bool  doIO         = false;     // determines whether or not the program outputs its results to a .dat file

    int h, i, j;

    /* 2D Array of Temperature Values */
    /* Make the array 2 bigger in each direction to represent boundary conditions */
    float T [502][502];

    float dTdt [502][502];  // change in temperature over a small time step


    /* initialise temperature values */
    #pragma omp parallel for default(none) shared(T) private (i, j) schedule(static)
    for (i=0; i<502; i++){
        for (j=0; j<502; j++){
            /* section of array where temp = 50C */
            if (151<=i && i<351 && 151<=j && j<351){
                T[i][j] = 50;
            } else {
                T[i][j] = 20;
            }
        }
    }


    /* Calculate dTdt then use that to update the values in the array */
    /* Start from i=1 and stop at i<501 to simulate boundary conditions */
    for (h=0; h<maxTimeSteps; h++){
        #pragma omp parallel for default(none) shared(T) private(i, j, dTdt) schedule(static)
        for (i=1; i<501; i++){
            for (j=1; j<501; j++){
                dTdt[i][j] = alphSqrd*(((T[i+1][j]-2*T[i][j]+T[i-1][j])/(deltX*deltX))+((T[i][j+1]-2*T[i][j]+T[i][j-1])/(deltY*deltY)));
            }
        }
        #pragma omp parallel for default(none) shared(T) private(i, j, dTdt) schedule(static)
        for (i=1; i<501; i++){
            for (j=1; j<501; j++){
                T[i][j] = T[i][j] + dTdt[i][j] * timeStep; // update the values
            }
        }
    }

    if (doIO){
        printf("Writing out results\n");
        FILE *outfile;
        outfile=fopen("ca1.dat","w");

        for (i=1; i<501; i++){
            for (j=1; j<501; j++){
                fprintf(outfile,"%f %f %f \n",i*deltX, j*deltY, T[i][j]);
            }
        }
        fclose(outfile);
    }
    return 0;
}

