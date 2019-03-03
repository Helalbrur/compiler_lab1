#include<stdio.h>
#include<string.h>
char stk[15], input[50];
char left[50][50], right[50][50], temp[5], str[50];
int rule, stk_idx, inp_idx, len;
int is_operator(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' || ch=='(' || ch==')')
        return 1;
    return 0;
}

int check(char *Stk, int in_idx)
{
    printf("%s %d\n", Stk, in_idx);
    if(strlen(Stk)==1 && in_idx==len){
        //printf("!!!\n");
        return 1;
    }
    if(in_idx==len) return 0;
    int idx;
    char cur[50];
    int c = 0;
    for(idx=in_idx;idx<len;idx++){
        if(is_operator(str[in_idx])){
            cur[c++] = str[in_idx];
            cur[c] = '\0';
            in_idx++;
        }
        else{
            while(in_idx<len && !is_operator(str[in_idx])){
                cur[c++] = str[in_idx];
                in_idx++;
            }
            cur[c] = '\0';
        }
    }
    strcat(Stk, cur);
    printf("%s]]\n", Stk);
    char temp[50];
    strcpy(temp, Stk);
    if(check(Stk, in_idx)==1) return 1;
    int k,i;
    c = 0;
    for(idx=strlen(Stk)-1;idx>=0;idx--){
        cur[c++] = Stk[idx];
        cur[c] = '\0';
        strrev(cur);
        for(i=0;i<rule;i++) if(strcmp(right[i],cur)==0){
            temp[idx] = '\0';
            strcat(temp, left[i]);
            //printf("%s @\n", temp);
            if(check(temp, in_idx)==1)
                return 1;
        }
        strrev(cur);
    }
    return 0;
}
int main()
{
    freopen("input2.txt", "r", stdin);
    int i,j,k;
    //printf("How many production: ");
    scanf("%d", &rule);
    //printf("Enter the grammar:\n");
    for(i=0;i<rule;i++){
        scanf("%s%s%s", left[i], temp, right[i]);
    }
    //printf("Input: ");
    scanf("%s", str);
    len = strlen(str);
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
        strcat(stk,cur);
        printf("$%s\t\t",stk);
        for(i=inp_idx;i<len;i++)
            printf("%c", input[i]);
        printf("$\t\tShift %s\n",cur);
        char temp[50];
        //if(check(stk, inp_idx)==1) continue;
        strcpy(temp, stk);
        int k,i;
        int ok = 0,idx;
        c = 0;
        for(idx=strlen(stk)-1;idx>=0;idx--){
            cur[c++] = stk[idx];
            cur[c] = '\0';
            strrev(cur);
            for(i=0;i<rule;i++) if(strcmp(right[i],cur)==0){
                temp[idx] = '\0';
                printf("%s", temp);
                strcat(temp, left[i]);
                //printf(" => %s\n", temp);
                if(check(temp, inp_idx)==1){
                    printf("$");
                    strcpy(stk, temp);
                    printf("%s\t\t", stk);
                    for(k=inp_idx;k<len;k++)
                        printf("%c", input[k]);
                    printf("\t\tReduce %s\n", cur);
                    ok = 1;
                    break;
                }
            }
            if(ok==1) break;
            strrev(cur);
        }
    }
    if(strlen(stk)==1)
        printf("The given string is accepted\n");
    else 
        printf("The given string is not accepted\n");
    return 0;
}

