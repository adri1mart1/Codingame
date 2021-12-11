import sys
import math

a1 = int(input())
n = int(input())

seq = []
digits = {}
seq.append(a1)
digits[a1] = 0

# expected sequence:
# 0, 0, 1, 0, 2, 0, 2, 2, 1, 6, 0, 5, 0, 2, 6, 5, 4, 0, 5, 3, 0, 3

def next(i):
    if not seq[i] in digits:
        digits[seq[i]] = i
        seq.append(0)
    else:
        times = i - digits[seq[i]]
        seq.append(times)
        digits[seq[i]] = i

for i in range(n-1):
    next(i)

print('{}'.format(int(seq[-1])))
