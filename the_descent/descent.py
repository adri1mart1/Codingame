import sys
import math

# The while loop represents the game.
# Each iteration represents a turn of the game
# where you are given inputs (the heights of the mountains)
# and where you have to print an output (the index of the mountain to fire on)
# The inputs you are given are automatically updated according to your last actions.


# game loop

while True:
    arr = []
    for i in range(8):
        mountain_h = int(input())  # represents the height of one mountain.
        arr.append(mountain_h)

    max_val = 0
    max_idx = 0
    idxes = []
    i = 0
    while i < len(arr):
        if i not in idxes and arr[i] > max_val:
            max_val = arr[i]
            max_idx = i
            idxes.append(i)
        i+=1

    # The index of the mountain to fire on.
    print(max_idx)
