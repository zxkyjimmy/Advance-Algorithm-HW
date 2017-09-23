import sys
import re
import time
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
    entropy = 0
    for i, lword in enumerate(words):
        for j, rword in enumerate(words[i+1:]):
            if lword > rword:
                entropy += 1
    stopclock = time.clock()
    print("Total", len(words), "words")
    print("Entropy:", entropy)
    print("Time:", stopclock-startclock)
if __name__ == "__main__":
    main()