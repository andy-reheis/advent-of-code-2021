import csv
import os
import sys
import heapq
from numpy import Inf


def getData(fileName):
    strPath = os.path.join(sys.path[0], fileName)
    with open(strPath) as fileObject:
        data = fileObject.read().split('\n')

    ret_val = []
    for row in data:
        temp = []
        for spot in row:
            temp.append(int(spot))

        ret_val.append(temp)

    return ret_val


def get_end(data):
    return (0, 0), (len(data) - 1, len(data[0]) - 1)


def get_neighbours(chiton_map, node):
    max_x = len(chiton_map) - 1
    max_y = len(chiton_map[0]) - 1

    neighbors = []
    if node[0] > 0:
        neighbors.append((node[0] - 1, node[1]))
    if node[0] < max_x:
        neighbors.append((node[0] + 1, node[1]))
    if node[1] > 0:
        neighbors.append((node[0], node[1] - 1))
    if node[1] < max_y:
        neighbors.append((node[0], node[1] + 1))

    return neighbors


def a_star(chiton_map, start_node, end_node):
    open_queue = []
    closed_queue = set()
    parents = {}
    g_score = {}

    for y in range(len(chiton_map)):
        for x in range(len(chiton_map)):
            g_score[(y, x)] = Inf

    g_score[start_node] = 0
    heapq.heappush(open_queue, (get_manhattan_distance(start_node, end_node), start_node))
    while open_queue:
        _, node = heapq.heappop(open_queue)

        if node == end_node:
            total = 0
            path = []
            
            while node in parents:
                total += chiton_map[node[1]][node[0]]
                path.append(node)
                node = parents[node]
            return path, total
        elif node in closed_queue:
            continue
        else:
            neighbours = get_neighbours(chiton_map, node)

            for neighbour in neighbours:
                if neighbour in closed_queue:
                    continue

                added_g_score = chiton_map[neighbour[1]][neighbour[0]]

                candidate_g = g_score[node] + added_g_score

                if candidate_g <= g_score[neighbour]:
                    g_score[neighbour] = candidate_g
                    parents[neighbour] = node
                    f = get_manhattan_distance(neighbour, end_node) + candidate_g
                    heapq.heappush(open_queue, (f, neighbour))

            closed_queue.add(node)

def get_manhattan_distance(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def print_path(chiton_map, path):
    for i in range(0, len(chiton_map)):
        for j in range(0, len(chiton_map[0])):
            if (i, j) in path:
                print(chiton_map[i][j], end = '')
            else:
                print("*", end = '')
        print()


def extend_data(data):
    d = len(data)
    max_list_size = len(data) * 5
    extended_data = [[0 for _ in range(max_list_size)] for _ in range(max_list_size)]

    for y_index, y in enumerate(extended_data):
        for x_index, x in enumerate(y):
            n = data[y_index % d][x_index % d]
            extended_data[y_index][x_index] = (n + ((y_index // d) + (x_index // d)) - 1) % 9 + 1
    
    return extended_data


def main():
    map_example = getData("inputExample.csv")
    start_example, end_example = get_end(map_example)
    path_example, cost_example = a_star(map_example, start_example, end_example)
    print("Example: " + str(cost_example))
    print_path(map_example, path_example)

    map_part_one = getData("input.csv")
    start_part_one, end_part_one = get_end(map_part_one)
    path_part_one, cost_part_one = a_star(map_part_one, start_part_one, end_part_one)
    print("Part 1: " + str(cost_part_one))

    map_part_two = extend_data(getData("input.csv"))
    start_part_two, end_part_two = get_end(map_part_two)
    path_part_two, cost_part_two = a_star(map_part_two, start_part_two, end_part_two)
    print("Part 2: " + str(cost_part_two))

if __name__ == "__main__":
    main()

