record = set()
cache = list()
size = 0
url = ""
(N, M) = (int(x) for x in raw_input().split())
while N > 0:
    url = raw_input()
    if url in record:
        cache.remove(url)
        print "Cache"
    elif size >= M:
        record.remove(cache.pop())
        record.add(url)
        print "Internet"
    else:
        size += 1
        record.add(url)
        print "Internet"
    cache.insert(0, url)
    N -= 1