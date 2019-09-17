#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000000

void Invalid(void);
void Input(void);
void FindDistance(int **, int, int, size_t);
int compare(const void *, const void *);
size_t lower_bound(int **, size_t, int);

int main(void) {
    Input();
    return 0;
}

void Invalid(void) {
    puts("Invalid input.");
    exit(0);
}

void Input(void) {
    int * array;
    int * masterArray;
    array = (int *) malloc(MAX * sizeof(int));
    char c1, c2;
    int value, cnt, res, len;
    size_t counter = 0;
    puts("Suitable positions:");
    if(scanf(" %d %c",&len, &c1) != 2 || len <= 0 || c1 != ':') Invalid();
    if(scanf(" %c",&c1) != 1 || c1 != '{') Invalid();
    while(1) {
        if(scanf(" %d %c", &value, &c2) != 2 || value < 1 || value > len - 1 || (c2 != ',' && c2 != '}')) Invalid();
        if(counter == MAX) Invalid(); // if there are more than 1000000 elements inputted
        array[counter] = value;
        counter++;
        if(c2 == '}') break;
    }
    if(counter == 0) Invalid();
    masterArray = (int *) malloc(counter * sizeof(int));
    for(size_t h = 0; h < counter; h++)
        masterArray[h] = array[h];
    free(array);
    qsort(masterArray,counter,sizeof(int),compare);
    puts("Distances:");
    while(1) {
        if((res = scanf(" %d",&cnt)) != 1 || cnt < 0) {
            if(res == EOF) break;
            else Invalid();
        }
        FindDistance(&masterArray, cnt, len, counter);
    }
    free(masterArray);
}

void FindDistance(int ** masterArray, int interval, int len, size_t counter) {
    int answer = 0, previous = 0, value;
    size_t prev = 0, val;
    if(interval > len) puts("Billboards: 0");
    else if(interval < (*masterArray)[0]) puts("N/A");
    else {
        for(value = interval; value < len; value = (*masterArray)[prev] + interval) {
            if(value > (*masterArray)[counter - 1]) {
                if((*masterArray)[counter - 1] + interval < len) {
                    puts("N/A");
                    return;
                }
                answer++;
                break;
            }
            if(previous > 0 && value < (*masterArray)[prev + 1]) {
                puts("N/A");
                return;
            }
            /*for(size_t j = prev; j < counter; j++) {
                if((*masterArray)[j] > value) {
                    prev = j - 1;
                    previous = 1;
                    answer++;
                    break;
                }
                if((*masterArray)[j] == value) {
                    prev = j;
                    previous = 1;
                    answer++;
                    break;
                }
            }*/
            val = lower_bound(masterArray, counter, value);
            if((*masterArray)[val] == value) prev = val;
            else prev = val - 1;
            previous = 1;
            answer++;
        }
        printf("Billboards: %d\n",answer);
    }
}

int compare(const void * a, const void * b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

size_t lower_bound(int ** array, size_t counter, int data) {
    int l = 0, h = (int)counter, mid;
    while (l < h) {
        mid = (l + h) / 2;
        if(data <= (*array)[mid]) h = mid;
        else l = mid + 1;
    }
    return (size_t)l;
}