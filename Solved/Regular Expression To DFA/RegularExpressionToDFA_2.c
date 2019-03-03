#include<stdio.h>
#include<string.h>
int main(){
    while(1){
    char str[20],temp;
    int len,state,c;
    printf("Enter the string to check\n");
    gets(str);
    len=strlen(str);

    c=0;
    state=1; // initial state
      while(c<len){
            temp=str[c];
        switch(state){
            case 1:
                if(temp=='0')
                state=2;

                if(temp=='1')
                state=5;
                break;

            case 2:
                if(temp=='0')
                state=8;
                if(temp=='1')
                state=3;
                break;

            case 3:
                if(temp=='0')
                state=8;
                if(temp=='1')
                state=4;
                break;
            case 4:
                if(temp=='0')
                state=8;
                if(temp=='1')
                state=4;
                break;

            case 5:
                if(temp=='0')
                state=5;
                if(temp=='1')
                state=6;
                break;

            case 6:
                if(temp=='0')
                state=9;
                if(temp=='1')
                state=7;
                break;

            case 7:
                if(temp=='0')
                state=9;
                if(temp=='1')
                state=9;
                break;
            case 8:
                if(temp=='0')
                state=8;
                if(temp=='1')
                state=8;
                break;
             case 9:
                if(temp=='0')
                state=9;
                if(temp=='1')
                state=9;
                break;
            }
        c++;
    }

    if(state==4||state==7)
        printf("Valid string.\n");
    else
        printf("InValid string.\n");
    }
}

