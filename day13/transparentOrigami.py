import csv
import os
import sys
from collections import defaultdict

def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    ret_val = defaultdict(list)
    instructions = []

    for row in data:
        splitted = row.split(",")
        if len(splitted) > 1:
            ret_val[int(splitted[1])].append(int(splitted[0]))
        elif len(row) > 2:
            instructions.append(row)

    vertical_length = max(ret_val, key=int) + 1
    horizontal_length = 0
    for k in ret_val.values():
        if max(k) + 1 > horizontal_length:
            horizontal_length = max(k) + 1

    prettier_ret_val = []
    for i in range(0, vertical_length):
        prettier_ret_val.append([])
        for j in range(0, horizontal_length):
            if j in ret_val[i]:
                prettier_ret_val[i].append('#')
            else:
                prettier_ret_val[i].append('.')

    return prettier_ret_val, instructions


def printData(data):
    print("-----------------------------")
    for i in range(0, len(data)):
        for j in range(0, len(data[i])):
            print(data[i][j], end = '')
        print()
    print("-----------------------------")



def fold(data, instruction):
    ret_val = []
    fold_index = int(instruction.split("=")[1])
    fold_along_x = "x" in instruction

    print("dimensions: " + str(len(data)) + " x " + str(len(data[0])))
    print(instruction)

    if not fold_along_x:
        new_length = int(len(data) / 2)

        for i in range(0, new_length):
            ret_val.append([])
            for j in range(0, len(data[0])):
                if data[i][j] == '#' or data[len(data) - 1 - i][j] == '#':
                    ret_val[i].append('#')
                else:
                    ret_val[i].append('.')
  
    else:
        new_width = int(len(data[0]) / 2)
        for i in range(0, len(data)):
            ret_val.append([])
            for j in range(0, new_width):
                if data[i][j] == '#' or data[i][len(data[0]) - 1 - j] == '#':
                    ret_val[i].append('#')
                else:
                    ret_val[i].append('.')                    

    return ret_val


def countDots(data):
    counter = 0

    for i in range(0, len(data)):
        for j in range(0, len(data[0])):
            if data[i][j] == '#':
                counter += 1

    return counter


def main():
    data_part_one, instructions = getData("input.csv")
    data_part_two, instructions = getData("input.csv")

    for i in range(0, len(instructions)):
        data_part_one = fold(data_part_one, instructions[i])
        break
    
    print("Result Part 1: " + str(countDots(data_part_one)))

    for i in range(0, len(instructions)):
        data_part_two = fold(data_part_two, instructions[i])


    print("Result Part 2: Please read the letters")
    printData(data_part_two)



if __name__ == "__main__":
    main()

