import math
import multiprocessing
import random
import time

import matplotlib.pyplot as plt


def generate(num):
    result = [i for i in range(num)]
    random.shuffle(result)
    return result


def is_sorted(inp_arr: []):
    if len(inp_arr) == 0:
        print("array is empty")
        return
    for i in range(len(inp_arr) - 1):
        if inp_arr[i] > inp_arr[i + 1]:
            print("array is not sorted")
            return
    print("array is sorted")


def merge(*args):
    # Support explicit left/right args, as well as a two-item
    # tuple which works more cleanly with multiprocessing.
    left, right = args[0] if len(args) == 1 else args
    left_length, right_length = len(left), len(right)
    left_index, right_index = 0, 0
    merged = []
    while left_index < left_length and right_index < right_length:
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1
    if left_index == left_length:
        merged.extend(right[right_index:])
    else:
        merged.extend(left[left_index:])
    return merged


def merge_sort(data):
    length = len(data)
    if length <= 1:
        return data
    middle = int(length / 2)
    left = merge_sort(data[:middle])
    right = merge_sort(data[middle:])
    return merge(left, right)


def merge_sort_parallel(data, processes):
    pool = multiprocessing.Pool(processes=processes)
    size = int(math.ceil(float(len(data)) / processes))
    data = [data[i * size:(i + 1) * size] for i in range(processes)]
    data = pool.map(merge_sort, data)
    while len(data) > 1:
        extra = data.pop() if len(data) % 2 == 1 else None
        data = [(data[i], data[i + 1]) for i in range(0, len(data), 2)]
        data = pool.map(merge, data) + ([extra] if extra else [])
    return data[0]


if __name__ == '__main__':
    nums_processes = [2, 4, 8,12,16]
    lengths = [1_000, 5_000, 10_000, 50_000, 100_000, 500_000, 1_000_000, 5_000_000, 10_000_000, 50_000_000]

    times = [[]]
    for length in lengths:
        unsorted_array = generate(length)
        start = time.time()
        sorted_array = merge_sort(unsorted_array)
        end = time.time()
        times[0].append(end - start)
    print(f"Single thread time:{times[0]}")

    for i, num_processes in enumerate(nums_processes):
        times.append([])
        for length in lengths:
            unsorted_array = generate(length)
            start = time.time()
            sorted_array = merge_sort_parallel(unsorted_array, num_processes)
            end = time.time()
            times[i+1].append(end - start)
        print(f"{num_processes} processes time:{times[i+1]}")

    for time in times:
        plt.plot(lengths, time)
    nums_processes = [1, 2, 4,  8]
    plt.legend(nums_processes)
    plt.xlabel("Length of array")
    plt.ylabel("Time")
    plt.xscale("log")
    plt.show()
