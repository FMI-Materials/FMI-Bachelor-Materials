# SPECIFICATION:
#
# The stats function computes some basic statistics functions
# when given a list of numbers as input.
#
# TASK:
#
# Achieve full statement coverage on the stats function.
# All you should have to do is modify the test function
# to call stats with different lists of values.

def stats(lst):
    min = None
    max = None
    freq = {}
    for i in lst:
        if min is None or i < min:
            min = i
        if max is None or i > max:
            max = i
        if i in freq:
            freq[i] += 1
        else:
            freq[i] = 1
    lst_sorted = sorted(lst)
    if len(lst_sorted) % 2 == 0:
        middle = len(lst_sorted)/2
        median = (lst_sorted[middle] + lst_sorted[middle-1]) / 2
    else:
        median = lst_sorted[int(len(lst_sorted)/2)]
    mode_times = None
    for i in freq.values():
        if mode_times is None or i > mode_times:
            mode_times = i
    mode = []
    for (num, count) in freq.items():
        if count == mode_times:
            mode.append (num)
    print("list = " + str(lst))
    print("min = " + str(min))
    print("max = " + str(max))
    print("median = " + str(median))
    print("mode(s) = " + str(mode))


def test():
    ###Your code here.
    # Change l to something that manages full coverage. You may
    # need to call stats twice with different input in order
    # to achieve full coverage.
    l = [31]
    stats(l)


test()
