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


def quick_select(list, l, r, k):
    if 0 < k <= r - l + 1:
        index = partition(list, l, r)
        if index - l == k - 1:
            return list[index]
        if index - l > k - 1:
            return quick_select(list, l, index - 1, k)
        return quick_select(list, index + 1, r, k - index + l - 1)
    return -1


list = [10, 4, 5, 8, 6, 11, 26]
n, k = len(list), 3
print(quick_select(list, 0, n - 1, k))


# 3
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

#5
# Python3 program to calculate pow(x,n) 

# Function to calculate x 
# raised to the power y 
def power(x, y): 

	if (y == 0): return 1
	elif (int(y % 2) == 0): 
		return (power(x, int(y / 2)) *
			power(x, int(y / 2))) 
	else: 
		return (x * power(x, int(y / 2)) *
				power(x, int(y / 2))) 

# Driver Code 
x = 2; y = 3
print(power(x, y)) 


#6

#T(n) = 2T(n/2) + Θ(n)

# A Divide and Conquer based program 
# for maximum subarray sum problem 

# Find the maximum possible sum in 
# arr[] auch that arr[m] is part of it 
def maxCrossingSum(arr, l, m, h) : 
	
	# Include elements on left of mid. 
	sm = 0; left_sum = -10000
	
	for i in range(m, l-1, -1) : 
		sm = sm + arr[i] 
		
		if (sm > left_sum) : 
			left_sum = sm 
	
	
	# Include elements on right of mid 
	sm = 0; right_sum = -1000
	for i in range(m + 1, h + 1) : 
		sm = sm + arr[i] 
		
		if (sm > right_sum) : 
			right_sum = sm 
	

	# Return sum of elements on left and right of mid 
	# returning only left_sum + right_sum will fail for [-2, 1] 
	return max(left_sum + right_sum, left_sum, right_sum) 


# Returns sum of maxium sum subarray in aa[l..h] 
def maxSubArraySum(arr, l, h) : 
	
	# Base Case: Only one element 
	if (l == h) : 
		return arr[l] 

	# Find middle point 
	m = (l + h) // 2

	# Return maximum of following three possible cases 
	# a) Maximum subarray sum in left half 
	# b) Maximum subarray sum in right half 
	# c) Maximum subarray sum such that the 
	#	 subarray crosses the midpoint 
	return max(maxSubArraySum(arr, l, m), 
			maxSubArraySum(arr, m+1, h), 
			maxCrossingSum(arr, l, m, h)) 
			

# Driver Code 
arr = [2, 3, 4, 5, 7] 
n = len(arr) 

max_sum = maxSubArraySum(arr, 0, n-1) 
print("Maximum contiguous sum is ", max_sum) 


#7
'''Python3 Program to check for majority element in a sorted array'''

# This function returns true if the x is present more than n / 2
# times in arr[] of size n */
def isMajority(arr, n, x):
	
	# Find the index of first occurrence of x in arr[] */
	i = _binarySearch(arr, 0, n-1, x)

	# If element is not present at all, return false*/
	if i == -1:
		return False

	# check if the element is present more than n / 2 times */
	if ((i + n//2) <= (n -1)) and arr[i + n//2] == x:
		return True
	else:
		return False

# If x is present in arr[low...high] then returns the index of
# first occurrence of x, otherwise returns -1 */
def _binarySearch(arr, low, high, x):
	if high >= low:
		mid = (low + high)//2 # low + (high - low)//2;

		''' Check if arr[mid] is the first occurrence of x.
			arr[mid] is first occurrence if x is one of the following
			is true:
			(i) mid == 0 and arr[mid] == x
			(ii) arr[mid-1] < x and arr[mid] == x'''
		
		if (mid == 0 or x > arr[mid-1]) and (arr[mid] == x):
			return mid
		elif x > arr[mid]:
			return _binarySearch(arr, (mid + 1), high, x)
		else:
			return _binarySearch(arr, low, (mid -1), x)
	return -1


# Driver program to check above functions */
arr = [1, 2, 3, 3, 3, 3, 10]
n = len(arr)
x = 3
if (isMajority(arr, n, x)):
	print ("% d appears more than % d times in arr[]"
											% (x, n//2))
else:
	print ("% d does not appear more than % d times in arr[]"
													% (x, n//2))


#8 T(n) = T(k) + T(n-k-1) + \theta(n)

 # Python program for implementation of Quicksort Sort 

# This function takes last element as pivot, places 
# the pivot element at its correct position in sorted 
# array, and places all smaller (smaller than pivot) 
# to left of pivot and all greater elements to right 
# of pivot 
def partition(arr,low,high): 
	i = ( low-1 )		 # index of smaller element 
	pivot = arr[high]	 # pivot 

	for j in range(low , high): 

		# If current element is smaller than the pivot 
		if arr[j] < pivot: 
		
			# increment index of smaller element 
			i = i+1
			arr[i],arr[j] = arr[j],arr[i] 

	arr[i+1],arr[high] = arr[high],arr[i+1] 
	return ( i+1 ) 

# The main function that implements QuickSort 
# arr[] --> Array to be sorted, 
# low --> Starting index, 
# high --> Ending index 

# Function to do Quick sort 
def quickSort(arr,low,high): 
	if low < high: 

		# pi is partitioning index, arr[p] is now 
		# at right place 
		pi = partition(arr,low,high) 

		# Separately sort elements before 
		# partition and after partition 
		quickSort(arr, low, pi-1) 
		quickSort(arr, pi+1, high) 

# Driver code to test above 
arr = [10, 7, 8, 9, 1, 5] 
n = len(arr) 
quickSort(arr,0,n-1) 
print ("Sorted array is:") 
for i in range(n): 
	print ("%d" %arr[i]), 

