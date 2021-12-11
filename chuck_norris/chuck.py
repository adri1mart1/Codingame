import sys
import math
import binascii

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

message = input()
headers = ['00','0']

bin_rep = ''
for c in str(message):
    bin_rep += bin(int(binascii.hexlify(c.encode()), 16))[2:].zfill(7)


current_bit = 0 if bin_rep[0] == str(0) else 1

# print first header
print('{} '.format(headers[current_bit]), end='')

for b in bin_rep:
    if b == str(current_bit):
        print('0', end='')
    else:
        # change so print header + bit
        print(' ' + headers[int(b)] + ' 0', end='')
        current_bit = b

print('')