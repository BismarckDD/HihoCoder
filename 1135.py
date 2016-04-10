(x, y, z) = (int(x) for x in raw_input().split(' '))
aa = sorted([x, y, z])
ans = 0
ss = raw_input()
r, g, b = 0, 0, 0
for ch in ss:
    if ch == 'R':
        r += 1
    elif ch == 'Y':
        g += 1
    elif ch == 'B':
        b += 1
    else:
        r = g = b = 0
    ans = max(ans, r+g+b)
    bb = sorted([abs(r-g), abs(g-b), abs(b-r)])
    if aa[0] == bb[0] and aa[1] == bb[1] and aa[2] == bb[2]:
        r, g, b = 0, 0, 0
print ans