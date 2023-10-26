# Teorema master = T(n) = aT(n/b) + f(n)
# Unde a = numar de subprograme
#      b = complexitatea subprogramului ralativ la programul curent


# 1
# Complexitate: T(n) = T(n/2)+1
def binary_search(list, l, r, x):
    if r >= l:
        mid = l + (r - l) // 2
        if list[mid] == x:
            return mid
        elif list[mid] > x:
            return binary_search(list, l, mid - 1, x)
        else:
            return binary_search(list, mid + 1, r, x)

    else:
        return -1


list = [2, 3, 4, 10, 40]
x = 10
print(binary_search(list, 0, len(list) - 1, x))


# 2
# Complexitate: T(n) = T(n/2)+n
def partition(list, l, r):
    x = list[r]
    i = l
    for j in range(l, r):
        if list[j] <= x:
            list[i], list[j] = list[j], list[i]
            i += 1
    list[i], list[r] = list[r], list[i]
    return i

# 6
# 3
def quick_select(list, l, r, k):
    if 0 < k <= r - l + 1:
        index = partition(list, l, r)
        if index - l == k - 1:
            return list[index]
        if index - l > k - 1:
            return quick_select(list, l, index - 1, k)
        return quick_select(list, index + 1, r, k - index + l - 1)
    return -1

# 10, 4, 5, 8, 6, 11 | 26
# 10, 4, 5, 8, 6 | 11
# 4, 5, 6, 10, 8

list = [10, 4, 5, 8, 6, 11, 26]
n, k = len(list), 3
print(quick_select(list, 0, n - 1, k))


# 3
# Complexitate: T(n) = T(n) + 1
def count_appearances(list, x, search_right=False):
    (left, right) = (0, len(list) - 1)
    result = -1
    while left <= right:
        mid = (left + right) // 2
        if x == list[mid]:
            result = mid
            if search_right:
                right = mid - 1
            else:
                left = mid + 1
        elif x < list[mid]:
            right = mid - 1
        else:
            left = mid + 1
    return result


list = [5, 5, 2, 5, 6, 8, 6, 9, 1, 9]
list.sort()
key = 5
first = count_appearances(list, key, True)
last = count_appearances(list, key)
count = last - first + 1
print(count)
