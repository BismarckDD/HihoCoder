file1 = open("query_output.txt")
dic = {}
try:
    for line in file1:
        line = line.strip()
        words = line.split(' ')
        if words[0] != "DocId" and words[0] != "Rank":
            continue
        if words[0] == "DocId":
            DocId = words[1]
        else:
            Rank = words[1]
            dic[DocId] = Rank
finally:
    file1.close()

file2 = open("query_analyse.txt", "w")
try:
    for (key, value) in dic.items():
        file2.write(key + " " + value)
finally:
    file2.close()

