import sys
import math

n = int(input())
objs = []

# retrieve value (either arg1 or arg2)
def retrieve(val):
    if val[0] == '$':
        cell_number = int(val[1:])
        if objs[cell_number]['solved'] == False:
            return None
        else:
            return int(objs[cell_number]['value'])
    else:
        return int(val)

# trying to resolve object i
# return 0 on success
# return 1 if dependencies needs to be resolved first
def resolve(i):
    if objs[i]['solved'] == True:
        return 0
    if objs[i]['op'] == 'VALUE':
        a1 = retrieve(objs[i]['arg1'])
        if a1 != None:
            objs[i]['value'] = a1
            objs[i]['solved'] = True
            return 0
        return 1
    else:
        a1 = retrieve(objs[i]['arg1'])
        a2 = retrieve(objs[i]['arg2'])
        if a1 == None or a2 == None:
            return 1
        else:
            if objs[i]['op'] == 'ADD':
                objs[i]['value'] = int(a1 + a2)
            elif objs[i]['op'] == 'SUB':
                objs[i]['value'] = int(a1 - a2)
            else: # multiplication
                objs[i]['value'] = int(a1 * a2)
            objs[i]['solved'] = True
            return 0

# Geting all input values and store it in a dict array objs
for i in range(n):
    operation, arg_1, arg_2 = input().split()
    obj = {}
    obj['solved'] = False
    obj['op'] = operation
    obj['arg1'] = arg_1
    obj['arg2'] = arg_2
    obj['value'] = 0
    objs.append(obj)

# Starting to resolve all obj in objs
while True:
    unsolved = 0
    for i in range(n):
        unsolved = unsolved + resolve(i)
    if unsolved == 0:
        break        

# print resolved results
for i in objs:
    print(i['value'])