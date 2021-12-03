#include <stdio.h>
#include <stdlib.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define BUFFER_SIZE_POWER_CONSUMPTION 256
#define NUMBER_OF_BITS 12

int calculatePowerConsumption(char* filename);
FILE* openFile(char* filename);

int main() {
    printf("Power Consumption: %d\n", calculatePowerConsumption(FILENAME_PART_ONE));

    /*life support rating = oxygen generator rating * CO2 scrubber rating*/

    return EXIT_SUCCESS;
}

int calculatePowerConsumption(char* filename) {

    FILE* fp = openFile(filename);

    int arrayNumberOfZerosPerColumn[NUMBER_OF_BITS] = {0};
    int arrayNumberOfOnesPerColumn[NUMBER_OF_BITS] = {0};
    int number, gammaRate = 0, epsilonRate = 0;

    char buffer[BUFFER_SIZE_POWER_CONSUMPTION];

    while(fgets(buffer, BUFFER_SIZE_POWER_CONSUMPTION, fp)){
        number = (int) strtol(buffer, NULL, 2);

        for(int i = 0; i < NUMBER_OF_BITS; i++) {
            arrayNumberOfOnesPerColumn[i] += (number >> i) & 1;
            arrayNumberOfZerosPerColumn[i] += ((number >> i) & 1) == 0;
        }
    }

    for(int i = NUMBER_OF_BITS - 1; i >= 0; i--) {
        if(arrayNumberOfZerosPerColumn[i] < arrayNumberOfOnesPerColumn[i]) {
            gammaRate |= 1 << i;
        } else {
            epsilonRate |= 1 << i;
        }
    }

    printf("Gamma Rate: %d\n", gammaRate);
    printf("Epsilon Rate: %d\n", epsilonRate);

    return gammaRate * epsilonRate;
}

FILE* openFile(char* filename) {
    FILE* fp = fopen(filename, "r");

    if (!fp){
        printf("Can't open file\n");
        return NULL;
    } else {
        return fp;
    }
}