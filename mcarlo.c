#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int insidePoints = 0;
int totalPoints = 0;
void *mcSimulator(void* param);
double randomNum();

//To start type `./mcarlo <integer value>`
int main(int argc, char *argv[])
{
    pthread_t thread1;
    pthread_t thread2;

    if (argc != 2) {
        fprintf(stderr,"ERROR: make sure to use ./mcarlo <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) < 1) {
        fprintf(stderr,"ERROR: number not positive\n",atoi(argv[1]));
        return -1;
    }

    //takes the two arguments and begins calculations
    totalPoints = atoi(argv[1]);
    int *argument1 = malloc(sizeof(int));
    int *argument2 = malloc(sizeof(int));

    // gets the high and low thread
    *argument1 = (int)floor(totalPoints/2);
    *argument2 = (int)ceil(totalPoints/2);
    pthread_create(&thread1,NULL,mcSimulator,argument1);
    pthread_create(&thread2,NULL,mcSimulator,argument2);

    // returns values
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    // Prints the output from the computation
    printf("Estimate is = %f\n",(4.0*insidePoints/totalPoints));

    // frees memory
    free(argument1);
    free(argument2);

    return 0;
}

void *mcSimulator(void* param)
{
    int value = *((int *) param);
    int theSum = 0;

    //starts the simulation
    for (int i = 0; i < value; i++) {
        float num1 = randomNum() * 2.0 - 1.0;
        float num2 = randomNum() * 2.0 - 1.0;

        // finds eucleidean distance
        if (sqrt(*num1 + num2*num2) < 1.0) {
            ++theSum;
        }
    }

    insidePoints += (float)theSum;
    pthread_exit(0);
}

//returns number between 0 and 1
double randomNum() {
    return random() / ((double)RAND_MAX + 1);
}
