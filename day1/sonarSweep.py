import csv

# code is messy

with open('inputPart1.csv') as inputPart1File, open('inputPart2.csv') as inputPartTwoFile:
    # Part 1
    inputPart1 = csv.reader(inputPart1File, delimiter=',')
    numberIncreasesPartOne = 0
    lastRow = ""
    for row in inputPart1:
        if(lastRow != "" and int(row[0]) > int(lastRow[0])):
            numberIncreasesPartOne += 1
        lastRow = row
    print("Part 1: " + str(numberIncreasesPartOne))

    # Part 2
    inputPartTwo = csv.reader(inputPartTwoFile, delimiter=',')
    numberIncreasesPartTwo = 0
    window = list()
    for row in inputPartTwo:
        window.append(int(row[0]))
        if len(window) > 3:
            numberIncreasesPartTwo += sum(window[0:len(window)-1]) < sum(window[1:len(window)])
            window.pop(0)
    print("Part 2: " + str(numberIncreasesPartTwo))