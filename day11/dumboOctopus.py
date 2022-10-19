import csv
import os
import sys

def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    retVal = []

    for row in data:
        temp = []
        for char in row:
            temp.append(int(char))
        retVal.append(temp)

    return retVal


def printData(data, step):
    print("\nAfter Step " + str(step) + ":")
    for i in range(0, 10):
        for j in range(0, 10):
            print(str(data[i][j]) + " ", end = '')
        print("")



def flash(data, i, j, current_flashes):
    if data[i][j] >= 10:
        data[i][j] = -100
        current_flashes += 1
        if i > 0:
            data[i - 1][j] += 1
            current_flashes = flash(data, i - 1, j, current_flashes)
        if i > 0 and j > 0:
            data[i - 1][j - 1] += 1
            current_flashes = flash(data, i - 1, j - 1, current_flashes)
        if j > 0:
            data[i][j - 1] += 1
            current_flashes = flash(data, i, j - 1, current_flashes)
        if i < 9 and j > 0:
            data[i + 1][j - 1] += 1
            current_flashes = flash(data, i + 1, j - 1, current_flashes)
        if i < 9:
            data[i + 1][j] += 1
            current_flashes = flash(data, i + 1, j, current_flashes)
        if i < 9 and j < 9:
            data[i + 1][j + 1] += 1
            current_flashes = flash(data, i + 1, j + 1, current_flashes)
        if j < 9:
            data[i][j + 1] += 1
            current_flashes = flash(data, i, j + 1, current_flashes)
        if i > 0 and j < 9:
            data[i - 1][j + 1] += 1
            current_flashes = flash(data, i - 1, j + 1, current_flashes)

    else:
        return current_flashes

    return current_flashes



def calcFlashes(data, step, current_flashes, indicator):
    if not indicator:
        # Routine 1
        for i in range(0, 10):
            for j in range(0, 10):
                data[i][j] += 1

        # Routine 2
        for i in range(0, 10):
            for j in range(0, 10):
                current_flashes = flash(data, i, j, current_flashes)

        counter_sim = 0;

        # Routine 3
        for i in range(0, 10):
            for j in range(0, 10):
                if data[i][j] < 0 or data[i][j] > 9:
                    data[i][j] = 0
                    counter_sim += 1

        if counter_sim == 100:
            print("Reached on step " + str(step))
            indicator = True

    else:
        return current_flashes
    
    current_flashes = calcFlashes(data, step + 1, current_flashes, indicator)

    return current_flashes


def main():
    data = getData("inputPartOne.csv")
    result = calcFlashes(data, 0, 0, False)
    print("Result Part 1: " + str(result))

    data = getData("inputPartOne.csv")
    result = calcFlashes(data, 0, 0, False)


if __name__ == "__main__":
    main()

