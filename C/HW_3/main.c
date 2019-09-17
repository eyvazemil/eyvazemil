#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

unsigned long long toReturn(unsigned **, unsigned **, unsigned **, unsigned, unsigned, unsigned, unsigned long long);
void twoSides(unsigned *, unsigned *, unsigned long long *, unsigned long long, unsigned long long, unsigned long long);

unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        s3,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2,
                                                             unsigned int      * c3 )
{

    unsigned c11, c22, c33 = 0, c11final = 0, c22final = 0, c1tmp, c2tmp;
    unsigned long long answer = 0;
    unsigned long long s1andBulk = s1 + bulkhead, s2andBulk = s2 + bulkhead, s3andBulk = s3 + bulkhead;
    if(length == bulkhead)
        return toReturn(&c1,&c2,&c3,0,0,0,1);
    else if((bulkhead > length) || (s1 == 0 && s2 == 0 && s3 == 0))
        return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
    else {
        length -= bulkhead;
        // if at least one of the sides is 0
        if((s1 == 0 && s2 == 0) || (s1 == s2 && s2 == s3)) {
            if(length % s3andBulk == 0)
                return toReturn(&c1,&c2,&c3,0,0,length/s3andBulk,1);
            else return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
        } else if(s1 == 0 && s3 == 0) {
            if(length % s2andBulk == 0)
                return toReturn(&c1,&c2,&c3,0,length/s2andBulk,0,1);
            else return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
        } else if(s2 == 0 && s3 == 0) {
            if(length % s1andBulk == 0)
                return toReturn(&c1,&c2,&c3,length/s1andBulk,0,0,1);
            else return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
        } else if(s1 == 0) {
            if(s2 == s3) {
                if(length % s3andBulk == 0)
                    return toReturn(&c1,&c2,&c3,0,0,length/s3andBulk,1);
                else return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
            } else {
                twoSides(&c1tmp,&c2tmp,&answer,length,s2andBulk,s3andBulk);
                if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
                else return toReturn(&c1,&c2,&c3,0,c1tmp,c2tmp,answer);
            }
        } else if(s2 == 0) {
            if(s1 == s3) {
                if(length % s3andBulk == 0)
                    return toReturn(&c1,&c2,&c3,0,0,length/s3andBulk,1);
                else return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
            } else {
                twoSides(&c1tmp,&c2tmp,&answer,length,s1andBulk,s3andBulk);
                if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
                else return toReturn(&c1,&c2,&c3,c1tmp,0,c2tmp,answer);
            }
        } else if(s3 == 0) {
            if(s1 == s2) {
                if(length % s1andBulk == 0)
                    return toReturn(&c1,&c2,&c3,length/s1andBulk,0,0,1);
                else return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,0);
            } else {
                twoSides(&c1tmp,&c2tmp,&answer,length,s1andBulk,s2andBulk);
                if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
                else return toReturn(&c1,&c2,&c3,c1tmp,c2tmp,0,answer);
            }
        } else {
            // if none of the sides is 0
            if(s1 == s2) {
                twoSides(&c1tmp,&c2tmp,&answer,length,s1andBulk,s3andBulk);
                if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
                else return toReturn(&c1,&c2,&c3,c1tmp,0,c2tmp,answer);
            } else if(s2 == s3) {
                twoSides(&c1tmp,&c2tmp,&answer,length,s1andBulk,s3andBulk);
                if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
                else return toReturn(&c1,&c2,&c3,c1tmp,0,c2tmp,answer);
            } else if(s1 == s3) {
                twoSides(&c1tmp,&c2tmp,&answer,length,s1andBulk,s2andBulk);
                if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
                else return toReturn(&c1,&c2,&c3,c1tmp,c2tmp,0,answer);
            } else {
                // if none of the sides is zero and no two sides are equal
                unsigned constant1, constant2, c11prev, c33prev;
                for(constant1 = 0; constant1 * s1andBulk <= length; constant1++) {
                    unsigned long long tmp1 = length - s1andBulk * constant1;
                    c11 = constant1;
                    for(constant2 = 0; constant2 * s2andBulk <= tmp1; constant2++) {
                        unsigned long long tmp = tmp1 - s2andBulk * constant2;
                        c22 = constant2;
                        if(tmp % s3andBulk == 0) {
                            c11final = c11;
                            c22final = c22;
                            c33 = tmp / s3andBulk;
                            if(answer != 0)
                                if(c11prev == c33 && c33prev == c11) goto on;
                            c11prev = c11;
                            c33prev = c33;
                            answer++;
                        }
                    }
                }
            }
        }
    }
    on:
    if(answer == 0) return toReturn(&c1,&c2,&c3,*c1,*c2,*c3,answer);
    else return toReturn(&c1,&c2,&c3,c11final,c22final,c33,answer);
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    unsigned int c1, c2, c3;
    /*unsigned long long tmp = hyperloop ( 15918, 32, 152, 109, 2, &c1, &c2, &c3 );
    printf("%llu\n",tmp);
    printf("c1: %u, c2: %u, c3: %u\n",c1,c2,c3);
    printf("%u\n",12 * c1 + 8 * c2 + 10 * c3 + 3 * ( c1 + c2 + c3 + 1 ));*/
    assert ( hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 ) == 42
             && 4 * c1 + 7 * c2 + 5 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 100 );
    assert ( hyperloop ( 12345, 8, 3, 11, 3, &c1, &c2, &c3 ) == 82708
             && 8 * c1 + 3 * c2 + 11 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 12345 );
    c1 = 8;
    c2 = 9;
    c3 = 10;
    assert ( hyperloop ( 127, 12, 8, 10, 0, &c1, &c2, &c3 ) == 0
             && c1 == 8
             && c2 == 9
             && c3 == 10 );
    assert ( hyperloop ( 127, 12, 8, 10, 3, &c1, &c2, &c3 ) == 4
             && 12 * c1 + 8 * c2 + 10 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 127 );
    assert ( hyperloop ( 100, 35, 0, 0, 10, &c1, &c2, &c3 ) == 1
             && c2 == 0
             && c3 == 0
             && 35 * c1 + 10 * ( c1 + 1 ) == 100 );
    assert ( hyperloop ( 100, 35, 0, 35, 10, &c1, &c2, &c3 ) == 1
             && c2 == 0
             && 35 * c1 + 35 * c3 + 10 * ( c1 + c3 + 1 ) == 100 );
    assert ( hyperloop ( 100, 35, 35, 35, 10, &c1, &c2, &c3 ) == 1
             && 35 * c1 + 35 * c2 + 35 * c3 + 10 * ( c1 + c2 + c3 + 1 ) == 100 );
    c1 = 42;
    c2 = 43;
    c3 = 44;
    assert ( hyperloop ( 9, 1, 2, 3, 10, &c1, &c2, &c3 ) == 0
             && c1 == 42
             && c2 == 43
             && c3 == 44 );
    return 0;
}
#endif /* __PROGTEST__ */

unsigned long long toReturn(unsigned ** c1, unsigned ** c2, unsigned ** c3, unsigned val1, unsigned val2, unsigned val3, unsigned long long what) {
    **c1 = val1;
    **c2 = val2;
    **c3 = val3;
    return what;
}

void twoSides(unsigned * c1tmp, unsigned * c2tmp, unsigned long long * answer, unsigned long long length, unsigned long long s1andBulk, unsigned long long s2andBulk) {
    unsigned constant, c11 = 0, c22 = 0, c11final = 0, c11prev = 0, c22prev = 0;
    for(constant = 0; constant * s1andBulk <= length; constant++) {
        unsigned long long tmp = length - s1andBulk * constant;
        c11 = constant;
        if(tmp % s2andBulk == 0) {
            c11final = c11;
            c22 = tmp / s2andBulk;
            if(*answer != 0)
                if(c11prev == c22 && c22prev == c11) break;
            c11prev = c11;
            c22prev = c22;
            (*answer)++;
        }
    }
    *c1tmp = c11final;
    *c2tmp = c22;
}
