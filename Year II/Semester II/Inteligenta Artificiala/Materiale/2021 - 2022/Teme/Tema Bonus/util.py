from time import time
from math import sqrt, pow


def in_list(list, node):
    for s in list:
        if s.info == node.info:
            return s
    return None


def insert_node(node, list):
    idx = 0
    while idx < len(list) and (node.f > list[idx].f or (node.f == list[idx].f and node.g < list[idx].g)):
        idx += 1
    list.insert(idx, node)
