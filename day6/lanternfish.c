#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define FILENAME_EXAMPLE "inputExample.csv"
#define SIZE_OF_POPULATION 300
#define SIZE_OF_POPULATION_EXAMPLE 5
#define BUFFER_SIZE 1024
#define MAX_DAYS_FISH 9
#define USE_EXAMPLE 0
#define ENABLE_LOGGING 0

struct lanternfishPopulation {
    long long* population;
};

void printPopulation(struct lanternfishPopulation* fishes, int day);
void readInput(struct lanternfishPopulation* fishes, FILE* fp);
void calculateDay(struct lanternfishPopulation* fishes);
long long estimateSizePopulation(char* filename, int days);
FILE* openFile(char* filename);

int main() {
    //printf("Part 1:\n");
    //printf("Size of population: %lld\n", estimateSizePopulation(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_ONE, 80));

    printf("Part 2:\n");
    printf("Size of population: %lld\n", estimateSizePopulation(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_TWO, 256));

    return EXIT_SUCCESS;
}

long long estimateSizePopulation(char* filename, int days){
    long long result = 0;
    FILE* fp = openFile(filename);

    struct lanternfishPopulation* fishes = malloc(sizeof(struct lanternfishPopulation));
    fishes->population = calloc(MAX_DAYS_FISH, sizeof(long long));

    readInput(fishes, fp);

    free(fp);

    for(int i = 0; i < days; i++){

        if(ENABLE_LOGGING == 1){
            printf("Day: %d\n", i);
            printPopulation(fishes, i);
        }
        calculateDay(fishes);
    }

    if(ENABLE_LOGGING == 1){
        printPopulation(fishes, days);
    }

    for(int i = 0; i < MAX_DAYS_FISH; i++){
        result += fishes->population[i];
    }

    return result;
}

void readInput(struct lanternfishPopulation* fishes, FILE* fp){
    char* charInputNumbers;
    char buffer[BUFFER_SIZE];
    long long newFish = 0;

    while(fgets(buffer, BUFFER_SIZE, fp)){
        charInputNumbers = strtok(buffer, ",");
        while(charInputNumbers != NULL) {
            newFish = (long long) strtol(charInputNumbers, NULL, 10);
            fishes->population[newFish]++; 
            charInputNumbers = strtok(NULL, ",");
        }
    }
}

void printPopulation(struct lanternfishPopulation* fishes, int day){
    printf("Population after day %d: \n", day);
    for(int i = 0; i < MAX_DAYS_FISH; i++){
        printf("Remaining day %d: %lld\n", i, fishes->population[i]);
    }
    printf("\n");
}

void calculateDay(struct lanternfishPopulation* fishes){
    long long* newPopulation = calloc(MAX_DAYS_FISH, sizeof(long long));
    for(int i = 0; i < MAX_DAYS_FISH - 1; i++) {
        newPopulation[i] = fishes->population[i + 1];
    }

    newPopulation[6] = fishes->population[7] + (long long) fishes->population[0];
    newPopulation[8] = fishes->population[0];

    free(fishes->population);

    fishes->population = newPopulation;
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