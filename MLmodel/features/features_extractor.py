import numpy as np
from collections import Counter

def compute_size(arr):
    return len(arr)

def compute_order_ratio(arr):
    """
    relative sequential gradient = inc gradient - dec gradient
    range: [-1, 1]
        completely out of order ~= 0
    """
    n = len(arr)
    if n <= 1:
        return 1.0
    inc = 0
    dec = 0
    total = n - 1
    for i in range(total):
        if arr[i] < arr[i + 1]:
            inc += 1
        elif arr[i] > arr[i + 1]:
            dec += 1
    return (inc / total) - (dec / total)

def compute_duplicated_rank(arr):
    if not arr:
        return 0
    counts = Counter(arr)
    duplicates = sum(v - 1 for v in counts.values() if v > 1)
    return duplicates / len(arr)

def compute_unique_ratio(arr):
    if not arr:
        return 0
    return len(set(arr)) / len(arr)

def compute_entropy(arr):
    if not arr:
        return 0
    n = len(arr)
    counts = Counter(arr)
    probs = [v / n for v in counts.values()]
    entropy = -sum(p * np.log2(p) for p in probs if p > 0)
    return entropy

def compute_value_range(arr):
    if not arr:
        return 0
    return max(arr) - min(arr)

def compute_sorted_prefix_length(arr, direction):
    n = len(arr)
    if n == 0:
        return 0
    count = 1
    for i in range(1, n):
        if (direction == +1 and arr[i] >= arr[i - 1]) or (direction == -1 and arr[i] <= arr[i - 1]):
            count += 1
        else:
            break
    return count / n

def compute_sorted_suffix_length(arr, direction):
    n = len(arr)
    if n == 0:
        return 0
    count = 1
    for i in range(n - 2, -1, -1):
        if (direction == +1 and arr[i] <= arr[i + 1]) or (direction == -1 and arr[i] >= arr[i + 1]):
            count += 1
        else:
            break
    return count / n

def extract_features(arr, direction = +1):
    arr = list(arr) if not isinstance(arr, (list, tuple)) else arr
    order_ratio = compute_order_ratio(arr)
    effective_order = order_ratio * direction
    return {
        "size": compute_size(arr),
        "order_ratio": order_ratio,
        "effective_order": effective_order,
        "duplicated_rank": compute_duplicated_rank(arr),
        "unique_ratio": compute_unique_ratio(arr),
        "entropy": compute_entropy(arr),
        "value_range": compute_value_range(arr),
        "sorted_prefix_length": compute_sorted_prefix_length(arr, direction),
        "sorted_suffix_length": compute_sorted_suffix_length(arr, direction),
        "sort_direction": direction
    }