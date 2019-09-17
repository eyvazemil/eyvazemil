#include <stdio.h>
#include <stdlib.h>

typedef struct Letter {
    char character;
    char visited;
} letter;

void Invalid(letter *);
void Input(void);
void Process(letter *, char *, int, int, int);

int main(void) {
    Input();
    return 0;
}

void Invalid(letter * puzzle) {
    puts("Invalid input.");
    free(puzzle);
    exit(0);
}

void Input(void) {
    int width = 0, height = 0, prev_width = 0, counter_puzzle = 50, final = 0;
    char c, c1, prev = 'a';
    letter * puzzle = (letter *) malloc(counter_puzzle * sizeof(letter));

    puts("Enter your wordfind puzzle:");
    while(1) { // input puzzle
        if(scanf("%c",&c) != 1 || (c != '.' && c != '\n' && (c < 97 || c > 122))) Invalid(puzzle); // no valid characters inputted
        if(c == '\n' && width == 0 && height == 0) Invalid(puzzle); // if only empty line was inputted
        if(c == '\n' && prev == '\n') break; // if the empty line comes
        if(c == '\n') {
            if(height > 0 && width != prev_width) Invalid(puzzle); // if the rectangle shape isn't preserved or there is no empty line
            prev_width = width;
            width = 0;
            prev = c;
            height++;
            continue;
        }
        if(height * prev_width + width == counter_puzzle)
            puzzle = (letter *) realloc(puzzle, (counter_puzzle *= 2) * sizeof(letter));
        puzzle[height * prev_width + width].character = c;
        puzzle[height * prev_width + width].visited = 0; // stands for not visited
        width++;
        prev = c;
    }

    //printf("height: %d, width: %d\n",height, prev_width);

    /*for(int y = 0; y < height; y++) {
        for(int u = 0; u < prev_width; u++)
            if(puzzle[y * prev_width + u].visited == 0)
                printf("%c",puzzle[y * prev_width + u].character);
        puts("");
    }*/

    while(1) { // take words
        int size = 50, counter = 0, res;
        char * word = (char *) malloc(size * sizeof(char));
        while((res = scanf("%c",&c1)) != EOF) {
            if(c1 == '\n') break;
            if(counter == size)
                word = (char *) realloc(word, (size *= 2) * sizeof(char));
            word[counter] = c1;
            counter++;
        }
        if(counter > 0)
            Process(puzzle, word, counter, prev_width, height);
        free(word);
        if(res == EOF) break;
    }
    printf("Result:");
    for(int l = 0; l < height; l++) {
        for(int m = 0; m < prev_width; m++) {
            if(puzzle[l * prev_width + m].visited == 0 && puzzle[l * prev_width + m].character != '.') {
                if(final % 60 == 0) puts("");
                printf("%c", puzzle[l * prev_width + m].character);
                final++;
            }
        }
    }
    puts("");
    free(puzzle);
}

void Process(letter * array, char * word, int counter, int width, int height) {
    int k, count = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            for(k = 0; k < counter; k++) { // 1
                if(j + k >= width) goto ON1;
                if(array[i * width + j + k].character != word[k]) goto ON1;
            }
            for(k = 0; k < counter; k++) {
                array[i * width + j + k].visited = 1;
                //printf("i: %d, j + k: %d\n",i, j + k);
                count = 1;
            }
            ON1:
            for(k = 0; k < counter; k++) { // 2
                if(j - k < 0) goto ON2;
                if(array[i * width + j - k].character != word[k]) goto ON2;
            }
            for(k = 0; k < counter; k++) {
                array[i * width + j - k].visited = 1;
                //printf("i: %d, j - k: %d\n",i, j - k);
                count = 1;
            }
            ON2:
            for(k = 0; k < counter; k++) { // 3
                if(i + k >= height) goto ON3;
                if(array[(i + k) * width + j].character != word[k]) goto ON3;
            }
            for(k = 0; k < counter; k++) {
                array[(i + k) * width + j].visited = 1;
                //printf("i + k: %d, j: %d\n",i + k, j);
                count = 1;
            }
            ON3:
            for(k = 0; k < counter; k++) { // 4
                if(i - k < 0) goto ON4;
                if(array[(i - k) * width + j].character != word[k]) goto ON4;
            }
            for(k = 0; k < counter; k++) {
                array[(i - k) * width + j].visited = 1;
                //printf("i - k: %d, j: %d\n",i - k, j);
                count = 1;
            }
            ON4:
            for(k = 0; k < counter; k++) { // 5
                if(i - k < 0 || j - k < 0) goto ON5;
                if(array[(i - k) * width + j - k].character != word[k]) goto ON5;
            }
            for(k = 0; k < counter; k++) {
                array[(i - k) * width + j - k].visited = 1;
                //printf("i - k: %d, j - k: %d\n",i - k, j - k);
                count = 1;
            }
            ON5:
            for(k = 0; k < counter; k++) { // 6
                if(i - k < 0 || j + k >= width) goto ON6;
                if(array[(i - k) * width + j + k].character != word[k]) goto ON6;
            }
            for(k = 0; k < counter; k++) {
                array[(i - k) * width + j + k].visited = 1;
                //printf("i - k: %d, j + k: %d\n",i - k, j + k);
                count = 1;
            }
            ON6:
            for(k = 0; k < counter; k++) { // 7
                if(i + k >= height || j - k < 0) goto ON7;
                if(array[(i + k) * width + j - k].character != word[k]) goto ON7;
            }
            for(k = 0; k < counter; k++) {
                array[(i + k) * width + j - k].visited = 1;
                //printf("i + k: %d, j - k: %d\n",i + k, j - k);
                count = 1;
            }
            ON7:
            for(k = 0; k < counter; k++) { // 8
                if(i + k >= height || j + k >= width) goto ON8;
                if(array[(i + k) * width + j + k].character != word[k]) goto ON8;
            }
            for(k = 0; k < counter; k++) {
                array[(i + k) * width + j + k].visited = 1;
                //printf("i + k: %d, j + k: %d\n",i + k, j + k);
                count = 1;
            }
            ON8:
            continue;
        }
    }
    if(count == 0) {
        printf("Word '");
        for(int h = 0; h < counter; h++)
            printf("%c",word[h]);
        puts("' not found.");
        free(array);
        exit(0);
    }
}