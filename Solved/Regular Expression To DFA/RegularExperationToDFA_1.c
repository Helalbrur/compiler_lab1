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
                state=1;
                break;

            case 2:
                if(temp=='0')
                state=2;
                if(temp=='1')
                state=3;
                break;

            case 3:
                if(temp=='0')
                state=2;
                if(temp=='1')
                state=1;
                break;
            }
        c++;
    }

    if(state==3)
        printf("Valid string.\n");
    else
        printf("InValid string.\n");
    }
}
