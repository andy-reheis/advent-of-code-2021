#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define FILENAME_EXAMPLE "inputExample.csv"
#define NUMBER_BUCKETS 2000
#define NUMBER_BUCKETS_EXAMPLE 16
#define BUFFER_SIZE 4096
#define USE_EXAMPLE 0
#define ENABLE_LOGGING 0
#define USE_NUMBER_BUCKETS (USE_EXAMPLE == 1 ? NUMBER_BUCKETS_EXAMPLE : NUMBER_BUCKETS)
#define PART 2

struct crabSubmarines {
    int* population;
    int numberSubmarines;
    int* positions;
};

void printPositions(struct crabSubmarines* crabs);
void readInput(struct crabSubmarines* crabs, FILE* fp);
int findBestPosition(struct crabSubmarines* crabs);
void calculatePosition(struct crabSubmarines* crabs, int goToPosition, int part);
void calculateBestPosition(char* filename, int part);
FILE* openFile(char* filename);

int main() {
    printf("Part %d:\n", PART);
    calculateBestPosition(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_ONE, PART);

    return EXIT_SUCCESS;
}

void calculateBestPosition(char* filename, int part){
    int bestPosition = 0;
    FILE* fp = openFile(filename);

    struct crabSubmarines* crabs = malloc(sizeof(struct crabSubmarines));
    crabs->population = calloc(USE_EXAMPLE == 1 ? NUMBER_BUCKETS_EXAMPLE : NUMBER_BUCKETS, sizeof(int));
    crabs->positions = calloc(USE_EXAMPLE == 1 ? NUMBER_BUCKETS_EXAMPLE : NUMBER_BUCKETS, sizeof(int));
    crabs->numberSubmarines = 0;

    readInput(crabs, fp);

    if(ENABLE_LOGGING == 1) {
        printf("Total number of submarines: %d\n", crabs->numberSubmarines);
        printf("Initial positions:\n");
        for(int i = 0; i <= USE_NUMBER_BUCKETS; i++){
            printf("Submarines on position %d: %d\n", i, crabs->population[i]);
        }
        printf("\n");
    }

    free(fp);

    for(int i = 0; i <= USE_NUMBER_BUCKETS; i++){
        calculatePosition(crabs, i, part);
    }

    if(ENABLE_LOGGING == 1){
        printPositions(crabs);
    }

    bestPosition = findBestPosition(crabs);

    printf("Best position %d with cost %d\n", bestPosition, crabs->positions[bestPosition]);

    free(crabs);
}

void readInput(struct crabSubmarines* crabs, FILE* fp){
    char* charInputNumbers;
    char buffer[BUFFER_SIZE];
    int newSubmarine = 0;

    while(fgets(buffer, BUFFER_SIZE, fp)){
        charInputNumbers = strtok(buffer, ",");
        while(charInputNumbers != NULL) {
            newSubmarine = (int) strtol(charInputNumbers, NULL, 10);
            crabs->population[newSubmarine]++; 
            crabs->numberSubmarines++;
            charInputNumbers = strtok(NULL, ",");
        }
    }
}

void printPositions(struct crabSubmarines* crabs){
    for(int i = 0; i <= USE_NUMBER_BUCKETS; i++){
        printf("Position %d, Consumed Fuel: %d\n", i, crabs->positions[i]);
    }
    printf("\n");
}

int findBestPosition(struct crabSubmarines* crabs){
    int minFuel = INT_MAX, minIndex;
    for(int i = 0; i <= USE_NUMBER_BUCKETS; i++){
        if(crabs->positions[i] < minFuel){
            minFuel = crabs->positions[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void calculatePosition(struct crabSubmarines* crabs, int goToPosition, int part){
    int consumedFuel = 0;
    int distance = 0;

    if(ENABLE_LOGGING == 1){
        printf("Calculating position %d ...\n", goToPosition);
    }

    for(int i = 0; i <= USE_NUMBER_BUCKETS; i++){
        distance = i < goToPosition ? goToPosition - i : i - goToPosition;
        if(ENABLE_LOGGING == 1){
            printf("Distance from %d to %d: %d\n", i, goToPosition, distance);
        }

        if(part == 1){
            consumedFuel += distance * crabs->population[i];
        } else {
            consumedFuel += ((distance * distance + distance) / 2) * crabs->population[i];
        }
    }

    crabs->positions[goToPosition] = consumedFuel;
}

FILE* openFile(char* filename) {
    FILE* fp = fopen(filename, "r");

    if (!fp){
        perror("Error opening file");
        return NULL;
    } else {
        return fp;
    }
}