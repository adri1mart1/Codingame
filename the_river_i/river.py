import sys
import math

r1 = input()
r2 = input()

r1_next = int(r1)
r2_next = int(r2)

while True:
    if r1_next == r2_next:
        print(r1_next)
        break
    if r1_next < r2_next:
        for l in r1:
            r1_next += int(l)
    else:
        for l in r2:
            r2_next += int(l)
    r1 = str(r1_next)
    r2 = str(r2_next)