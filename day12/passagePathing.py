import csv
import os
import sys
from collections import defaultdict

def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    retVal = defaultdict(list)

    for row in data:
        connection = row.strip().split('-')
        retVal[connection[0]].append(connection[1])
        retVal[connection[1]].append(connection[0])

    return retVal

def findPathOne(data, node, visited):
    res = []
    new_visit = visited + [node]
    if node == 'end':
        return [new_visit]
    for n in data[node]:
        if n != 'start':
            if n not in visited or n.isupper():
                temp_res = findPathOne(data, n, new_visit)
                res.extend(temp_res)
    return res

def findPathTwo(data, node, visited):
    res = []
    new_visit = visited + [node]
    if node == 'end':
        return [new_visit]

    for n in data[node]:
        if n != 'start':
            if n.isupper():
                temp_res = findPathTwo(data, n, new_visit)
                res.extend(temp_res)
            else:
                l_case = [i for i in new_visit if i.islower()]
                twice = any([True for i in l_case if l_case.count(i) > 1])
                if (twice and new_visit.count(n) < 1) or (not twice and new_visit.count(n) < 2):
                    temp_res = findPathTwo(data, n, new_visit)
                    res.extend(temp_res)
    
    return res

def main():
    data = getData("inputPartOne.csv")
    result = findPathOne(data, 'start', [])
    print("Result Part 1: " + str(len(result)))

    resultPartTwo = findPathTwo(data, 'start', [])
    print("Result Part 2: " + str(len(resultPartTwo)))


if __name__ == "__main__":
    main()

