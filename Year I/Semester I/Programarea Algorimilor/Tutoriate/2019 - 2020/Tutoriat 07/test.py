

# T(n) = a*T(n/b) + f(n)
# a = numar de subprograme
# b = reducere complexitate

# P 1
# a = 1
# b = 2
# f(n) = 1
# T(n) = 1*T(n/2) + 1
# O(n) = log(n)

def cautare_binara(list, l, r, x):
    if r >= l:
        m = (l+r)//2
        if list[m] == x:
            return m
        if list[m] > x:
            return cautare_binara(list, l, m-1, x)
        return cautare_binara(list, m+1, r, x)
    return -1

list = [2, 3, 4, 10, 40]
x = 10
print(cautare_binara(list,0, len(list)-1, x))

# P 2
# T(n) = 1*T(n/2) + n

def partition(list, l, r):
    x = list[r]
    i = l
    for j in range(l, r):
        if list[j] <= x:
            list[i], list[j] = list[j], list[i]
            i += 1
    list[i], list[r] = list[r], list[i]
    return i

def quick_select(list, l, r, k):
    if 0 <= k <= r-l+1:
        index = partition(list, l, r)
        if index - l == k-1:
            print(list)
            return list[index]
        if index - l > k - 1:
            return quick_select(list, l, index-1, k)
        return quick_select(list, index+1, r, k-index+l-1)
    return -1


# 10 4 5 8 6 11 26
# 0 6
# 10 4 5 8 6 11
# 26
list2 = [10, 4, 5,5, 8, 6, 11, 26]
n, k = len(list2), 3
# 6 : 0 - 6
print(quick_select(list2, 0, n - 1, k))


# P 3
# T(n) = T(n/2)+1
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


list3 = [5, 5, 2, 5, 6, 8, 6, 9, 1, 9]
# [1, 2, 5, 5, 5, 6, 6, 8, 9, 9]
# 0 - 9
list3.sort()
print(list3)
key = 5
first = count_appearances(list3, key, True)
last = count_appearances(list3, key)
count = last - first + 1
print(count)

