#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define FILENAME_EXAMPLE "inputExample.csv"
#define HEIGHT 1000
#define WIDTH 1000
#define HEIGHT_EXAMPLE 10
#define WIDTH_EXAMPLE 10
#define BUFFER_SIZE 1024
#define USE_EXAMPLE 0
#define ENABLE_LOGGING 0

struct coordinate {
    int x;
    int y;
};

struct ventLine {
    struct coordinate start;
    struct coordinate end;
};

struct oceanPoint {
    int counter;
};

struct oceanFloor {
    struct oceanPoint floor[USE_EXAMPLE == 1 ? HEIGHT_EXAMPLE : HEIGHT][USE_EXAMPLE == 1 ? WIDTH_EXAMPLE : WIDTH];
};

int calculatePointsTwoPlus(char* filename, int indicatorOnlyUseVerticalAndHorizontal);
void fillInVents(struct oceanFloor* floor, FILE* fp, int indicatorOnlyUseVerticalAndHorizontal);
int countPointsBiggerThanNumber(struct oceanFloor* floor, int number);
void resetFloor(struct oceanFloor* floor);
void printFloor(struct oceanFloor* floor);
FILE* openFile(char* filename);

int main() {
    printf("Part 1:\n");
    printf("Number of Point where counter >= 2 without diagonal: %d\n", calculatePointsTwoPlus(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_ONE, 1));

    printf("Part 2:\n");
    printf("Number of Point where counter >= 2 with diagonal: %d\n", calculatePointsTwoPlus(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_TWO, 0));

    return EXIT_SUCCESS;
}

int calculatePointsTwoPlus(char* filename, int indicatorOnlyUseVerticalAndHorizontal){
    int result;
    FILE* fp = openFile(filename);

    struct oceanFloor* floor = malloc(sizeof(struct oceanFloor));

    resetFloor(floor);

    fillInVents(floor, fp, indicatorOnlyUseVerticalAndHorizontal);

    fclose(fp);

    if(ENABLE_LOGGING == 1){
        printFloor(floor);
    }

    result = countPointsBiggerThanNumber(floor, 1);
    free(floor);

    return result;
}

void resetFloor(struct oceanFloor* floor){
    for(int y = 0; y < (USE_EXAMPLE == 1 ? HEIGHT_EXAMPLE : HEIGHT); y++){
        for(int x = 0; x < (USE_EXAMPLE == 1 ? WIDTH_EXAMPLE : WIDTH); x++){
            floor->floor[y][x].counter = 0;
        }
    }
}

void printFloor(struct oceanFloor* floor){
    printf("-----------------\n");
    for(int y = 0; y < (USE_EXAMPLE == 1 ? HEIGHT_EXAMPLE : HEIGHT); y++){
        for(int x = 0; x < (USE_EXAMPLE == 1 ? WIDTH_EXAMPLE : WIDTH); x++){
            printf("%d ", floor->floor[y][x].counter);
        }
        printf("\n");
    }
    printf("-----------------\n");
}

void fillInVents(struct oceanFloor* floor, FILE* fp, int indicatorOnlyUseVerticalAndHorizontal){
    char buffer[BUFFER_SIZE];
    const char* delimiter1 = " -> ";
    const char* delimiter2 = ",";
    char* tempLine;
    char* coordinates;
    char* tempLinePtr = NULL;
    char* coordinatesPtr = NULL;
    int indicatorCoordinate = 0, start, end;

    struct ventLine* line = malloc(sizeof(struct ventLine));
    struct coordinate* point = malloc(sizeof(struct coordinate));

    while(fgets(buffer, BUFFER_SIZE, fp)){
        tempLine = strtok_r(buffer, delimiter1 , &tempLinePtr);

        while(tempLine != NULL) {
            coordinates = strtok_r(tempLine, delimiter2 , &coordinatesPtr);

            while(coordinates != NULL){
                if(indicatorCoordinate == 0) {
                    line->start.x = (int) strtol(coordinates, NULL, 10);
                } else if(indicatorCoordinate == 1) {
                    line->start.y = (int) strtol(coordinates, NULL, 10);
                } else if(indicatorCoordinate == 2) {
                    line->end.x = (int) strtol(coordinates, NULL, 10);
                } else {
                    line->end.y = (int) strtol(coordinates, NULL, 10);
                }

                coordinates = strtok_r(NULL, delimiter2 , &coordinatesPtr);
                indicatorCoordinate++;
            }

            tempLine = strtok_r(NULL, delimiter1 , &tempLinePtr);
        }
        
        if(ENABLE_LOGGING == 1){
            printf("line: %d,%d -> %d,%d\n", line->start.x, line->start.y, line->end.x, line->end.y);
        }

        if(line->start.x == line->end.x){
            start = line->start.y < line->end.y ? line->start.y : line->end.y;
            end = line->start.y > line->end.y ? line->start.y : line->end.y;
            for(int i = start; i <= end; i++){
                floor->floor[i][line->start.x].counter++;
            }
        } else if(line->start.y == line->end.y) {
            start = line->start.x < line->end.x ? line->start.x : line->end.x;
            end = line->start.x > line->end.x ? line->start.x : line->end.x;
            for(int i = start; i <= end; i++){
                floor->floor[line->start.y][i].counter++;
            }
        }

        if(indicatorOnlyUseVerticalAndHorizontal == 0 && line->start.x != line->end.x && line->start.y != line->end.y){
            point->x = line->start.x;
            point->y = line->start.y;

            while(point->x != line->end.x){
                floor->floor[point->y][point->x].counter++;

                if(ENABLE_LOGGING == 1){
                    printf("point %d %d\n", point->x, point->y);
                }

                if(line->start.x > line->end.x){
                    point->x--;
                } else {
                    point->x++;
                }
                
                if(line->start.y > line->end.y){
                    point->y--;
                } else {
                    point->y++;
                }
            }

            floor->floor[point->y][point->x].counter++;
        }

        indicatorCoordinate = 0;
    }

    free(line);
    free(point);
}

int countPointsBiggerThanNumber(struct oceanFloor* floor, int number){
    int result = 0;
    for(int y = 0; y < (USE_EXAMPLE == 1 ? HEIGHT_EXAMPLE : HEIGHT); y++){
        for(int x = 0; x < (USE_EXAMPLE == 1 ? WIDTH_EXAMPLE : WIDTH); x++){
            if(floor->floor[y][x].counter > number){
                result++;
            }
        }
    }

    return result;
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