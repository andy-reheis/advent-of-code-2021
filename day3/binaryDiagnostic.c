#include <stdio.h>
#include <stdlib.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define BUFFER_SIZE_POWER_CONSUMPTION 256
#define NUMBER_OF_BITS 12
#define NUMBER_OF_LINES 1024

struct dataPoint {
    int number, indicator;    
};

struct data {
    struct dataPoint* fileContent;
    int counter, fileLength;
};

int calculatePowerConsumption(char* filename);
int calculateLifeSupportRating(char* filename);
int calculateOxygenOrScrubberRating (struct data* data, int indicatorOxygen);
FILE* openFile(char* filename);

int main() {
    printf("Part 1:\n");
    printf("Power Consumption: %d\n", calculatePowerConsumption(FILENAME_PART_ONE));

    printf("Part 2:\n");
    printf("Life Support Rating: %d\n", calculateLifeSupportRating(FILENAME_PART_TWO));

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

int calculateLifeSupportRating(char* filename) {

    FILE* fp = openFile(filename);

    int number, oxygenGeneratorRating = 0, co2ScrubberRating = 0;

    struct data* oxygenData = malloc(sizeof(struct data));
    struct data* co2Data = malloc(sizeof(struct data));

    oxygenData->fileContent = malloc(NUMBER_OF_LINES * sizeof(struct dataPoint));
    oxygenData->counter = 0;
    oxygenData->fileLength = 0;

    co2Data->fileContent = malloc(NUMBER_OF_LINES * sizeof(struct dataPoint));
    co2Data->counter = 0;
    co2Data->fileLength = 0;

    char buffer[BUFFER_SIZE_POWER_CONSUMPTION];

    while(fgets(buffer, BUFFER_SIZE_POWER_CONSUMPTION, fp)){
        number = (int) strtol(buffer, NULL, 2);

        oxygenData->fileContent[oxygenData->fileLength].number = number;
        oxygenData->fileContent[oxygenData->fileLength++].indicator = 1;
        co2Data->fileContent[co2Data->fileLength].number = number;
        co2Data->fileContent[co2Data->fileLength++].indicator = 1;
    }

    oxygenData->counter = oxygenData->fileLength;
    co2Data->counter = co2Data->fileLength;

    oxygenGeneratorRating = calculateOxygenOrScrubberRating(oxygenData, 1);
    co2ScrubberRating = calculateOxygenOrScrubberRating(co2Data, 0);

    printf("Pxygen Generator Rating: %d\n", oxygenGeneratorRating);
    printf("CO2 Scrubber Rating: %d\n", co2ScrubberRating);

    return oxygenGeneratorRating * co2ScrubberRating;
}

int calculateOxygenOrScrubberRating (struct data* data, int indicatorOxygen) {
    int rating, bit = 0, indicatorOxygenBitwise, indicatorCo2Bitwise;
    int arrayNumberOfZerosPerColumn[NUMBER_OF_BITS] = {0};
    int arrayNumberOfOnesPerColumn[NUMBER_OF_BITS] = {0};

    while (data->counter > 1) {
        for(int i = 0; i < data->fileLength; i++){
            if(data->fileContent[i].indicator == 1){
                arrayNumberOfOnesPerColumn[bit] += (data->fileContent[i].number >> (NUMBER_OF_BITS - bit - 1)) & 1;
                arrayNumberOfZerosPerColumn[bit] += ((data->fileContent[i].number >> (NUMBER_OF_BITS - bit - 1)) & 1) == 0;
            }
        }

        if(indicatorOxygen == 1){
            indicatorOxygenBitwise = arrayNumberOfOnesPerColumn[bit] >= arrayNumberOfZerosPerColumn[bit] ? 1 : 0;

            for (int indexDataPoint = 0; indexDataPoint < data->fileLength; indexDataPoint++){
                if(((data->fileContent[indexDataPoint].number >> (NUMBER_OF_BITS - bit - 1)) & 1) != indicatorOxygenBitwise && data->fileContent[indexDataPoint].indicator > 0 && data->counter > 1) {
                    data->fileContent[indexDataPoint].indicator = -1;
                    data->counter -= 1;
                    
                }
            }

        } else {
            indicatorCo2Bitwise = arrayNumberOfOnesPerColumn[bit] >= arrayNumberOfZerosPerColumn[bit] ? 0 : 1;

            for (int indexDataPoint = 0; indexDataPoint < data->fileLength; indexDataPoint++){
                if(((data->fileContent[indexDataPoint].number >> (NUMBER_OF_BITS - bit - 1)) & 1) != indicatorCo2Bitwise && data->fileContent[indexDataPoint].indicator > 0 && data->counter > 1) {
                    data->fileContent[indexDataPoint].indicator = -1;
                    data->counter -= 1;
                }
            }
        }

        bit++;
    }

    // finding the ratings
    for(int i = 0; i < data->fileLength; i++) {
        if(data->fileContent[i].indicator == 1){
            rating = data->fileContent[i].number;
        }
    }

    return rating;
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