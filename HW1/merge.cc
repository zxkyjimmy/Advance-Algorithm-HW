#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(int argc, char** argv) {
    time_t start, stop;
    int length;
    char *content;
    FILE *f;
    if (argc != 2) {
        cout << "Usage : " << argv[0] << " filename" << endl;
        return 1;
    }
    f = fopen(argv[1], "r");
    if (f == NULL) {
        cout << argv[1] << " can not be opened!" << endl;
        return 1;
    }
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    content = (char *)malloc(length);
    start = clock();
    fread(content, 1, length, f);
    stop = clock();
    cout << double(stop-start)*1000/CLOCKS_PER_SEC << " ms."<< endl;
    free(content);
    fclose(f);
    return 0;
}