#include<stdio.h>
#include<string.h>
int i=0,j=0,k=0,z=0,length=0;
char stk[15], input[50];
char left[50][50], right[50][50], temp[5], str[50];
int rule, stk_idx, inp_idx;
int is_operator(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' || ch=='(' || ch==')')
        return 1;
    return 0;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int i,j,k;
    //printf("How many production: ");
    scanf("%d", &rule);
    //printf("Enter the grammar:\n");
    for(i=0;i<rule;i++){
        scanf("%s%s%s", left[i], temp, right[i]);
    }
    //printf("Input: ");
    scanf("%s", str);
    int len = strlen(str);
    strcpy(input, str);
    printf("Stack\t\tInput\t\tAction\n");
    printf("=======     ===============   =============\n");
    printf("$\t\t%s$\n",str);
    stk[0] = '\0';
    while(1){
        if(inp_idx==len) break;
        char cur[50];
        int c = 0;
        if(is_operator(str[inp_idx])){
            cur[c++] = str[inp_idx];
            cur[c] = '\0';
            inp_idx++;
        }
        else{
            while(inp_idx<len && !is_operator(str[inp_idx])){
                cur[c++] = str[inp_idx];
                inp_idx++;
            }
            cur[c] = '\0';
        }
        printf("$%s%s\t\t",stk, cur);
        for(i=inp_idx;i<len;i++)
            printf("%c", input[i]);
        printf("$\t\tShift %s\n",cur);
        if(strcmp(cur,")")==0){
            char temp[50];
            for(i=strlen(stk)-1;i>=0;i--){
                if(stk[i]=='(') break;
            }
            j = i;
            int t = 0;
            for(;i<strlen(stk);i++){
                temp[t++] = stk[i];
            }
            temp[t] = ')';
            temp[t+1] = '\0';
            strcpy(cur, temp);
            stk[j] = '\0';
            //printf("%s!!\n", cur);
        }
        
        while(1){
            int reduce = 0;
            for(i=0;i<rule;i++){
                if(strcmp(cur, right[i])==0){
                    printf("$%s%s\t\t",stk,left[i]);
                    for(j=inp_idx;j<len;j++)
                        printf("%c", input[j]);
                    printf("$\t\tReduce %s\n", cur);
                    strcpy(cur, left[i]);
                    reduce = 1;
                    break;
                }
            }
            if(reduce==0) break;
        }
        strcat(stk,cur);
        while(1){
            int reduce = 0;
            for(i=0;i<rule;i++){
                if(strcmp(stk, right[i])==0){
                    printf("$%s\t\t",left[i]);
                    for(j=inp_idx;j<len;j++)
                        printf("%c", input[j]);
                    printf("$\t\tReduce %s\n", stk);
                    strcpy(stk, left[i]);
                    reduce = 1;
                    break;
                }
            }
            if(reduce==0) break;
            strcpy(cur, stk);
        }
    }
    if(strlen(stk)==1)
        printf("The given string is accepted\n");
    else 
        printf("The given string is not accepted\n");
    return 0;
}
