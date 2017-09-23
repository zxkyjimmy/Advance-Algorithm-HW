import sys
import re
import time
entropy = 0
def merge_sort(x):
    global entropy
    result = []
    if len(x) < 2:
        return x
    mid = int(len(x) / 2)
    y = merge_sort(x[:mid])
    z = merge_sort(x[mid:])
    i = 0
    j = 0
    while i < len(y) and j < len(z):
        if y[i] > z[j]:
            result.append(z[j])
            j += 1
            entropy += len(y)-i
        else:
            result.append(y[i])
            i += 1
    result += y[i:]
    result += z[j:]
    return result
def main():
    if len(sys.argv) != 2:
        print("Usage:", "python", sys.argv[0], "[input file]")
        return
    startclock = time.clock()
    f = open(sys.argv[1], 'r')
    s = f.read()
    f.close()
    result = re.findall(r'[a-zA-Z]+', s)
    words = [x.lower() for x in result]
    sort_words = merge_sort(words)
    stopclock = time.clock()
    print("Total", len(words), "words")
    print("Entropy:", entropy)
    print("Time:", stopclock-startclock)
if __name__ == "__main__":
    main()