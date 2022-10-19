import csv
import os
import sys

def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    return data

def checkBrackets(string=''):
    stack = []
    brackets = {'(': ')', '[': ']', '{': '}', '<': '>'}
    score_dict = {')': 3, ']': 57, '}': 1197, '>': 25137}
    score_complete_dict = {')': 1, ']': 2, '}': 3, '>': 4}

    score = 0
    score_complete = 0
    brackets_ok = True

    for symbol in string:
        if symbol in brackets.keys():
            stack.append(symbol)
        elif symbol in brackets.values():
            if stack:
                bracket = stack.pop()
                if brackets.get(bracket) != symbol:
                    print(
                        f' - {string} - Expected {brackets.get(bracket)}, but found {symbol} instead.'
                    )
                    score += score_dict[symbol]
                    brackets_ok = False
                    break
            else:
                break

    if stack and brackets_ok:
        complete_stack = []
        for item in stack[::-1]:
            complete_stack.append(brackets.get(item))
            score_complete = score_complete * 5 + score_complete_dict[
                brackets.get(item)]
        stack_string = ''.join(complete_stack)
        print(
            f' - {string} - Complete by adding {stack_string} - {score_complete} total points.'
        )

    return score, score_complete

def main():
    data = getData("inputPartOne.csv")

    result = 0
    result_part_two = []
    for row in data:
        score, score_complete = checkBrackets(row.replace('\n', ''))
        result += score
        if score_complete != 0:
            result_part_two.append(score_complete)

    print('result: ' + str(result))
    print('result part two: ' + str(sorted(result_part_two)[len(result_part_two) // 2]))


if __name__ == "__main__":
    main()

