#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include <limits.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define FILENAME_EXAMPLE "inputExample.csv"
#define NUMBER_LINES_EXAMPLE 5
#define NUMBER_LINE_LENGTH_EXAMPLE 10
#define NUMBER_LINES_PART_ONE_AND_TWO 100
#define NUMBER_LINE_LENGTH_PART_ONE_AND_TWO 100
#define VISITED_SIZE 1000
#define BUFFER_SIZE 1024
#define USE_EXAMPLE 0
#define ENABLE_LOGGING 0
#define PART 2
#define NUMBER_INPUT_LINES (USE_EXAMPLE == 1 ? NUMBER_LINES_EXAMPLE : NUMBER_LINES_PART_ONE_AND_TWO)
#define NUMBER_LINE_LENGTH (USE_EXAMPLE == 1 ? NUMBER_LINE_LENGTH_EXAMPLE : NUMBER_LINE_LENGTH_PART_ONE_AND_TWO)

struct point {
    int x;
    int y;
    int value;
};

typedef struct point Point;

struct lowPoints {
    struct point** lowPoints;
    int foundBasins;
    struct point* lowestBasinSize;
};

int calculateLowPoints(char* filename);
long long calculateBasinSize(char* filename);
void calculateSize(int** input, int i, int j, Point** visited, int* size);
int checkAlreadyVisited(Point** visited, int i, int j, int* size);
void readInput(int** input, FILE* fp);
void print(int** input);
FILE* openFile(char* filename);

int main() {
    printf("Part %d:\n", PART);
    int result = 0;
    long long resultPart2 = 0;
    if(PART == 1){
        result = calculateLowPoints(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_ONE);
        printf("Result: %d\n", result);

    } else {
        resultPart2 = calculateBasinSize(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_TWO);
        printf("Result: %lld\n", resultPart2);
    }

    return EXIT_SUCCESS;
}

