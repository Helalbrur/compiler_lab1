#include<bits/stdc++.h>
using namespace std;
string input, lft[50], rgt[50];
int rule, len;
int is_operator(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' || ch=='(' || ch==')')
        return 1;
    return 0;
}

int check(string cur_stk, int inp_idx)
{
    cout << cur_stk << " -> " << inp_idx << "\n";
    if(cur_stk.size()==1 && inp_idx==len)
        return 1;
    if(inp_idx==len) return 0;
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
    if(check(cur_stk, inp_idx)==1) return 1;
    cur = "";
    for(int idx=cur_stk.size()-1;idx>=0;idx--){
        cur += cur_stk[idx];
        reverse(cur.begin(), cur.end());
        string temp_cur = cur;
        while(1){
            int ok = 0;
            for(int i=0;i<rule;i++) if(rgt[i] == temp_cur){
                string temp = cur_stk.substr(0,idx);
                temp+=lft[i];
                for(int j=0;j<temp.size();j++){
                    string tt = temp.substr(j,temp.size()-j);
                    for(int k = 0;k<rule;k++)if(rgt[k]==tt){
                        if(check(temp.substr(0,j)+lft[k], inp_idx)==1)
                            return 1;
                    }
                }
                temp_cur = lft[i];
                ok = 1;
            }
            if(ok==0) break;
        }
        reverse(cur.begin(), cur.end());
    }
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
    }
    //printf("Input: ");
    cin>>input;
    len = input.size();
    cout << "Stack\t\tInput\t\tAction\n";
    cout << "=======     ===============   =============\n";
    cout << "$\t\t$" << input << "\n";
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
        cout << "$" << cur_stk << "\t\t";
        for(i=inp_idx;i<len;i++)
            cout << input[i];
        cout << "$\t\tShift " << cur << "\n";
        string temp;
        if(check(cur_stk, inp_idx)==1) continue;
        cur = "";
        for(int idx=cur_stk.size()-1;idx>=0;idx--){
            cur += cur_stk[idx];
            reverse(cur.begin(), cur.end());
            string temp_cur = cur;
            while(1){
                int ok = 0;
                for(int i=0;i<rule;i++) if(rgt[i] == temp_cur){
                    ok = 1;
                    //cout << "##\n";
                    string temp = cur_stk.substr(0,idx);
                    temp+=lft[i];
                    if(check(temp, inp_idx)==1){
                        cout << "$";
                        cur_stk = temp;
                        cout << cur_stk << "\t\t";
                        for(int k=inp_idx;k<len;k++)
                            printf("%c", input[k]);
                        cout << "\t\tReduce " << temp_cur << "\n";
                        //cout << "!!\n";
                    }
                    temp_cur = lft[i];
                    break;
                }
                if(ok==0) break;
            }
            reverse(cur.begin(), cur.end());
        }
    }
    if(cur_stk.size()==1)
        printf("The given string is accepted\n");
    else 
        printf("The given string is not accepted\n");
    return 0;
}


