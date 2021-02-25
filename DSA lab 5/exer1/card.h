
#include<stdio.h>
#include<stdlib.h>


struct card{
    long long cardNum;
    char bankCode[5];
    struct{
        int m;
        int y;
    } expDate;
    char firstName[10];
    char lastName[10];    
};