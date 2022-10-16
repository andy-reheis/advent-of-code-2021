#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include <limits.h>

#define FILENAME_PART_ONE "inputPartOne.csv"
#define FILENAME_PART_TWO "inputPartTwo.csv"
#define FILENAME_EXAMPLE "inputExample.csv"
#define NUMBER_LINES_EXAMPLE 10
#define NUMBER_LINES_PART_ONE_AND_TWO 200
#define NUMBER_SEGMENTS_ONE 2
#define NUMBER_SEGMENTS_SEVEN 3
#define NUMBER_SEGMENTS_FOUR 4
#define NUMBER_SEGMENTS_EIGHT 7
#define NUMBER_INPUT 10
#define NUMBER_OUTPUT 4
#define BUFFER_SIZE 1024
#define USE_EXAMPLE 0
#define ENABLE_LOGGING 0
#define PART 2
#define NUMBER_INPUT_LINES (USE_EXAMPLE == 1 ? NUMBER_LINES_EXAMPLE : NUMBER_LINES_PART_ONE_AND_TWO)

#define TOP 1
#define TOP_RIGHT 2
#define TOP_LEFT 4
#define MIDDLE 8
#define BOT 16
#define BOT_LEFT 32
#define BOT_RIGHT 64

#define PANELS_ZERO (TOP + TOP_LEFT + TOP_RIGHT + BOT + BOT_LEFT + BOT_RIGHT)
#define PANELS_ONE (TOP_RIGHT + BOT_RIGHT)
#define PANELS_TWO (TOP + TOP_RIGHT + MIDDLE + BOT_LEFT + BOT)
#define PANELS_THREE (TOP + TOP_RIGHT + MIDDLE + BOT_RIGHT + BOT)
#define PANELS_FOUR (TOP_LEFT + MIDDLE + TOP_RIGHT + BOT_RIGHT)
#define PANELS_FIVE (TOP + TOP_LEFT + MIDDLE + BOT_RIGHT + BOT)
#define PANELS_SIX (TOP + TOP_LEFT + MIDDLE + BOT + BOT_LEFT + BOT_RIGHT)
#define PANELS_SEVEN (TOP + TOP_RIGHT + BOT_RIGHT)
#define PANELS_EIGHT (TOP + TOP_LEFT + TOP_RIGHT + MIDDLE + BOT + BOT_LEFT + BOT_RIGHT)
#define PANELS_NINE (TOP + TOP_LEFT + TOP_RIGHT + MIDDLE + BOT_RIGHT + BOT)

struct inputLine {
    char** output;
    char** input;
};

void readInput(struct inputLine** input, FILE* fp);
void calculateNumberUniqueSegmentsOutput(char* filename);
void calculateOutputSum(char* filename);
int exp10(int e);
void print(struct inputLine** input);
FILE* openFile(char* filename);

int main() {
    printf("Part %d:\n", PART);
    if(PART == 1){
        calculateNumberUniqueSegmentsOutput(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_ONE);
    } else {
        calculateOutputSum(USE_EXAMPLE == 1 ? FILENAME_EXAMPLE : FILENAME_PART_TWO);
    }

    return EXIT_SUCCESS;
}

void calculateNumberUniqueSegmentsOutput(char* filename){
    FILE* fp = openFile(filename);
    struct inputLine** input = malloc(sizeof(struct inputLine*) * NUMBER_INPUT_LINES);
    int counterUniqueNumbers = 0;

    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        input[i] = malloc(sizeof(struct inputLine));
        input[i]->input = malloc(sizeof(char*) * NUMBER_INPUT);
        input[i]->output = malloc(sizeof(char*) * NUMBER_OUTPUT);
    }

    if(ENABLE_LOGGING){
        printf("YEA. Everything is malloc'd\n");
    }

    readInput(input, fp);

    if(ENABLE_LOGGING){
        printf("after reading\n");
    }

    print(input);

    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        for(int idxOutput = 0; idxOutput < NUMBER_OUTPUT; idxOutput++){
            if( strlen(input[i]->output[idxOutput]) == 2 || 
                strlen(input[i]->output[idxOutput]) == 4 ||
                strlen(input[i]->output[idxOutput]) == 3 ||
                strlen(input[i]->output[idxOutput]) == 7
            ){
                counterUniqueNumbers++;
            }
        }
    }

    printf("Unique Segment Numbers: %d\n", counterUniqueNumbers);

    free(fp);
    free(input);
}

