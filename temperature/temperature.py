import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

min_val = 9999

n = int(input())  # the number of temperatures to analyse
for i in input().split():
    # t: a temperature expressed as an integer ranging from -273 to 5526
    t = int(i)
    
    #print("t:{} min_val:{}".format(t, min_val))

    if abs(t) < abs(min_val):
        min_val = t
    elif abs(t) == abs(min_val):
        if min_val < 0 and t > 0:
            min_val = t

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr)

if n == 0:
    print("0")
else:
    print(min_val)
