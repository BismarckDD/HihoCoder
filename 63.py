COUNT = 0
EDGE = [0] * 13
MAP = [0] * (1<<12)
DP = [[0]*(1<<12) for x in range(0, 13)]
hasOnes = [0] * (1<<12)
"""
def dfs(u, unused):
    global COUNT
    global EDGE
    global MAP
    if not unused:
        COUNT += EDGE[u] & 1
        return
    rest = unused & EDGE[u]
    while rest:
        temp = rest & (-rest)
        dfs(MAP[temp], unused-temp)
        rest -= temp
    return
"""


def calcOnes(n):
    global hasOnes
    for i in range(0, 1<<n):
        cnt = 0
        t = i
        while t:
            t &= (t-1)
            cnt += 1
        hasOnes[i] = cnt


def calc(n):
    global DP
    global hasOnes
    global COUNT
    global EDGE
    for numberOfOnes in range(n, -1, -1):
        for status in range(0, (1<<n)):
            if hasOnes[status] == numberOfOnes:
                for prev in range(1, n+1):
                    for curr in range(1, n+1):
                        if not status&(1<<(curr-1)) and EDGE[prev]&(1<<(curr-1)) and prev != curr:
                            DP[curr][status] += DP[prev][status + (1<<(curr-1))]
    for i in range(1, n+1):
        if EDGE[i] & 1:
            COUNT += DP[i][0]

(n, m) = (int(x) for x in raw_input().split())
for i in range(0, n):
    MAP[1 << i] = i+1
while m > 0:
    (a, b) = (int(x) for x in raw_input().split())
    EDGE[a] |= (1 << (b-1))
    m -= 1
#dfs(1, (1<<n)-2)
DP[1][(1<<n)-2] = 1
calcOnes(n)
calc(n)
print COUNT



