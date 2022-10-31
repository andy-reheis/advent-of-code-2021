import csv
import os
import sys
from operator import add, mul, gt, lt, eq

def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    ret_val = []
    for row in data:
        ret_val.append(row)

    return ret_val


def convert_to_binary(packet):
    converted = ''
    for char in packet:
        converted += format(int(char, 16), '0>4b')

    print("Converted to:")
    print(converted)

    return converted


def parse(line):
    bits = ((int(c, 16) >> i) & 1 for c in line for i in range(3, -1, -1))
    ops = add, mul, lambda *x: min(x), lambda *x: max(x), None, gt, lt, eq
    pos = ver = 0

    def read(size):
        nonlocal pos
        pos += size
        return sum(next(bits) << i for i in range(size - 1, -1, -1))

    def packet():
        nonlocal ver
        ver += read(3)

        if (type_id := read(3)) == 4:
            go, total = read(1), read(4)
            while go:
                go, total = read(1), total << 4 | read(4)
        elif read(1) == 0:
            length = read(15) + pos
            total = packet()
            while pos < length:
                total = ops[type_id](total, packet())
        else:
            count = read(11)
            total = packet()
            for _ in range(count - 1):
                total = ops[type_id](total, packet())

        return total

    total = packet()

    return ver, total


def main():
    packet_example = getData("inputExample.csv")
    for line in packet_example:
        version_example, total_example = parse(line)
        print("Sum version: " + str(version_example))
        print("Total: " + str(total_example))
        print("==========================")

    packet_part_one = getData("input.csv")
    for line in packet_part_one:
        version_part_one, total_part_one = parse(line)
        print("Sum version: " + str(version_part_one))
        print("Total: " + str(total_part_one))
        print("==========================")
if __name__ == "__main__":
    main()
