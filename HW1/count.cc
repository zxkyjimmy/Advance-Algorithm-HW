#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;
char *content;
bool func(int i, int j) {
    return strcmp(content+i, content+j) < 0;
}
class Item {
    int index;
    int num = 0;
};
int main(int argc, char **argv) {
    time_t start, stop;
    int length;
    int *labels;
    int count = 0;
    bool previous_is_word = false;
    FILE *f;
    if (argc != 2) {
        cout << "Usage : " << argv[0] << " filename" << endl;
        return 1;
    }
    f = fopen(argv[1], "rb");
    if (f == NULL) {
        cout << argv[1] << " can not be opened!" << endl;
        return 1;
    }
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    content = (char *)malloc(length);
    labels = (int *)malloc(length*sizeof(int));
    start = clock();
    fread(content, 1, length, f);
    for (int i = 0; i < length; i++) {
        content[i] |= 32;
        if (content[i] < 'a' || 'z' < content[i]) {
            if (previous_is_word) {
                content[i] = '\0';
                previous_is_word = false;
            }
        } else {
            if (!previous_is_word) {
                labels[count] = i;
                count += 1;
                previous_is_word = true;
            }
        }
    }
    sort(labels, labels+count, func);
    stop = clock();
    cout << "words: " << count << endl;
    cout << "time : " << double(stop-start)*1000/CLOCKS_PER_SEC << " ms."<< endl;
    free(content);
    free(labels);
    fclose(f);
    return 0;
}