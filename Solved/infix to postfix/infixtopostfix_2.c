#include<stdio.h>
#include <ctype.h>
char stk[100];
int top = -1;

char push(char ch){
    stk[++top]=ch;
}

char pop(){
    return(stk[top--]);
}

int precedence(char ch){
    if(ch=='#')
        return 0;
    else if(ch=='(')
        return 1;
    else if(ch=='+' || ch=='-')
        return 2;
    else if(ch=='*' || ch=='/')
        return 3;
}
/*int precedence(char ch){
    switch(ch){
    case '#': return 0;
    case '(': return 1;
    case '+':
    case '-': return 2;
    case '*':
    case '/': return 3;
    }
}
*/
int main(){
    char infix[100],postfix[100],ch,elem;
    printf("Enter an infix expression:");
    scanf("%s",infix);
    push('#');
    int i=0,k=0;
    while((ch=infix[i++])!='\0'){
        if(ch=='(')
            push(ch);
        else if(isalnum(ch))
                postfix[k++]=ch;
            else if(ch==')'){
                    while(stk[top] != '(')
                        postfix[k++]=pop();
                        elem=pop();
                }
                else{
                    while(precedence(stk[top])>=precedence(ch))
                        postfix[k++]=pop();
                        push(ch);
                }
    }

    while(stk[top]!='#')
        postfix[k++]=pop();
        postfix[k]='\0';
        printf("\nPostfix Expression =  %s\n",postfix);
}


