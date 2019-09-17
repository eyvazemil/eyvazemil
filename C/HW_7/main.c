#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Invalid(char *);
void Input(void);
int recursion_helper(char *, int *, int, int, int, int, int, int);
int recursion(char *, int, int, int);
int janitor(char *, int, int, int, int);
int decimalToRoman(char *, int);
int convert_to_integer(char);

int answer;

int main() {
    Input();
    return 0;
}

void Invalid(char * string) {
    puts("Invalid input.");
    free(string);
    exit(0);
}

void Input(void) {
    int size = 50, counter = 0, number = 0, flagList;
    char * string, c;
    string = (char *) malloc(size * sizeof(char));

    puts("Sequence:");
    while(1) {
        if(scanf("%c",&c) != 1 || (c != 'I' && c != 'V' && c != 'X' && c != 'L' && c != 'C' && c != 'D' && c != 'M' && c != '\n')) Invalid(string);
        if(c == '\n') {
            if(counter == 0) Invalid(string);
            break;
        }
        if(counter == size - 1)
            string = (char *) realloc(string, (size *= 2) * sizeof(char));
        string[counter] = c;
        counter++;
    }

    puts("Operations:");
    while(1) {
        flagList = 0;
        int res;
        char str[6], c1, c2, newline;
        res = scanf("%5[^\n]",str);
        if(res == EOF) break;

        if(strncmp(str, "list", 4) == 0) {
            flagList = 1;
            if(str[4] != ' ') Invalid(string);
            if(scanf("%c",&c1) != 1) Invalid(string);
            if(isdigit(c1) == 0) Invalid(string);
            else ungetc(c1, stdin);
            if(scanf("%d",&number) != 1 || number <= 0) Invalid(string);
        } else if(strncmp(str, "count", 5) == 0) {
            if(scanf("%c",&c1) != 1 || c1 != ' ') Invalid(string);
            if(scanf("%c",&c2) != 1) Invalid(string);
            if(isdigit(c2) == 0) Invalid(string);
            else ungetc(c2, stdin);
            if(scanf("%d",&number) != 1 || number <= 0) Invalid(string);
        } else Invalid(string);
        scanf("%c",&newline);
        answer = 0;
        recursion(string, counter, number, flagList);
        printf("%d: %d\n",number, answer);
    }
    free(string);
}

int recursion(char * string, int counter, int number, int flagList) {
    int * array = (int *) malloc(counter * sizeof(int));
    int ret = recursion_helper(string, array, counter, 0, 1, 0, number, flagList);
    free(array);
    return ret;
}

int recursion_helper(char * string, int * array, int size, int count, int id, int sum, int number, int flagList) {
    if(id == size + 1) {
        if(sum == number) {
            answer++;
            if(flagList) {
                int k;
                printf("> %d = ",number);
                for(k = 0; k < array[0]; k++)
                    printf("%c",string[k]);
                if(count != 1) printf("+");
                for(k = 1; k < count; k++) {
                    for(int j = array[k - 1]; j < array[k]; j++)
                        printf("%c",string[j]);
                    if(k != count - 1) printf("+");
                }
                puts("");
            }
            return 1;
        }
    }
    int ret = 0, start = id - 1, tmp;
    for(; id <= size; id++) {
        tmp = janitor(string, sum, number, start, id);
        if(tmp == 0) return 0;
        array[count] = id;
        ret += recursion_helper(string, array, size, count + 1, id + 1, sum + tmp, number, flagList);
    }
    return ret;
}

int janitor(char * string, int sum, int number, int start, int end) {
    int tmp_sum = 0, counter = 0, current, next;
    char * str1 = (char *) malloc((end - start + 1) * sizeof(char));
    for(int i = start; i < end; i++) {
        current = convert_to_integer(string[i]);
        str1[counter] = string[i];
        counter++;
        if(i + 1 < end && convert_to_integer(string[i]) < convert_to_integer(string[i + 1]) && string[i] != 'V' && string[i] != 'L' && string[i] != 'D') {
            next = convert_to_integer(string[i + 1]);
            current = next - current;
            str1[counter] = string[i + 1];
            counter++;
            i++;
        }
        tmp_sum += current;
    }
    if(decimalToRoman(str1, tmp_sum) == 0) {
        free(str1);
        return 0;
    }
    if(tmp_sum + sum > number) {
        free(str1);
        return 0; // if sum is more than number
    }
    free(str1);
    return tmp_sum;
}

int decimalToRoman(char * string, int num) {
    int decimal[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char ** symbol;
    symbol = (char **) malloc(12 * sizeof(char *));
    symbol[0] = (char *) "M";
    symbol[1] = (char *) "CM";
    symbol[2] = (char *) "D";
    symbol[3] = (char *) "CD";
    symbol[4] = (char *) "C";
    symbol[5] = (char *) "XC";
    symbol[6] = (char *) "L";
    symbol[7] = (char *) "XL";
    symbol[8] = (char *) "X";
    symbol[9] = (char *) "IX";
    symbol[10] = (char *) "V";
    symbol[11] = (char *) "IV";
    symbol[12] = (char *) "I";
    char * str;
    int i = 0, count = 0, size = 1, current = 0;
    str = (char *) malloc(size * sizeof(char));

    while(num) {
        while(num/decimal[i]) {
            if(i == 0 || i == 2 || i == 4 || i == 6 || i == 8 || i == 10 || i == 12) current = 1;
            else if(i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 11) current = 2;
            count += current;
            if(count >= size - 1)
                str = (char *) realloc(str, (size *= 2) * sizeof(char));
            if(current == 1)
                str[count - 1] = *(symbol[i]);
            else {
                str[count - 2] = *(symbol[i]);
                str[count - 1] = *(symbol[i] + 1);
            }
            num -= decimal[i];
        }
        i++;
    }
    if(strncmp(str, string, (size_t) count) == 0) {
        free(str);
        return 1;
    } else {
        free(str);
        return 0;
    }
}

int convert_to_integer(char c) {
    int current;
    if(c == 'I') current = 1;
    else if(c == 'V') current = 5;
    else if(c == 'X') current = 10;
    else if(c == 'L') current = 50;
    else if(c == 'C') current = 100;
    else if(c == 'D') current = 500;
    else current = 1000;
    return current;
}
