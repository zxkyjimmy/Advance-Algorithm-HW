import sys
import re
import time
from collections import Counter
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
    count = Counter(words)
    result = sorted(count.items(), key=lambda x:(-x[1], x[0]))
    stopclock = time.clock()
    f = open('output.txt', 'w')
    times = 0
    for item in result:
        if item[1] != times:
            if times != 0:
                f.write('\n')
            times = item[1]
            f.write(str(times) + ': ')
        f.write(item[0] + ' ')
    f.close()
    print("Total", len(words), "words")
    print("Time:", stopclock-startclock)
if __name__ == "__main__":
    main()