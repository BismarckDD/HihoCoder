MAXN = 32
MAXM = 20002
C = [[0]*150 for i in range(0, MAXN)]
V = [0] * MAXN
F = [0] * MAXM
(n, m) = (int(x) for x in raw_input().split())
for i in range(0, n):
    (V[i], C[i][1]) = (int(x) for x in raw_input().split())
    tmp = int(1.07 * C[i][1])
    j = 2
    while True:
        C[i][j] = C[i][j-1] + tmp
        if C[i][j] > m or j > 146:
            break
        tmp = int(1.07 * tmp)
        j += 1
    for j in range(m, 0, -1):
        k = 1
        while C[i][k] <= j and k <= 146:
            F[j] = max(F[j], F[j - C[i][k]] + V[i] * k)
            k += 1

ret = 0
for j in range(1, m+1):
    ret = max(ret, F[j])
print ret
