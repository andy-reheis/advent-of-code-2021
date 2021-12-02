import csv

with open('inputPart1.csv') as inputPart1File, open('inputPart2.csv') as inputPart2File:
    # Part 1
    inputPart1 = csv.reader(inputPart1File, delimiter=' ')
    horizontalPosition = 0
    depth = 0
    for row in inputPart1:
        depth += int(row[1]) * -1 if row[0] == "up" else int(row[1]) if row[0] == "down" else 0
        horizontalPosition += (int(row[1]) if row[0] == "forward" else 0)

    print("Part 1")
    print("horizontal: " + str(horizontalPosition));
    print("depth: " + str(depth))
    print("result: " + str(depth * horizontalPosition))

    # Part 2
    inputPart2 = csv.reader(inputPart2File, delimiter=' ')
    horizontalPosition = 0
    depth = 0
    aim = 0
    for row in inputPart2:
        aim += int(row[1]) * -1 if row[0] == "up" else int(row[1]) if row[0] == "down" else 0
        horizontalPosition += (int(row[1]) if row[0] == "forward" else 0)
        depth += aim * int(row[1]) if row[0] == "forward" else 0
    
    print("Part 2")
    print("horizontal: " + str(horizontalPosition));
    print("depth: " + str(depth))
    print("result: " + str(depth * horizontalPosition))