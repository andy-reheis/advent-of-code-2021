#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define NUMBER_OF_BINGO_FIELDS 100
#define NUMBER_OF_COLUMNS_BINGO_FIELD 5
#define NUMBER_OF_ROWS_BINGO_FIELD 5
#define BUFFER_SIZE 1024

struct bingoNumber {
    int number;
    int marked;
};

struct bingoField {
    struct bingoNumber bingoNumbers[NUMBER_OF_ROWS_BINGO_FIELD][NUMBER_OF_COLUMNS_BINGO_FIELD];
    int alreadyWon;
};

int findWinningBingoField(char* filename);
int findLastWinningBingoField(char* filename);
int checkForWinningBingoField(struct bingoField field);
int checkForLastWinningBingoField(struct bingoField* field, int* wonFields);
FILE* openFile(char* filename);

int main() {

    printf("Part 1:\n");
    printf("Result: %d\n", findWinningBingoField(FILENAME_PART_ONE));

    printf("Part 2:\n");
    printf("Result: %d\n", findLastWinningBingoField(FILENAME_PART_TWO));

    return EXIT_SUCCESS;
}

int findWinningBingoField(char* filename) {
    int result = 0, currentNumber, indexCurrentInputNumber = 0, indicatorReadingInputNumbers = 1, numberInputs, indexBingoField = 0, indexRow = 0, indexColumn = 0;
    FILE* fp = openFile(filename);
    char buffer[BUFFER_SIZE];
    char* charInputNumbers;
    int inputNumbers[100];

    struct bingoField* fields = malloc(sizeof(struct bingoField) * NUMBER_OF_BINGO_FIELDS);

    while(fgets(buffer, BUFFER_SIZE, fp)){
        if(buffer[0] == '\n'){
            if(indexRow > 0){
                indexBingoField++;
            }
            indexRow = 0;
            continue;
        }

        if(indicatorReadingInputNumbers == 1){
            charInputNumbers = strtok(buffer, ",");
            while(charInputNumbers != NULL) {
                inputNumbers[indexCurrentInputNumber++] = (int) strtol(charInputNumbers, NULL, 10);        
                charInputNumbers = strtok(NULL, ",");
            }

            numberInputs = indexCurrentInputNumber;
            indexCurrentInputNumber = 0;

            indicatorReadingInputNumbers = 0;
        } else {
            charInputNumbers = strtok(buffer, " ");
            while(charInputNumbers != NULL) {
                fields[indexBingoField].bingoNumbers[indexRow][indexColumn].number = (int) strtol(charInputNumbers, NULL, 10);
                fields[indexBingoField].bingoNumbers[indexRow][indexColumn].marked = 0;  
                charInputNumbers = strtok(NULL, " ");
                indexColumn++;
            }

            indexColumn = 0;
        }

        indexRow++;
    }

    for(indexCurrentInputNumber = 0; indexCurrentInputNumber < numberInputs; indexCurrentInputNumber++) {
        currentNumber = inputNumbers[indexCurrentInputNumber];

        for(indexBingoField = 0; indexBingoField <= NUMBER_OF_BINGO_FIELDS; indexBingoField++) {
            for(indexRow = 0; indexRow <= NUMBER_OF_ROWS_BINGO_FIELD; indexRow++) {
                for(indexColumn = 0; indexColumn < NUMBER_OF_COLUMNS_BINGO_FIELD; indexColumn++) {
                    if(fields[indexBingoField].bingoNumbers[indexRow][indexColumn].number == currentNumber) {
                        fields[indexBingoField].bingoNumbers[indexRow][indexColumn].marked = 1;
                    }
                }
            }
        }

        for(indexBingoField = 0; indexBingoField <= NUMBER_OF_BINGO_FIELDS; indexBingoField++) {
            if((result = currentNumber * checkForWinningBingoField(fields[indexBingoField])) > 0) {
                break;
            }
        }

        if(result > 0) {
            break;
        }
    }

    return result;
}

int checkForWinningBingoField(struct bingoField field) {
    int indicatorMarkedColumn = 1;
    int indicatorMarkedRow = 1;
    int indexWinningRow =  -1, indexWinningColumn = -1;
    int retval = 0;

    for(int row = 0; row < NUMBER_OF_ROWS_BINGO_FIELD; row++) {
        indicatorMarkedRow = 1;
        for(int column = 0; column < NUMBER_OF_COLUMNS_BINGO_FIELD; column++) {
            if(field.bingoNumbers[row][column].marked == 0 && indicatorMarkedRow == 1){
                indicatorMarkedRow = 0;
            }
        }

        if(indicatorMarkedRow == 1) {
            indexWinningRow = row;
        }

    }
    
    for(int column = 0; column < NUMBER_OF_COLUMNS_BINGO_FIELD; column++) {
        indicatorMarkedColumn = 1;
        for(int row = 0; row < NUMBER_OF_ROWS_BINGO_FIELD; row++) {
            if(field.bingoNumbers[row][column].marked == 0 && indicatorMarkedColumn == 1){
                indicatorMarkedColumn = 0;
            }
        }

        if(indicatorMarkedColumn == 1) {
            indexWinningColumn = column;
        }
    }

    if(indexWinningColumn != -1 || indexWinningRow != -1) {
        for(int row = 0; row < NUMBER_OF_ROWS_BINGO_FIELD; row++) {
            for(int column = 0; column < NUMBER_OF_COLUMNS_BINGO_FIELD; column++) {
                if(field.bingoNumbers[row][column].marked == 0) {
                    retval += field.bingoNumbers[row][column].number;
                }
            }
        }
    }
    
    return retval;
}

