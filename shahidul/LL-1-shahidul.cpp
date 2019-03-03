/**
    Terminal: Non uppercase character
    Non terminal: Uppercase letter
    Assume epsilon as: @
    Assume id as: i
    
*/

#include<bits/stdc++.h>
using namespace std;
int rule;
set<char> First[30], Follow[30], lft, term;
bool done[30];
vector<string> prod[30];
bool Epsilon[30];
string M[300][300];
int num[300][300];
string grammer[100], g[100];

void find_first(char ch)
{
    int id = ch - 'A';
    if(done[id]) return;
    for(string p:prod[id]){
        int i = 0, len = p.size();
        if(p[0]=='@'){
            First[id].insert(p[0]);
            i = 1;
        }
        if(i<len && !isupper(p[i])){
            First[id].insert(p[i]);
            continue;
        }
        while(i<len){
            if(!isupper(p[i])){
                First[id].insert(p[i]);
                break;
            }
            find_first(p[i]);
            bool epsilon = 0;
            for(char c:First[p[i] - 'A']){
                if(c!='@') First[id].insert(c);
                else {
                    epsilon = 1;
                }
            }
            if(Epsilon[p[i] - 'A']) First[id].insert('@');
            if(!epsilon) break;
            i++;
        }
    }
    done[id] = 1;
}
void find_follow(char ch)
{
    int id = ch - 'A';
    if(done[id]) return;
    for(char letter:lft){
        int let_id = letter - 'A';
        for(string p:prod[let_id]){
            int len = p.size();
            for(int i = 0;i<len;i++){
                if(p[i]!=ch) continue;
                if(i==len-1){
                    if(letter!=ch) find_follow(letter);
                    for(char c:Follow[let_id]) Follow[id].insert(c);
                    break;
                }
                while(i+1<len){
                    if(p[i+1]=='@'){
                        if(letter!=ch) find_follow(letter);
                        for(char c:Follow[let_id]) Follow[id].insert(c);
                    }
                    else if(!isupper(p[i+1])){
                        Follow[id].insert(p[i+1]);
                        break;
                    }
                    else{
                        for(char c:First[p[i+1]-'A']) if(c!='@')
                            Follow[id].insert(c);
                        if(First[p[i+1]-'A'].count('@')){
                            if(letter!=ch) find_follow(letter);
                            for(char c:Follow[let_id]) Follow[id].insert(c);
                        }
                        else break;
                    }
                    if(p[i+1]==ch) break;
                    i++;
                }
            }
        }
    }
    done[id] = 1;
}
string stk, input;
int main()
{
    freopen("inp.txt", "r", stdin);
    //printf("How many production: ");
    cin>>rule;
    //printf("Enter the grammar:\n");
    char ch;
    term.insert('$');
    getchar();
    for(int i=1;i<=rule;i++){
        getline(cin, grammer[i]);
        ch = grammer[i][0];
        int id = ch - 'A';
        if(i==1) Follow[id].insert('$');
        lft.insert(ch);
        int j = 1, len = grammer[i].size();
        while(j<len && grammer[i][j]==' ') ++j;
        while(j<len && grammer[i][j]=='=') ++j;
        while(j<len && grammer[i][j]=='-') ++j;
        while(j<len && grammer[i][j]=='>') ++j;
        while(j<len && grammer[i][j]==' ') ++j;
        g[i] = grammer[i].substr(j,len-j);
        prod[ch-'A'].push_back(g[i]);
        if(g[i]=="@") Epsilon[id] = 1;
        for(char ch:g[i]) if(ch!='@' && !isupper(ch))
            term.insert(ch);
    }
    for(char ch:lft){
        find_first(ch);
    }
    memset(done, 0, sizeof(done));
    for(char ch:lft){
        find_follow(ch);
    }
    
    for(int i = 1;i<=rule;i++){
        char lf = grammer[i][0];
        char st = g[i][0];
        if(g[i]=="@" || (isupper(st) && First[st - 'A'].count('@'))){
            for(char flo:Follow[lf-'A']){
                M[lf][flo] = grammer[i];
                num[lf][flo] = i;
                
            }
            if(Follow[lf-'A'].count('$')){
                M[lf]['$'] = grammer[i];
                num[lf]['$'] = i;
            }
        }
        if(isupper(st)){
            for(char fst:First[st-'A']){
                M[lf][fst] = grammer[i];
                num[lf][fst] = i;
            }
            if(First[st-'A'].count('@') && Follow[lf-'A'].count('$')){
                M[lf]['$'] = grammer[i];
                num[lf]['$'] = i;
            }
        }
        else {
            M[lf][st] = grammer[i];
            num[lf][st] = i;
        }
    }
//    for(char r:lft){
//        cout << r << ":\n======\n";
//        for(char c:term){
//            cout << c << ": " << M[r][c] << "\n";
//        }
//        cout << "\n";
//    }
    cin>>input;
    input+="$";
    int len = input.size();
    stk = "$";
    stk+=grammer[1][0];
    cout << "Stack\t\t\tInput\t\t\tAction\n\n";
    cout << stk << "\t\t\t" << input << "\n";
    int i = 0;
    while(i<len){
        int act;
        if(stk.back()==input[i]){
            stk.pop_back();
            act = 1;
            i++;
        }
        else{
            act = 2;
            int SL = num[stk.back()][input[i]];
            if(SL==0){
                act = 3;
            }
            else{
                string str = g[SL];
                reverse(str.begin(), str.end());
                stk.pop_back();
                if(str!="@")
                    stk+=str;
            }
        }
        cout << stk << "\t\t\t";
        for(int j = i;j<=len;j++)
            cout << input[j];
        cout << "\t\t\t";
        if(act==1)
            cout << "Pop\n";
        else if(act==2)
            cout << "Replace\n";
        else {
            cout << "Error\n";
            break;
        }
    }
    if(stk.size()==0 && i==len)
        cout << "Parsed !\n";
    else cout << "Not parsed\n";
    return 0;
}
