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
public:
    int index;
    int num;
    bool operator< (const Item item) const {
        if (num == item.num) {
            return strcmp(content+index, content+item.index) < 0;
        }
        return num > item.num;
    }
};
int main(int argc, char **argv) {
    time_t start, stop;
    int length;
    int *labels;
    int count = 0;
    bool previous_is_word = false;
    FILE *f;
    Item *counter;
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
    counter = (Item *)malloc(count*sizeof(Item));
    sort(labels, labels+count, func);
    int tmpindex = length;
    int counter_size = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(content+labels[i], content+tmpindex) == 0) {
            counter[counter_size-1].num++;
        } else {
            counter[counter_size].index = labels[i];
            counter[counter_size].num = 1;
            tmpindex = labels[i];
            counter_size++;
        }
    }
    sort(counter, counter+counter_size);
    stop = clock();
    fclose(f);
    f = fopen("output.txt", "w");
    int times = 0;
    for (int i = 0; i < counter_size; i++) {
        if (counter[i].num != times) {
            if (times != 0) {
                fprintf(f, "\n");
            }
            times = counter[i].num;
            fprintf(f, "%d: ", times);
        }
        fprintf(f, "%s ", content+counter[i].index);
    }
    cout << "words: " << count << endl;
    cout << "time : " << double(stop-start)*1000/CLOCKS_PER_SEC << " ms."<< endl;
    free(content);
    free(labels);
    fclose(f);
    return 0;
}