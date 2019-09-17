#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Section {
    int value;
    double tolls[26];
} sect;

void Invalid(void);
sect * createNode(int);
void Input(void);
void findDistance(sect **, size_t, int, int);
size_t lower_bound(sect **, size_t, int);

int main() {
    Input();
    return 0;
}

void Invalid(void) {
    puts("Invalid input.");
    exit(0);
}

sect * createNode(int data) {
    sect * tmp = (sect *) malloc(sizeof(sect));
    tmp->value = data;
    for(int i = 0; i < 26; i++)
        tmp->tolls[i] = 0;
    return tmp;
}

void Input(void) {
    size_t size = 100, counter = 0;
    char c1, c2, c3, c4, c5, c6;
    int val, res, first, second;
    double toll, parent[26];
    sect ** array = (sect **) malloc(size * sizeof(sect *));
    for(int i = 0; i < 26; i++)
        parent[i] = 0;

    puts("Toll:");
    if(scanf(" %c",&c1) != 1 || c1 != '{') Invalid();
    while(1) {
        if(scanf(" %c",&c2) != 1 || (c2 != '[' && c2 != '}')) Invalid();
        if(c2 == '}' && counter == 0) Invalid();
        if(scanf(" %d %c",&val, &c3) != 2 || val <= 0 || c3 != ':') Invalid();
        if(counter > 0)
            val += array[counter - 1]->value;
        if(counter == size)
            array = (sect **) realloc(array, (size *= 2) * sizeof(sect *));
        array[counter] = createNode(val);
        for(int j = 0; j < 26; j++)
            array[counter]->tolls[j] = parent[j];
        counter++;
        while(1) {
            if(scanf(" %c",&c3) != 1 || (c3 != ']' && (c3 < 65 || c3 > 90))) Invalid();
            if(c3 == ']') break;
            if(scanf(" %c %lf",&c4, &toll) != 2 || c4 != '=' || toll < 0) Invalid();
            if(scanf(" %c",&c5) != 1 || (c5 != ',' && c5 != ']')) Invalid();
            array[counter - 1]->tolls[(int)c3 - 65] = toll;
            parent[(int)c3 - 65] = toll;
            if(c5 == ']') break;
        }
        if(scanf(" %c",&c6) != 1 || (c6 != ',' && c6 != '}')) Invalid();
        if(c6 == '}') break;
    }
    puts("Search:");
    while((res = scanf(" %d %d",&first, &second)) != EOF) {
        if(res != 2 || first == second || first < 0 || second < 0 || first > array[counter - 1]->value || second > array[counter - 1]->value) Invalid();
        findDistance(array, counter, first, second);
        puts("");
    }
    for(size_t k = 0; k < counter; k++)
        free(array[k]);
    free(array);
}

void findDistance(sect ** array, size_t counter, int first, int second) {
    int min, max, i, count = 0;
    size_t upperMin, upperMax, current;
    double output[26];
    for(i = 0; i < 26; i++)
        output[i] = 0;
    if(first < second) {
        min = first;
        max = second;
    } else {
        min = second;
        max = first;
    }
    printf("%d - %d:",first, second);
    upperMin = lower_bound(array, counter, min);
    upperMax = lower_bound(array, counter, max);
    if(upperMin == upperMax) {
        for(i = 0; i < 26; i++) {
            if((*(array + upperMin))->tolls[i] != 0) {
                if(count == 0)
                    printf(" %c=%f",(char)(i + 65), (max - min) * (*(array + upperMin))->tolls[i]);
                else printf(", %c=%f",(char)(i + 65), (max - min) * (*(array + upperMin))->tolls[i]);
                count = 1;
            }
        }
    } else {
        current = upperMin + 1;
        for(i = 0; i < 26; i++) {
            if((*(array + upperMin))->tolls[i] != 0)
                output[i] += ((*(array + upperMin))->value - min) * (*(array + upperMin))->tolls[i];
        }
        while(current < upperMax) {
            for(i = 0; i < 26; i++) {
                if((*(array + current))->tolls[i] != 0)
                    output[i] += ((*(array + current))->value - (*(array + current - 1))->value) * (*(array + current))->tolls[i];
            }
            current++;
        }
        for(i = 0; i < 26; i++) {
            if((*(array + upperMax))->tolls[i] != 0)
                output[i] += (max - (*(array + upperMax - 1))->value) * (*(array + upperMax))->tolls[i];
        }
        // output
        for(i = 0; i < 26; i++) {
            if(output[i] != 0) {
                if(count == 0)
                    printf(" %c=%f",(char)(i + 65), output[i]);
                else printf(", %c=%f",(char)(i + 65), output[i]);
                count = 1;
            }
        }
    }
}

size_t lower_bound(sect ** array, size_t counter, int data) {
    int l = 0, h = (int)counter, mid;
    while (l < h) {
        mid = (l + h) / 2;
        if(data <= (*(array + mid))->value) h = mid;
        else l = mid + 1;
    }
    return (size_t)l;
}