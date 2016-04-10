dp = [[-1] * 101 for i in range(0, 101)]
attractive = [-1] * 101
recommend = [False] * 101  # array(N+1)
child = [[-1] for i in range(0, 101)]  # array[N+1][1]
#father = [0] * 101


def solve():
    (N, K, M) = (int(x) for x in raw_input().split())
    # f[i][j] represents the max attractive it could acquire to visit j nodes in the tree whose root is i
    tmp = raw_input().split()
    for i in range(0, N):
        attractive[i + 1] = int(tmp[i])
    tmp = raw_input().split()
    for i in range(0, len(tmp)):
        attractive[int(tmp[i])] += 20000
    for i in range(0, N - 1):
        (a, b) = (int(x) for x in raw_input().split())
        child[a].append(b)
        #father[b] = a
    if N < M or M < K:
        # print "error"
        return -1
    #return helper(1, M) - 20000 * K
    dfs(1,M)
    return dp[1][M] - 20000 * K


def dfs(root, m):
    dp[root][1] = attractive[root]
    for i in range(1, len(child[root])):
        dfs(child[root][i], m-1)
        for j in range(m, 0, -1):
            if dp[root][j] == -1:
                continue
            for k in range(0, m-j+1):
                if dp[child[root][i]][k] == -1:
                    continue
                dp[root][j+k] = max(dp[root][j+k], dp[root][j] + dp[child[root][i]][k])
    return dp[root]



def helper(root, m):
    if m == 0:
        return 0
    if dp[root][m] != -1:
        return dp[root][m]
    # g[i][j] represents travel j node in trees rooted of first i children of current root, the max attractive score it could acquire
    chi = child[root]
    child_number = len(chi) - 1
    if child_number == 0:
        dp[root][m] = attractive[root]
        return dp[root][m]

    g = []
    for x in range(0, child_number + 1):
        g.append([0] * m)

    for i in range(1, child_number + 1):
        for j in range(0, m):
            for k in range(0, j + 1):
                if g[i][j] < g[i - 1][j - k] + helper(chi[i], k):
                    g[i][j] = g[i - 1][j - k] + helper(chi[i], k)

    dp[root][m] = g[child_number][m - 1] + attractive[root]
    return dp[root][m]

ans = solve()
if ans < 0:
    print "-1"
else:
    print ans
