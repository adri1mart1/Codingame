import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())  # Number of elements which make up the association table.
q = int(input())  # Number Q of file names to be analyzed.
exts_mt = {}

for i in range(n):
    # ext: file extension
    # mt: MIME type.
    ext, mt = input().split()
    exts_mt[ext] = mt

def get_extension(s):
    if s.rfind('.') == -1:
        return None
    elif s.rfind('.') == len(s)-1:
        return None
    return s[s.rfind('.')+1:]

for i in range(q):
    fname = input()  # One file name per line.
    
    file_ext = get_extension(fname)

    if file_ext and file_ext.upper() in (e.upper() for e in exts_mt):
        # extension is in list, we need to find the index
        for k, v in exts_mt.items():
            if k.upper() == file_ext.upper():
                print(v)
                break
    else:
        print("UNKNOWN")
