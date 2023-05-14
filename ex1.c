#include <stdio.h>
#include <stdlib.h>
#define ISDIGIT(x) (x >= '0' && x<= '9')

int interface();
void in_switch(int ch, int a, int b);
int alu (char del);
int a1 = 0,a2 = 0,a3 = 0,a4 = 0,a5 = 0,a6 = 0,a7 = 0,a8 = 0,a9 = 0,a10 = 0;
int b1 = 0,b2 = 0,b3 = 0,b4 = 0,b5 = 0,b6 = 0,b7 = 0,b8 = 0,b9 = 0,b10 = 0;
int carry = 0;
int overflow = 0;
int main(void)
{
    while(1)
    {
        if (!interface())
            break;
        while(fgetc(stdin) != '\n');
    }
    exit(0);
}

int interface() {
    int ch;
    while ((ch = fgetc(stdin)) != '+') {
        if (ch == ' ' && !ISDIGIT(ch))
            continue;

        a10 = (a10*10 + a9/100)%1000;
        a9 = (a9*10 + a8/100)%1000;
        a8 = (a8*10 + a7/100)%1000;
        a7 = (a7*10 + a6/100)%1000;
        a6 = (a6*10 + a5/100)%1000;
        a5 = (a5*10 + a4/100)%1000;
        a4 = (a4*10 + a3/100)%1000;
        a3 = (a3*10 + a2/100)%1000;
        a2 = (a2*10 + a1/100)%1000;
        a1 = (a1*10 + (ch - '0'))%1000;
    }
    while ((ch = fgetc(stdin)) != '\n') {
        if (ch == ' ' && !ISDIGIT(ch))
            continue;

        b10 = (b10*10 + b9/100)%1000;
        b9 = (b9*10 + b8/100)%1000;
        b8 = (b8*10 + b7/100)%1000;
        b7 = (b7*10 + b6/100)%1000;
        b6 = (b6*10 + b5/100)%1000;
        b5 = (b5*10 + b4/100)%1000;
        b4 = (b4*10 + b3/100)%1000;
        b3 = (b3*10 + b2/100)%1000;
        b2 = (b2*10 + b1/100)%1000;
        b1 = (b1*10 + (ch - '0'))%1000;
    }
    a2 = (a2+b2) + (a1+b1)/1000; 
    a1 = (a1+b1)%1000;
    a3 = (a3+b3) + (a2+b2)/1000;
    a2 = a2 % 1000;
    a4 = (a4+b4) + (a3+b3)/1000;
    a3 = a3 % 1000;
    a5 = (a5+b5) + (a4+b4)/1000;
    a4 = a4 % 1000;
    a6 = (a6+b6) + (a5+b5)/1000;
    a5 = a5 % 1000;
    a7 = (a7+b7) + (a6+b6)/1000;
    a6 = a6 % 1000;
    a8 = (a8+b8) + (a7+b7)/1000;
    a7 = a7 % 1000;
    a9 = (a9+b9) + (a8+b8)/1000;
    a8 = a8 % 1000;
    a10 = (a10+b10) + (a9+b9)/1000;
    a9 = a9 % 1000;
    if (a10 >= 1000)
        overflow++;

    if (overflow)
        printf("overflow!\n");
    else
    {
        printf("%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n", a10,a9,a8,a7,a6,a5,a4,a3,a2,a1);
        a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = a10 = b1 = b2 = b3 = b4 = b5 = b6 = b7 = b8 = b9 = b10 = 0;
    }
    overflow = 0;
    printf("계속 하시겠습니까?\n");
    if((ch = fgetc(stdin)) == 'y')
        return 1;
    else if (ch == 'n')
        return 0;
    
}