int findLastWinningBingoField(char* filename) {
    int result = 0, currentNumber, indexCurrentInputNumber = 0, indicatorReadingInputNumbers = 1, numberInputs, indexBingoField = 0, indexRow = 0, indexColumn = 0, numberOfWonFields = 0;
    FILE* fp = openFile(filename);
    char buffer[BUFFER_SIZE];
    char* charInputNumbers;
    int inputNumbers[100];

    struct bingoField* fields = malloc(sizeof(struct bingoField) * (NUMBER_OF_BINGO_FIELDS + 1));

    while(fgets(buffer, BUFFER_SIZE, fp)){
        if(buffer[0] == '\n'){
            if(indexRow > 0){
                indexBingoField++;
            }
            indexRow = 0;
            continue;
        }

        if(indicatorReadingInputNumbers == 1){
            charInputNumbers = strtok(buffer, ",");
            while(charInputNumbers != NULL) {
                inputNumbers[indexCurrentInputNumber++] = (int) strtol(charInputNumbers, NULL, 10);        
                charInputNumbers = strtok(NULL, ",");
            }

            numberInputs = indexCurrentInputNumber;
            indexCurrentInputNumber = 0;

            indicatorReadingInputNumbers = 0;
        } else {
            charInputNumbers = strtok(buffer, " ");
            while(charInputNumbers != NULL) {
                fields[indexBingoField].bingoNumbers[indexRow][indexColumn].number = (int) strtol(charInputNumbers, NULL, 10);
                fields[indexBingoField].bingoNumbers[indexRow][indexColumn].marked = 0;  
                charInputNumbers = strtok(NULL, " ");
                indexColumn++;
            }

            indexColumn = 0;
        }

        indexRow++;
    }

    for(indexCurrentInputNumber = 0; indexCurrentInputNumber < numberInputs; indexCurrentInputNumber++) {
        currentNumber = inputNumbers[indexCurrentInputNumber];

        for(indexBingoField = 0; indexBingoField <= NUMBER_OF_BINGO_FIELDS; indexBingoField++) {
            for(indexRow = 0; indexRow <= NUMBER_OF_ROWS_BINGO_FIELD; indexRow++) {
                for(indexColumn = 0; indexColumn < NUMBER_OF_COLUMNS_BINGO_FIELD; indexColumn++) {
                    if(fields[indexBingoField].bingoNumbers[indexRow][indexColumn].number == currentNumber) {
                        fields[indexBingoField].bingoNumbers[indexRow][indexColumn].marked = 1;
                    }
                }
            }
        }

        for(indexBingoField = 0; indexBingoField < NUMBER_OF_BINGO_FIELDS; indexBingoField++) {
            if((result = currentNumber * checkForLastWinningBingoField(&fields[indexBingoField], &numberOfWonFields)) > 0) {
                break;
            }
        }

        if(numberOfWonFields == NUMBER_OF_BINGO_FIELDS) {
            break;
        }
    }

    return result;
}

int checkForLastWinningBingoField(struct bingoField* field, int* wonFields) {
    int indicatorMarkedColumn = 1;
    int indicatorMarkedRow = 1;
    int retval = 0;

    if(field->alreadyWon > 0){
        return retval;
    }

    for(int row = 0; row < NUMBER_OF_ROWS_BINGO_FIELD; row++) {
        indicatorMarkedRow = 1;
        for(int column = 0; column < NUMBER_OF_COLUMNS_BINGO_FIELD; column++) {
            if(field->bingoNumbers[row][column].marked == 0 && indicatorMarkedRow == 1){
                indicatorMarkedRow = 0;
            }
        }

        if(indicatorMarkedRow == 1) {
            field->alreadyWon = 1;
        }

    }
    
    for(int column = 0; column < NUMBER_OF_COLUMNS_BINGO_FIELD; column++) {
        indicatorMarkedColumn = 1;
        for(int row = 0; row < NUMBER_OF_ROWS_BINGO_FIELD; row++) {
            if(field->bingoNumbers[row][column].marked == 0 && indicatorMarkedColumn == 1){
                indicatorMarkedColumn = 0;
            }
        }

        if(indicatorMarkedColumn == 1) {
            field->alreadyWon = 1;
        }
    }


    if(field->alreadyWon == 1){
        *(wonFields) += 1;
    }

    if(*wonFields == NUMBER_OF_BINGO_FIELDS) {
        for(int row = 0; row < NUMBER_OF_ROWS_BINGO_FIELD; row++) {
            for(int column = 0; column < NUMBER_OF_COLUMNS_BINGO_FIELD; column++) {
                if(field->bingoNumbers[row][column].marked == 0) {
                    retval += field->bingoNumbers[row][column].number;
                }
            }
        }
    }
    
    return retval;
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