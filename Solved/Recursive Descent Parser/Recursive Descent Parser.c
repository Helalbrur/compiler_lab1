#include<stdio.h>
#include<string.h>
#include<ctype.h>

char input[100];
int i,error,length;
void E();
void T();
void E_desh();
void T_desh();
void F();
int main(){
    printf("Enter a string: ");
    while(1){
    i=0,error=0;
    scanf("%s",input);
    length=strlen(input);
    E();
    if(length==i&&error==0)
        printf("\nGiven string is accepted.\n");
    else
        printf("\nGiven string is rejected.\n");
    }
}

void E(){
    T();
    E_desh();
}
void E_desh(){
     if(input[i]=='+'){
        i++;
        T();
        E_desh();
     }
}
void T(){
     F();
     T_desh();
}
void T_desh(){
     if(input[i]=='*'){
         i++;
         F();
         T_desh();
    }
}
void F(){
    if((input[i])=='a')
        i++;
    else if(input[i]=='('){
          i++;
          E();
        if(input[i]==')')
            i++;
        else
            error=1;
   }

    else
        error=1;
}


