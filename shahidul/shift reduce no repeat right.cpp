#include<bits/stdc++.h>
using namespace std;
string input, lft[50], rgt[50];
int rule, len;
map<string, string> prod;
int is_operator(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' || ch=='(' || ch==')')
        return 1;
    return 0;
}
int check(string cur_stk, int inp_idx)
{
    if(cur_stk.size()==1 && inp_idx==len)
        return 1;
    string cur, tmp_stk = cur_stk;
    while(tmp_stk.size()>0){
        cur = tmp_stk.back() + cur;
        tmp_stk.pop_back();
        if(prod.find(cur)==prod.end()) continue;
        if(check(tmp_stk+prod[cur], inp_idx)==1)
            return 1;
    }
    if(inp_idx==len) return 0;
    cur = "";
    if(is_operator(input[inp_idx])){
        cur += input[inp_idx++];
    }
    else{
        while(inp_idx<len && !is_operator(input[inp_idx])){
            cur += input[inp_idx++];
        }
    }
    cur_stk+=cur;
    if(check(cur_stk, inp_idx)==1) return 1;
    return 0;
}
int main()
{
    freopen("input2.txt", "r", stdin);
    int i,j,k;
    //printf("How many production: ");
    cin>>rule;
    //printf("Enter the grammar:\n");
    string tmp;
    for(int i=0;i<rule;i++){
        cin >> lft[i] >> tmp >> rgt[i];
        prod[rgt[i]] = lft[i];
    }
    //printf("Input: ");
    cin>>input;
    len = input.size();
    cout << "Stack\t\t\tInput\t\t\tAction\n";
    cout << "=======               ===============         =============\n";
    cout << "$\t\t\t$" << input << "\n";
    string cur_stk;
    int inp_idx = 0;
    while(inp_idx<len){
        string cur;
        if(is_operator(input[inp_idx])){
            cur += input[inp_idx++];
        }
        else{
            while(inp_idx<len && !is_operator(input[inp_idx])){
                cur += input[inp_idx++];
            }
        }
        cur_stk+=cur;
        cout << "$" << cur_stk << "\t\t\t";
        for(i=inp_idx;i<len;i++)
            cout << input[i];
        cout << "$\t\t\tShift " << cur << "\n";
        cur = "";
        string tmp_stk = cur_stk;
        while(tmp_stk.size()>0){
            cur = tmp_stk.back() + cur;
            tmp_stk.pop_back();
            if(prod.find(cur)==prod.end()) continue;
            if(check(tmp_stk+prod[cur], inp_idx)==1){
                cur_stk = tmp_stk+prod[cur];
                tmp_stk = cur_stk;
                cout << "$";
                cout << cur_stk << "\t\t\t";
                for(int k=inp_idx;k<len;k++)
                    printf("%c", input[k]);
                cout << "$\t\t\t Reduce " << cur << "\n";
                cur = "";
            }
        }
    }
    if(cur_stk.size()==1)
        printf("The given string is accepted\n");
    else 
        printf("The given string is not accepted\n");
    return 0;
}
