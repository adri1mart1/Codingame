import sys
import math

lon = input()
ln = float(lon.replace(',','.'))
lat = input()
la = float(lat.replace(',','.'))
n = int(input())
defibs = []

for i in range(n):
    defib = input()
    num, name, address, phone, lng, latt = defib.split(';')
    d = {}
    d['name'] = name
    d['lng'] = float(lng.replace(',','.'))
    d['lat'] = float(latt.replace(',','.'))
    defibs.append(d)

shortest_d = 9999
shortest_idx = 0

for i in range(len(defibs)):
    x = (ln - defibs[i]['lng']) * math.cos((defibs[i]['lat'] + la) / 2)
    y = la - defibs[i]['lat']
    d = math.sqrt(x*x + y*y) * 6371

    if d < shortest_d:
        shortest_d = d
        shortest_idx = i

print(defibs[shortest_idx]['name'])