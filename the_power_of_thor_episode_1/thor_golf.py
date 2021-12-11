x,y,a,b = [int(i) for i in input().split()]
while True:
    input()
    m=""
    if y > b:
        m="S"
        b+=1
    elif y < b:
        m="N"
        b-=1
    if x > a:
        m+="E"
        a+=1
    elif x < a:
        m+="W"
        a-=1
    print(m)
