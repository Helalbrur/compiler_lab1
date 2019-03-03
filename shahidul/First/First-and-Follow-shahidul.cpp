/**
    Terminal: Non uppercase character
    Non terminal: Uppercase letter
    Assume epsilon as: @
    Assume id as: i
    
*/

#include<bits/stdc++.h>
using namespace std;
int rule;
set<char> First[30], Follow[30], lft;
bool done[30];
vector<string> prod[30];
bool Epsilon[30];
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
int main()
{
    freopen("input4.txt", "r", stdin);
    //printf("How many production: ");
    cin>>rule;
   // printf("Enter the grammar:\n");
    char ch;
    getchar();
    for(int i=0;i<rule;i++){
        string grammer;
        getline(cin, grammer);
        ch = grammer[0];
        int id = ch - 'A';
        if(i==0) Follow[id].insert('$');
        lft.insert(ch);
        string g;
        for(int j = 1;j<grammer.size();j++){
            if(grammer[j]==' ' || grammer[j]=='=' || grammer[j]=='-' || grammer[j]=='>') continue;
            if(grammer[j]=='|'){
                prod[ch-'A'].push_back(g);
                if(g=="@") Epsilon[id] = 1;
                g = "";
            }
            else g+=grammer[j];
        }
        if(g.size()>0){
            if(g=="@") Epsilon[id] = 1;
            prod[id].push_back(g);
        }
    }
    for(char ch:lft){
        find_first(ch);
    }
    
    memset(done, 0, sizeof(done));
    for(char ch:lft){
        find_follow(ch);
    }
    for(char ch:lft){
        cout << "First of " << ch << ": {";
        int cnt = 0;
        for(char c:First[ch-'A']) {
                if(cnt>0) cout << ", ";
                cout << c ;
                cnt++;
        }
        cout << "}\n";
    }
    cout << "\n\n";
    for(char ch:lft){
        cout << "Follow of " << ch << ": {";
        int cnt = 0;
        for(char c:Follow[ch-'A']) {
                if(cnt>0) cout << ", ";
                cout << c ;
                cnt++;
        }
        cout << "}\n";
    }
    return 0;
}