/* ATTENTION !!! */
/* REALLY MESSY CODE HERE !!! */
void calculateOutputSum(char* filename){
    FILE* fp = openFile(filename);
    struct inputLine** input = malloc(sizeof(struct inputLine*) * NUMBER_INPUT_LINES);

    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        input[i] = malloc(sizeof(struct inputLine));
        input[i]->input = malloc(sizeof(char*) * NUMBER_INPUT);
        input[i]->output = malloc(sizeof(char*) * NUMBER_OUTPUT);
    }

    if(ENABLE_LOGGING){
        printf("YEA. Everything is malloc'd\n");
    }

    readInput(input, fp);

    if(ENABLE_LOGGING){
        printf("after reading\n");
    }

    print(input);

    long long sum = 0;

    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        if(ENABLE_LOGGING){
            printf("Line %d\n", i);
        }

        char *letters_one, *letters_four, *letters_seven, *letters_eight;

        char *fixed_letters_zero, *fixed_letters_one, *fixed_letters_two, *fixed_letters_three, *fixed_letters_four, *fixed_letters_five,
        *fixed_letters_six, *fixed_letters_seven, *fixed_letters_eight, *fixed_letters_nine;

        char *fixed_letter_top, *fixed_letter_top_right, *fixed_letter_top_left, *fixed_letter_middle, *fixed_letter_bot, 
        *fixed_letter_bot_right, *fixed_letter_bot_left;

        char six_chars[3][8];
        int counter_six_chars = 0;

        char five_chars[3][8];
        int counter_five_chars = 0;


        for(int idxInput = 0; idxInput < NUMBER_INPUT; idxInput++){
            if(strlen(input[i]->input[idxInput]) == 2){
                letters_one = input[i]->input[idxInput];
                fixed_letters_one = input[i]->input[idxInput];
            } else if(strlen(input[i]->input[idxInput]) == 4){
                letters_four = input[i]->input[idxInput];
                fixed_letters_four = input[i]->input[idxInput];
            } else if(strlen(input[i]->input[idxInput]) == 3){
                letters_seven = input[i]->input[idxInput];
                fixed_letters_seven = input[i]->input[idxInput];
            } else if (strlen(input[i]->input[idxInput]) == 7){
                letters_eight = input[i]->input[idxInput];
                fixed_letters_eight = input[i]->input[idxInput];
            }
        }
  
        if(ENABLE_LOGGING){
            printf("1: %s, 4: %s, 7: %s, 8: %s\n", letters_one, letters_four, letters_seven, letters_eight);
        }

        for(int index = 0; index < strlen(letters_seven); index++){
            if(strchr(letters_one, letters_seven[index]) == NULL){
                fixed_letter_top = letters_seven[index];
            }
        }

        if(ENABLE_LOGGING){
            printf("letter top: %c\n", fixed_letter_top);
        }
        
        for(int idxInput = 0; idxInput < NUMBER_INPUT; idxInput++){          
            if(strlen(input[i]->input[idxInput]) == 6){
                strncpy(six_chars[counter_six_chars++], input[i]->input[idxInput], 8);
            }
        }

        if(ENABLE_LOGGING){
            printf("Six chars: ");
            for(int print_counter = 0; print_counter < 3; print_counter++){
                printf("%s ", six_chars[print_counter]);
            }
            printf("\n");
        }

        for(int index = 0; index < 3; index++){
            for(int indexOne = 0; indexOne < strlen(letters_one); indexOne++){
                if(strchr(six_chars[index], letters_one[indexOne]) == NULL){
                    fixed_letter_top_right = letters_one[indexOne];
                }
            }
        }

        if(ENABLE_LOGGING){
            printf("letter top-right: %c\n", fixed_letter_top_right);
        }

        for(int indexOne = 0; indexOne < strlen(letters_one); indexOne++){
            if(strchr(&fixed_letter_top_right, letters_one[indexOne]) == NULL){
                fixed_letter_bot_right = letters_one[indexOne];
            }
        }

        if(ENABLE_LOGGING){
            printf("letter bot_right: %c\n", fixed_letter_bot_right);
        }

        for(int idxInput = 0; idxInput < NUMBER_INPUT; idxInput++){          
            if(strlen(input[i]->input[idxInput]) == 5){
                strncpy(five_chars[counter_five_chars++], input[i]->input[idxInput], 8);
            }
        }

        if(ENABLE_LOGGING){
            printf("Five chars: ");
            for(int print_counter = 0; print_counter < 3; print_counter++){
                printf("%s ", five_chars[print_counter]);
            }
            printf("\n");
        }

        for(int index = 0; index < 3; index++){
            int counter_unknown = 0;
            for(int subindex = 0; subindex < strlen(five_chars[index]); subindex++){
                if( five_chars[index][subindex] == fixed_letter_top_right ||
                    five_chars[index][subindex] == fixed_letter_top ||
                    five_chars[index][subindex] == fixed_letter_bot_right){
                        continue;
                }
                counter_unknown++;

            }

            if(counter_unknown == 2){
                for(int subindex = 0; subindex < strlen(five_chars[index]); subindex++){
                    if( five_chars[index][subindex] == fixed_letter_top_right ||
                        five_chars[index][subindex] == fixed_letter_top ||
                        five_chars[index][subindex] == fixed_letter_bot_right){
                            continue;
                    }

                    if(strchr(letters_four, five_chars[index][subindex]) != NULL){
                        fixed_letter_middle = five_chars[index][subindex];
                    }
                }
            }
        }

        if(ENABLE_LOGGING){
            printf("letter middle: %c\n", fixed_letter_middle);
        }

        for(int index = 0; index < strlen(letters_four); index++){
            if( letters_four[index] == fixed_letter_middle ||
                letters_four[index] == fixed_letter_top ||
                letters_four[index] == fixed_letter_top_right ||
                letters_four[index] == fixed_letter_bot_right){
                    continue;
                }
            fixed_letter_top_left = letters_four[index];
        }

        if(ENABLE_LOGGING){
            printf("letter top-left: %c\n", fixed_letter_top_left);
        }

        for(int index = 0; index < 3; index++){
            int counter_unknown = 0;
            for(int subindex = 0; subindex < strlen(six_chars[index]); subindex++){
                if( six_chars[index][subindex] == fixed_letter_top_right ||
                    six_chars[index][subindex] == fixed_letter_top_left ||
                    six_chars[index][subindex] == fixed_letter_top ||
                    six_chars[index][subindex] == fixed_letter_bot_right ||
                    six_chars[index][subindex] == fixed_letter_middle){
                        continue;
                }
                counter_unknown++;

            }

            if(counter_unknown == 1){
                for(int subindex = 0; subindex < strlen(six_chars[index]); subindex++){
                    if( six_chars[index][subindex] == fixed_letter_top_right ||
                        six_chars[index][subindex] == fixed_letter_top_left ||
                        six_chars[index][subindex] == fixed_letter_top ||
                        six_chars[index][subindex] == fixed_letter_bot_right ||
                        six_chars[index][subindex] == fixed_letter_middle){
                            continue;
                    }
                    fixed_letter_bot = six_chars[index][subindex];
                }
            }
        }

        if(ENABLE_LOGGING){
            printf("letter bot: %c\n", fixed_letter_bot);
        }

        for(int index = 0; index < 3; index++){
            int counter_unknown = 0;
            for(int subindex = 0; subindex < strlen(six_chars[index]); subindex++){
                if( six_chars[index][subindex] == fixed_letter_bot ||
                    six_chars[index][subindex] == fixed_letter_top_left ||
                    six_chars[index][subindex] == fixed_letter_top ||
                    six_chars[index][subindex] == fixed_letter_bot_right ||
                    six_chars[index][subindex] == fixed_letter_middle){
                        continue;
                }
                counter_unknown++;
            }

            if(counter_unknown == 2){
                for(int subindex = 0; subindex < strlen(six_chars[index]); subindex++){
                    if( six_chars[index][subindex] == fixed_letter_bot ||
                        six_chars[index][subindex] == fixed_letter_top_left ||
                        six_chars[index][subindex] == fixed_letter_top_right ||
                        six_chars[index][subindex] == fixed_letter_top ||
                        six_chars[index][subindex] == fixed_letter_bot_right ||
                        six_chars[index][subindex] == fixed_letter_middle){
                            continue;
                    }

                    fixed_letter_bot_left = six_chars[index][subindex];
                }
            }
        }
        if(ENABLE_LOGGING){
            printf("letter bot-left: %c\n", fixed_letter_bot_left);
        }

        if(ENABLE_LOGGING){
            printf("\n");
            printf("Getting all correlations between numbers and text...\n");
            printf("top: %c\n", fixed_letter_top);
            printf("top-right: %c\n", fixed_letter_top_right);
            printf("top-left: %c\n", fixed_letter_top_left);
            printf("middle: %c\n", fixed_letter_middle);
            printf("bot: %c\n", fixed_letter_bot);
            printf("bot-left: %c\n", fixed_letter_bot_left);
            printf("bot-right: %c\n", fixed_letter_bot_right);
        }

        for(int idxInput = 0; idxInput < NUMBER_INPUT; idxInput++){
            if(strlen(input[i]->input[idxInput]) == 6){
                if(
                    strchr(input[i]->input[idxInput], fixed_letter_top) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_left) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_right) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_left) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_right) != NULL
                ){
                    fixed_letters_zero = input[i]->input[idxInput];
                }

                else if(
                    strchr(input[i]->input[idxInput], fixed_letter_top) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_left) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_left) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_middle) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_right) != NULL
                ){
                    fixed_letters_six = input[i]->input[idxInput];
                }

                else if(
                    strchr(input[i]->input[idxInput], fixed_letter_top) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_left) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_right) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_middle) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_right) != NULL
                ){

                    fixed_letters_nine = input[i]->input[idxInput];
                }
            }

            else if(strlen(input[i]->input[idxInput]) == 5){
                if(
                    strchr(input[i]->input[idxInput], fixed_letter_top) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_left) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_middle) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_right) != NULL
                ){
                    fixed_letters_five = input[i]->input[idxInput];
                }
                else if(
                    strchr(input[i]->input[idxInput], fixed_letter_top) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_right) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_middle) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_left) != NULL
                ){
                    fixed_letters_two = input[i]->input[idxInput];
                }
                else if(
                    strchr(input[i]->input[idxInput], fixed_letter_top) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_top_right) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_middle) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot) != NULL &&
                    strchr(input[i]->input[idxInput], fixed_letter_bot_right) != NULL
                ){
                    fixed_letters_three = input[i]->input[idxInput];
                }
            }
        }

        if(ENABLE_LOGGING){
            printf("Finished calculation...\n");
        }

        printf("Letters for 0: %s\n", fixed_letters_zero);
        printf("Letters for 1: %s\n", fixed_letters_one);
        printf("Letters for 2: %s\n", fixed_letters_two);
        printf("Letters for 3: %s\n", fixed_letters_three);
        printf("Letters for 4: %s\n", fixed_letters_four);
        printf("Letters for 5: %s\n", fixed_letters_five);
        printf("Letters for 6: %s\n", fixed_letters_six);
        printf("Letters for 7: %s\n", fixed_letters_seven);
        printf("Letters for 8: %s\n", fixed_letters_eight);
        printf("Letters for 9: %s\n", fixed_letters_nine);

        int number = 0;
        for(int idxOutput = 0; idxOutput < NUMBER_OUTPUT; idxOutput++){
            if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 0 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 1 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) == NULL
            ){
                number += 2 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 3 * exp10(3 - idxOutput);
            }  else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 4 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 5 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 6 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 7 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 8 * exp10(3 - idxOutput);
            } else if(
                strchr(input[i]->output[idxOutput], fixed_letter_top) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_right) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_top_left) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_middle) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot) != NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_left) == NULL &&
                strchr(input[i]->output[idxOutput], fixed_letter_bot_right) != NULL
            ){
                number += 9 * exp10(3 - idxOutput);
            } else {
                return EXIT_SUCCESS;
            }
        }
        
        printf("number: %d\n", number);
        printf("----------------------------------------------\n\n");

        sum += number;
    }

    printf("Sum: %lld\n", sum);

    free(fp);
    free(input);
}

