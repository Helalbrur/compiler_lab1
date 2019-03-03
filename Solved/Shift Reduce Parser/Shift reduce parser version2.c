#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char input[15],stk[15];
int ip_ptr=0,st_ptr=0,len,i;
char temp[2],temp2[2];
char act[15];
void check();
int main(){
    printf("Enter a string: ");
    gets(input);
    printf("\nStack\t\t Input \t\t Action");
    printf("\n$\t\t%s$\t\t\t--",input);

    strcpy(act,"Shift  ");
    temp[0]=input[ip_ptr];
    temp[1]='\0';
    strcat(act,temp);
    len=strlen(input);
    for(i=0;i<=len-1;i++){
        stk[st_ptr]=input[ip_ptr];
        stk[st_ptr+1]='\0';
        input[ip_ptr]=' ';
        ip_ptr++;
        printf("\n$%s\t\t%s$\t\t\t%s",stk,input,act);
        strcpy(act,"shift ");
        temp[0]=input[ip_ptr];
        temp[1]='\0';
        strcat(act,temp);
        check();
        st_ptr++;
    }
    st_ptr++;
    check();
}


void check(){
    int flag=0;
    temp2[0]=stk[st_ptr];
    temp2[1]='\0';
    if((!strcmpi(temp2,"a"))||(!strcmpi(temp2,"(E)"))){
        stk[st_ptr]='F';
        //strcpy(stk,"F");
        //st_ptr=0;
        if(!strcmpi(temp2,"a"))
            printf("\n$%s\t\t%s$\t\t\tF->id",stk, input);
        else
           printf("\n$%s\t\t%s$\t\t\tF->(E)",stk,input);
        flag=1;
    }
    if((!strcmpi(temp2,"+"))||(strcmpi(temp2,"*"))||(strcmpi(temp2,"("))||(strcmpi(temp2,")"))){
        flag=1;
    }
    if((!strcmpi(stk,"E+T"))||(!strcmpi(stk,"T"))){
        strcpy(stk,"E");
        st_ptr=0;
        if(!strcmpi(stk,"E+T"))
            printf("\n$%s\t\t%s$\t\t\tE->E+T",stk,input);
        else
            printf("\n$%s\t\t %s$\t\t\tE->T",stk,input);
        flag=1;
    }
    if((!strcmpi(stk,"T*F"))||(!strcmpi(stk,"F"))){
        strcpy(stk,"T");
        st_ptr=0;
        if(!strcmpi(stk,"T*F"))
            printf("\n$%s\t\t %s$\t\t\tT->T*F",stk,input);
        else
            printf("\n$%s\t\t %s$\t\t\tT->F",stk,input);
        flag=1;
    }

    if(!strcmpi(stk,"E")&&ip_ptr==len){
        printf("\n$%s\t\t%s$\t\t\tAccepted.",stk,input);
        exit(0);
    }
    if(flag==0){
        printf("\n%s\t\t\t%s\t\t Rejected.",stk,input);
        exit(0);
    }
    return;
}

/*
E->E+E
E->E/E
E->E*E
E->a/b
*/
