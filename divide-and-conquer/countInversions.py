import math


def merge_and_count(a: list, b: list) -> tuple[list, int]:
    '''Merges two sorted arrays of integers and returns the number of inversions'''
    merged = []
    inv = 0
    i = 0
    j = 0
    while i < len(a) or j < len(b):
        if i < len(a) and j < len(b):
            if b[j] < a[i]:
                inv += len(a) - i
                merged.append(b[j])
                j += 1
            else:
                merged.append(a[i])
                i += 1
        elif j < len(b):
            merged.append(b[j])
            j += 1
        else:
            merged.append(a[i])
            i += 1
    return merged, inv

def sort_and_count(arr: list) -> tuple[list, int]:
    '''Sorts an array of non-repeating integers and returns sorted array and number of inversions'''
    if len(arr) == 1:
        return arr, 0
    else:
        midpt = math.floor(len(arr)/2)
        x, left_inv = sort_and_count(arr[0:midpt])
        y, right_inv = sort_and_count(arr[midpt:len(arr)])
        merged, overall_inv = merge_and_count(x, y)
    return merged, left_inv + right_inv + overall_inv

test_array = [2, 4, 1, 3, 5]
sorted_array, n_inversions = sort_and_count(test_array)
assert n_inversions == 3
print(sorted_array)

with open('data/IntegerArray.txt') as f:
    lines = f.read().splitlines()
    nums = [int(line) for line in lines]

f.close()

_, inversions = sort_and_count(nums)
print(inversions)