int exp10(int e){
  int x = 1;
  for (int i = 0; i < e; i++) {
    x = x * 10;
  }
  return x;
}


void readInput(struct inputLine** input, FILE* fp){
    char buffer[BUFFER_SIZE];
    const char* delimiter1 = "|";
    const char* delimiter2 = " ";
    char* tempLine;
    char* values;
    char* tempLinePtr = NULL;
    char* valuesPtr = NULL;
    int indicatorInOutput = 0, counterLine = 0, counterInOutput = 0;
    char* tempPtr;

    while(fgets(buffer, BUFFER_SIZE, fp)){
        buffer[strcspn(buffer, "\n")] = 0;
        if(ENABLE_LOGGING){
            printf("buffer: %s\n", buffer);
        }
        tempLine = strtok_r(buffer, delimiter1 , &tempLinePtr);
        while(tempLine != NULL) {
            if(ENABLE_LOGGING){
                printf("tempLine: %s\n", tempLine);
            }
            values = strtok_r(tempLine, delimiter2 , &valuesPtr);

            while(values != NULL){
                if(ENABLE_LOGGING){
                    printf("values: %s\n", values);
                    printf("counterInOutput %d\n", counterInOutput);
                }

                tempPtr = malloc(sizeof(char*));

                strncpy(tempPtr, values, 8);
    
                if(ENABLE_LOGGING){
                    printf("tempPtr: %s\n", tempPtr);
                }

                if(indicatorInOutput == 0){
                    input[counterLine]->input[counterInOutput] = tempPtr;
                } else {
                    input[counterLine]->output[counterInOutput] = tempPtr;
                }

                counterInOutput++;
                values = strtok_r(NULL, delimiter2 , &valuesPtr);
            }

            counterInOutput = 0;
            indicatorInOutput++;
            tempLine = strtok_r(NULL, delimiter1 , &tempLinePtr);
        }

        if(ENABLE_LOGGING){
            printf("\n");
        }

        counterLine++;
        indicatorInOutput = 0;
    }
}

void print(struct inputLine** input){
    for(int i = 0; i < NUMBER_INPUT_LINES; i++){
        printf("line %d: ", i);
        for(int idxInput = 0; idxInput < NUMBER_INPUT; idxInput++){
            printf("%s ", input[i]->input[idxInput]);
        }

        printf("| ");

        for(int idxOutput = 0; idxOutput < NUMBER_OUTPUT; idxOutput++){
            printf("%s ", input[i]->output[idxOutput]);
        }

        printf("\n");
    }
    
    printf("\n");
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