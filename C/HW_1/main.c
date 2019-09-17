#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double minimum(double a, double b) {
    return a < b ? a : b;
}

char c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13;
double A1, B1, C1, A2, B2, C2, x1, max1, mid1, min1, max2, mid2, min2, Circumference1, Circumference2;
double Triangle1[3][2];
double Triangle2[3][2];
double epsilon = 1e-12;
int flag1 = 0, flag2 = 0, flagIdentical = 0;

void Invalid(void) {
    puts("Invalid input.");
    exit(0);
}

void TriangleDoesNotExist(void) {
    puts("Invalid triangle.");
    exit(0);
}

void Input(void) {

    puts("Triangle #1:");

    if(scanf(" %c",&c1) != 1 || c1 != '{') Invalid();

    if(scanf(" %lf",&x1) == 1) { // take lengths' of sides
        A1 = x1;
        if(scanf(" %c %lf %c %lf %c",&c2,&B1,&c3,&C1,&c4) != 5 || c2 != ',' || c3 != ',' || c4 != '}') Invalid();
    } else { // take coordinates
        flag1 = 1;
        for(int i = 0; i < 3; i++) {
            if(scanf(" %c %lf %c %lf %c",&c2,&Triangle1[i][0],&c3,&Triangle1[i][1],&c4) != 5 || c2 != '[' || c3 != ';' || c4 != ']') Invalid();
            if(i != 2 && (scanf(" %c",&c5) != 1 || c5 != ',')) Invalid();
        }
        if(scanf(" %c",&c6) != 1 || c6 != '}') Invalid();
    }

    if(flag1) {
        A1 = sqrt((Triangle1[1][0] - Triangle1[0][0])*(Triangle1[1][0] - Triangle1[0][0]) + (Triangle1[1][1] - Triangle1[0][1])*(Triangle1[1][1] - Triangle1[0][1]));
        B1 = sqrt((Triangle1[2][0] - Triangle1[1][0])*(Triangle1[2][0] - Triangle1[1][0]) + (Triangle1[2][1] - Triangle1[1][1])*(Triangle1[2][1] - Triangle1[1][1]));
        C1 = sqrt((Triangle1[2][0] - Triangle1[0][0])*(Triangle1[2][0] - Triangle1[0][0]) + (Triangle1[2][1] - Triangle1[0][1])*(Triangle1[2][1] - Triangle1[0][1]));
    }
    if(A1 + B1 - C1 <= epsilon * C1) TriangleDoesNotExist();
    if(A1 + C1 - B1 <= epsilon * B1) TriangleDoesNotExist();
    if(B1 + C1 - A1 <= epsilon * A1) TriangleDoesNotExist();

    puts("Triangle #2:");

    if(scanf(" %c",&c1) != 1 || c1 != '{') Invalid();

    if(scanf(" %lf",&x1) == 1) { // take lengths' of sides
        A2 = x1;
        if(scanf(" %c %lf %c %lf %c",&c2,&B2,&c3,&C2,&c4) != 5 || c2 != ',' || c3 != ',' || c4 != '}') Invalid();
    } else { // take coordinates
        flag2 = 1;
        for(int i = 0; i < 3; i++) {
            if(scanf(" %c %lf %c %lf %c",&c2,&Triangle2[i][0],&c3,&Triangle2[i][1],&c4) != 5 || c2 != '[' || c3 != ';' || c4 != ']') Invalid();
            if(i != 2)
                if(scanf(" %c",&c5) != 1 || c5 != ',') Invalid();
        }
        if(scanf(" %c",&c6) != 1 || c6 != '}') Invalid();
    }
    if(flag2) {
        A2 = sqrt((Triangle2[1][0] - Triangle2[0][0])*(Triangle2[1][0] - Triangle2[0][0]) + (Triangle2[1][1] - Triangle2[0][1])*(Triangle2[1][1] - Triangle2[0][1]));
        B2 = sqrt((Triangle2[2][0] - Triangle2[1][0])*(Triangle2[2][0] - Triangle2[1][0]) + (Triangle2[2][1] - Triangle2[1][1])*(Triangle2[2][1] - Triangle2[1][1]));
        C2 = sqrt((Triangle2[2][0] - Triangle2[0][0])*(Triangle2[2][0] - Triangle2[0][0]) + (Triangle2[2][1] - Triangle2[0][1])*(Triangle2[2][1] - Triangle2[0][1]));
    }
    if(A2 + B2 - C2 <= epsilon * C2) TriangleDoesNotExist();
    if(A2 + C2 - B2 <= epsilon * B2) TriangleDoesNotExist();
    if(B2 + C2 - A2 <= epsilon * A2) TriangleDoesNotExist();
}


int main(void) {

    Input();

    // find the max, mid, and min for the first triangle
    if(A1 >= B1 && A1 >= C1) {
        max1 = A1;
        if(B1 >= C1) {
            mid1 = B1;
            min1 = C1;
        } else {
            mid1 = C1;
            min1 = B1;
        }
    } else if(B1 >= A1 && B1 >= C1) {
        max1 = B1;
        if(A1 >= C1) {
            mid1 = A1;
            min1 = C1;
        } else {
            mid1 = C1;
            min1 = A1;
        }
    } else {
        max1 = C1;
        if(A1 >= B1) {
            mid1 = A1;
            min1 = B1;
        } else {
            mid1 = B1;
            min1 = A1;
        }
    }


    // find max, mid, and min for the second triangle
    if(A2 >= B2 && A2 >= C2) {
        max2 = A2;
        if(B2 >= C2) {
            mid2 = B2;
            min2 = C2;
        } else {
            mid2 = C2;
            min2 = B2;
        }
    } else if(B2 >= A2 && B2 >= C2) {
        max2 = B2;
        if(A1 >= C2) {
            mid2 = A2;
            min2 = C2;
        } else {
            mid2 = C2;
            min2 = A2;
        }
    } else {
        max2 = C2;
        if(A2 >= B2) {
            mid2 = A2;
            min2 = B2;
        } else {
            mid2 = B2;
            min2 = A2;
        }
    }

    if(fabs(max1 / max2 - mid1 / mid2) < epsilon * minimum(max1 / max2,mid1 / mid2))
        if(fabs(mid1 / mid2 - min1 / min2) < epsilon * minimum(mid1 / mid2,min1 / min2) && fabs(max1 / max2 - min1 / min2) < epsilon * minimum(max1 / max2,min1 / min2)) flagIdentical = 1;

    Circumference1 = A1 + B1 + C1;
    Circumference2 = A2 + B2 + C2;

    if(flagIdentical)
        puts("The triangles are identical.");
    else {
        if(fabs(Circumference1 - Circumference2) < epsilon * minimum(Circumference1,Circumference2))
            puts("The triangles are not identical, however, they have the same circumference.");
        else {
            if(Circumference1 > Circumference2)
                puts("Triangle #1 has a longer circumference.");
            else puts("Triangle #2 has a longer circumference.");
        }
    }

    return 0;
}