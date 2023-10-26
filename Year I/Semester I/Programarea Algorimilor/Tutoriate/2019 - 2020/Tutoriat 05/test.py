intervals = [[570, 670], [500, 590], [600, 680], [690, 840], [930, 1005], [730, 790], [700, 795], [900, 960]]

def calculateLengths(intervals):
    intervals.sort()
    total = 0
    current_start = intervals[0][0]
    current_end = intervals[0][1]
    for interval in intervals:
        if interval[0] < current_end:
            current_end = max(current_end, interval[1])
        else:
            total += current_end - current_start
            current_start = interval[0]
            current_end = interval[1]
    total += current_end - current_start
    return total

print(calculateLengths(intervals))
