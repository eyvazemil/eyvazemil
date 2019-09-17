#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void Invalid(void);
void Input(void);
void DigitsZeros(int);
void Sequence(void);
void go_on(void);
void Digits(void);

char c, c1, c3, c4, c5, c6, what;
int base;
long long start, end;

int main() {
    Input();
    return 0;
}

void Invalid(void) {
    puts("Invalid input.");
    exit(0);
}

void go_on(void) {
    if(what == 'l') Digits(); //DigitsZeros(0);
    else if(what == 'z') DigitsZeros(1);
    else Sequence();
}

void Input(void) {
    puts("Enter the intervals:");
    while(scanf(" %c",&c) != EOF) {
        base = 10;
        c1 = c;
        if(c1 != 'r' && c1 != '<') Invalid();
        if(c1 == 'r') {
            if(scanf(" %d %c %c %lld %c %lld %c", &base, &c3, &c4, &start, &c5, &end, &c6) != 7 || base < 2 || base > 36 || c3 != ':' || c4 != '<' || c5 != ';' || c6 != '>' || start < 0 || end < 0 || start > end) Invalid();
        } else {
            if(scanf(" %lld %c %lld %c", &start, &c5, &end, &c6) != 4 || c5 != ';' || c6 != '>' || start < 0 || end < 0 || start > end) Invalid();
        }
        if(scanf(" %c", &what) != 1 || (what != 'l' && what != 'z' && what != 's')) Invalid();
        // call function go_on
        go_on();
    }
}

void DigitsZeros(int flag) {
    int count = 0;
    long long j;
    if(start == 0) count++;
    for(long long i = start; i <= end; i++) {
        j = i;
        while(j) {
            if(!flag) count++;
            else if(j % base == 0) count++;
            j /= base;
        }
    }
    if(!flag) printf("Digits: %d\n",count);
    else printf("Zeros: %d\n",count);
}

void Sequence(void) {
    int tmp = 0, max = 0;
    long long j;
    if(start == 0) max++;
    for(long long i = start; i <= end; i++) {
        //tmp = 0;
        j = i;
        while(j) {
            if(j % base == 0) tmp++;
            else {
                if(tmp > max) max = tmp;
                tmp = 0;
            }
            j /= base;
        }
    }
    printf("Sequence: %d\n",max);
}

void Digits(void) {
    int digits = 1;
    long long final = 0, interval_lower2 = 1, interval_upper, interval_lower1 = 1;
    while(interval_lower1 * base <= start) {
        interval_lower1 *= base;
        digits++;
    }
    interval_upper = interval_lower1 * base;
    while(interval_lower2 * base <= end) interval_lower2 *= base;
    if(interval_lower1 == interval_lower2) printf("Digits: %lld\n",(end - start + 1) * digits);
    else {
        final += (interval_upper - start) * digits;
        digits++;
        while(interval_upper < interval_lower2) {
            final += (interval_upper * base - interval_upper) * digits;
            interval_upper *= base;
            digits++;
        }
        final += (end - interval_upper + 1) * digits;
        printf("Digits: %lld\n",final);
    }
}