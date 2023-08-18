from typing import List
import math
import numpy as np

def choosePivot(arr: List[int], low: int, high: int, pivotType: str) -> int:
    """Chooses pivot according to pivot type selected by the user"""
    if pivotType == "median_of_three":
        indices = [low, high, low + math.floor((high-low)/2)]
        values = [arr[i] for i in indices]
        median = np.median(values)
        median_index = values.index(median)
        return indices[median_index]
    elif pivotType == "first":
        return low
    else:
        return high

def partition(arr: List[int], low: int, high: int, p: int) -> int:
    """Partitions the array around the pivot"""
    if p != low:
        temp = arr[low]
        arr[low] = arr[p]
        arr[p] = temp
    p = low
    pivot = arr[p]
    i = p
    for j in range(p+1,high+1):
        if arr[j] <= pivot:
            i += 1
            temp = arr[i]
            arr[i] = arr[j]
            arr[j] = temp
    temp = arr[i]
    arr[i] = pivot
    arr[p] = temp
    return i

def quicksort(arr: List[int], low: int, high: int, pivotType: str) -> int:
    """Sorts the array using QuickSort and returns the total number of swaps"""
    if low >= high:
        return 0 
    p = choosePivot(arr, low, high, pivotType)
    p = partition(arr, low, high, p)
    swaps_left = quicksort(arr, low, p-1, pivotType)
    swaps_right = quicksort(arr, p+1, high, pivotType)
    return high - low + swaps_left + swaps_right


# Tests
with open('data/QuickSortTest.txt') as f:
    lines = f.read().splitlines()
    nums = [int(line) for line in lines]

f.close()

swaps_first = quicksort(nums.copy(), 0, len(nums) - 1, "first")
swaps_last = quicksort(nums.copy(), 0, len(nums) - 1, "last")
swaps_median = quicksort(nums.copy(), 0, len(nums) - 1, "median_of_three")

print(swaps_first)
print(swaps_last)
print(swaps_median)