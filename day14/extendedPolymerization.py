import csv
import os
import sys
from itertools import combinations
from collections import defaultdict, Counter
import copy

def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    ret_val = defaultdict(list)
    template = ""

    for row in data:
        splitted = row.split(" -> ")
        if len(splitted) > 1:
            ret_val[splitted[0]] = [splitted[0][0] + splitted[1], splitted[1] + splitted[0][1]]
        elif len(row) > 2:
            template = row

    return ret_val, template

def polymer(pairs, mapping, steps):
    for _ in range(0, steps):
        result = defaultdict(int)
        for pair in pairs.keys():
            extended_pairs = mapping[pair]
            for extended in extended_pairs:
                result[extended] += pairs[pair]
        
        pairs = result
    
    return pairs

def main():
    pair_mapping_example, template_example = getData("inputExample.csv")
    pairs_example = [template_example[x:y] for x, y in combinations(range(len(template_example) + 1), r = 2) if len(template_example[x:y]) == 2 ]
    pairs_count_example = defaultdict(int)
    for pair in pairs_example:
        pairs_count_example[pair] += 1

    pairs_example = polymer(pairs_count_example, pair_mapping_example, 10)

    result_example = defaultdict(int)
    for key in pairs_example.keys():
        result_example[key[0]] += pairs_example[key]

    result_example[template_example[-1]] += 1

    print("Result Example: " + str(max(result_example.values()) - min(result_example.values())))



    pair_mapping_part_one, template_part_one = getData("input.csv")
    pairs_part_one = [template_part_one[x:y] for x, y in combinations(range(len(template_part_one) + 1), r = 2) if len(template_part_one[x:y]) == 2 ]
    pairs_count_part_one = defaultdict(int)
    for pair in pairs_part_one:
        pairs_count_part_one[pair] += 1

    pairs_part_one = polymer(pairs_count_part_one, pair_mapping_part_one, 10)

    result_part_one = defaultdict(int)
    for key in pairs_part_one.keys():
        result_part_one[key[0]] += pairs_part_one[key]

    result_part_one[template_part_one[-1]] += 1

    print("Result Part One: " + str(max(result_part_one.values()) - min(result_part_one.values())))


    pair_mapping_part_two, template_part_two = getData("input.csv")
    pairs_part_two = [template_part_two[x:y] for x, y in combinations(range(len(template_part_two) + 1), r = 2) if len(template_part_two[x:y]) == 2 ]
    pairs_count_part_two = defaultdict(int)
    for pair in pairs_part_two:
        pairs_count_part_two[pair] += 1

    pairs_part_two = polymer(pairs_count_part_two, pair_mapping_part_two, 40)

    result_part_two = defaultdict(int)
    for key in pairs_part_two.keys():
        result_part_two[key[0]] += pairs_part_two[key]

    result_part_two[template_part_two[-1]] += 1

    print("Result Part Two: " + str(max(result_part_two.values()) - min(result_part_two.values())))

if __name__ == "__main__":
    main()