int calculateLowPoints(char* filename){
    FILE* fp = openFile(filename);

    int sum = 0;
    
    int** input = malloc(sizeof(int*) * NUMBER_INPUT_LINES);
    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        input[i] = malloc(sizeof(int*) * NUMBER_LINE_LENGTH);
    }

    readInput(input, fp);

    printf("Got input:\n");
    print(input);

    for (int i = 0; i < NUMBER_INPUT_LINES; i++){
        for(int j = 0; j < NUMBER_LINE_LENGTH; j++){
            int isLowest = 1;
            if(ENABLE_LOGGING){
                printf("Looking at %d, indexes: %d %d:\n", input[i][j], i, j);
            }

            if(i > 0){
                if(ENABLE_LOGGING){
                    printf("Looking at above\n");
                    printf("Comparing %d with %d\n", input[i - 1][j], input[i][j]);
                }
                if(input[i - 1][j] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(i < NUMBER_INPUT_LINES - 1){
                if(ENABLE_LOGGING){
                    printf("Looking at below\n");
                    printf("Comparing %d with %d\n", input[i + 1][j], input[i][j]);
                }
                if(input[i + 1][j] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(j < NUMBER_LINE_LENGTH - 1){
                if(ENABLE_LOGGING){
                    printf("Looking at right\n");
                    printf("Comparing %d with %d\n", input[i][j + 1], input[i][j]);
                }
                if(input[i][j + 1] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(j > 0){
                if(ENABLE_LOGGING){
                    printf("Looking at left\n");
                    printf("Comparing %d with %d\n", input[i][j - 1], input[i][j]);
                }
                if(input[i][j - 1] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(isLowest == 1) {
                sum += 1 + input[i][j];
            }
        }
    }

    free(fp);
    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        free(input[i]);
    }
    free(input);

    return sum;
}

long long calculateBasinSize(char* filename){
    FILE* fp = openFile(filename);

    long long sum = 1;
    
    int** input = malloc(sizeof(int*) * NUMBER_INPUT_LINES);
    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        input[i] = malloc(sizeof(int*) * NUMBER_LINE_LENGTH);
    }

    struct lowPoints* points = malloc(sizeof(struct lowPoints));
    points->foundBasins = 0;
    points->lowestBasinSize = malloc(sizeof(struct point));
    points->lowPoints = malloc(sizeof(struct point*) * 3);

    readInput(input, fp);

    printf("Got input:\n");
    print(input);

    for (int i = 0; i < NUMBER_INPUT_LINES; i++){
        for(int j = 0; j < NUMBER_LINE_LENGTH; j++){
            int isLowest = 1;
            if(ENABLE_LOGGING){
                printf("Looking at %d, indexes: %d %d:\n", input[i][j], i, j);
            }

            if(i > 0){
                if(ENABLE_LOGGING){
                    printf("Looking at above\n");
                    printf("Comparing %d with %d\n", input[i - 1][j], input[i][j]);
                }
                if(input[i - 1][j] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(i < NUMBER_INPUT_LINES - 1){
                if(ENABLE_LOGGING){
                    printf("Looking at below\n");
                    printf("Comparing %d with %d\n", input[i + 1][j], input[i][j]);
                }
                if(input[i + 1][j] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(j < NUMBER_LINE_LENGTH - 1){
                if(ENABLE_LOGGING){
                    printf("Looking at right\n");
                    printf("Comparing %d with %d\n", input[i][j + 1], input[i][j]);
                }
                if(input[i][j + 1] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(j > 0){
                if(ENABLE_LOGGING){
                    printf("Looking at left\n");
                    printf("Comparing %d with %d\n", input[i][j - 1], input[i][j]);
                }
                if(input[i][j - 1] <= input[i][j]){
                    isLowest = 0;
                }
            }

            if(isLowest == 1) {
                int size = 0;

                struct point** visited = malloc(sizeof(struct point*) * VISITED_SIZE);
                for(int pointCounter = 0; pointCounter < VISITED_SIZE; pointCounter++){
                    visited[pointCounter] = malloc(sizeof(struct point));
                }

                if(ENABLE_LOGGING){
                    printf("\n ----------------------- \ncalculating for: %d %d %d\n", i , j, input[i][j]);
                }
                
                calculateSize(input, i, j, visited, &size);

                if(ENABLE_LOGGING){
                    printf("Size: %d\n", size);
                    printf("\n ----------------------- \n");
                }

                if(points->foundBasins < 3){
                    struct point* temp = malloc(sizeof(struct point));
                    temp->x = i;
                    temp->y = j;
                    temp->value = size;
                    points->lowPoints[points->foundBasins] = temp;

                    int lowestIndex = 0, lowestSize = INT_MAX;
                    for(int counter = 0; counter < points->foundBasins; counter++){
                        if(points->lowPoints[counter]->value < lowestSize){
                            lowestSize = points->lowPoints[counter]->value;
                            lowestIndex = counter;
                        }
                    }

                    points->lowestBasinSize = points->lowPoints[lowestIndex];

                    points->foundBasins++;
                } else {
                    if(size > points->lowestBasinSize->value){
                        struct point* temp = malloc(sizeof(struct point));
                        temp->x = i;
                        temp->y = j;
                        temp->value = size;

                        int lowestIndex = 0, lowestSize = INT_MAX;
                        for(int counter = 0; counter < points->foundBasins; counter++){
                            if(points->lowPoints[counter]->value < lowestSize){
                                lowestSize = points->lowPoints[counter]->value;
                                lowestIndex = counter;
                            }
                        }

                        free(points->lowPoints[lowestIndex]);

                        points->lowPoints[lowestIndex] = temp;

                        lowestIndex = 0;
                        lowestSize = INT_MAX;
                        for(int counter = 0; counter < points->foundBasins; counter++){
                            if(points->lowPoints[counter]->value < lowestSize){
                                lowestSize = points->lowPoints[counter]->value;
                                lowestIndex = counter;
                            }
                        }

                        points->lowestBasinSize = points->lowPoints[lowestIndex];
                    }
                }

                for(int pointCounter = 0; pointCounter < VISITED_SIZE; pointCounter++){
                    free(visited[pointCounter]);
                }
                free(visited);
            }
        }
    }

    for(int i = 0; i < 3; i++){
        sum *= points->lowPoints[i]->value;
    }

    free(fp);
    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        free(input[i]);
    }
    free(input);

    return sum;
}

void calculateSize(int** input, int i, int j, Point** visited, int* size){
    if(ENABLE_LOGGING){
        printf("in for %d %d\n", i, j);
    }
    if( i < 0 || j < 0 || i > NUMBER_INPUT_LINES - 1 || j > NUMBER_LINE_LENGTH - 1 || input[i][j] == 9 || 
        checkAlreadyVisited(visited, i, j, size)
    ){
        if(ENABLE_LOGGING){
            printf("returned for %d %d\n", i, j);
        }
        return;
    }

    visited[*size]->x = i;
    visited[*size]->y = j;
    (*size)++;

    calculateSize(input, i, j + 1, visited, size);
    calculateSize(input, i, j - 1, visited, size);
    calculateSize(input, i + 1, j, visited, size);
    calculateSize(input, i - 1, j, visited, size);

    return;
}

int checkAlreadyVisited(Point** visited, int i, int j, int* size){
    int indicator = 0;
    for(int pointCounter = 0; pointCounter < (*size); pointCounter++){
        if(visited[pointCounter]->x == i && visited[pointCounter]->y == j){
            if(ENABLE_LOGGING){
                printf("setting indicator\n");
            }
            indicator = 1;
        }
    }

    return indicator;
}

void readInput(int** input, FILE* fp){
    char buffer[BUFFER_SIZE];
    int counterInputLines = 0;

    while(fgets(buffer, BUFFER_SIZE, fp)){
        buffer[strcspn(buffer, "\n")] = 0;

        for(size_t i = 0; i < strlen(buffer); i++){
            input[counterInputLines][i] = buffer[i] - '0';
        }

        counterInputLines++;
    }
}

void print(int** input){
    for (int i = 0; i < NUMBER_INPUT_LINES; i++){
        for(int j = 0; j < NUMBER_LINE_LENGTH; j++){
            printf("%d", input[i][j]);
        }
        printf("\n");
    }
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