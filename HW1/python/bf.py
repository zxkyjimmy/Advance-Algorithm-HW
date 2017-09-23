import sys
import re
def main():
    if len(sys.argv) != 2:
        print("Usage:", "python", sys.argv[0], "[input file]")
        return
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
    print("Total", len(words), "words")
    print("entropy:", entropy)
    
if __name__ == "__main__":
    main()