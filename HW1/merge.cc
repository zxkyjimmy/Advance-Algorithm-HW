#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;
char *content;
uint64_t entropy = 0;
void merge_sort(int arr[], int len) {
	int* a = arr;
	int* b = (int*) malloc(len * sizeof(int));
	int seg, start;
	for (seg = 1; seg < len; seg += seg) {
		for (start = 0; start < len; start += seg + seg) {
			int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2) {
                if (strcmp(content+a[start1], content+a[start2]) > 0) {
                    b[k++] = a[start2++];
                    entropy += end1 - start1;
                } else {
                    b[k++] = a[start1++];
                }
            }
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		int* temp = a;
		a = b;
		b = temp;
	}
	if (a != arr) {
		b = a;
	}
	free(b);
}
int main(int argc, char** argv) {
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
    merge_sort(labels, count);
    stop = clock();
    cout << count << endl;
    cout << entropy << endl;
    cout << double(stop-start)*1000/CLOCKS_PER_SEC << " ms."<< endl;
    free(content);
    free(labels);
    fclose(f);
    return 0;
}