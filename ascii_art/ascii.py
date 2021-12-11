import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

l = int(input())
h = int(input())
t = input()
rows = []
alphabet = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','?']

for i in range(h):
    row = input()
    rows.append(row)

for i in range(h):
    for c in str(t).upper():
        if c not in alphabet:
            c = alphabet[-1]
        start_idx = l*alphabet.index(c)
        print(rows[i][start_idx:start_idx+l:1], end='')
    print('')

