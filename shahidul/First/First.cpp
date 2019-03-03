/**
    Terminal: Non uppercase character
    Non terminal: Uppercase letter
    Assume epsilon as: #
    Assume id as: i
    
*/

#include<bits/stdc++.h>
using namespace std;
int rule;
map<string, int> Id;
set<char> First[30], Follow[30], lft;
bool done[30];
vector<string> prod[30];
bool Epsilon[30];
void find_first(char ch)
{
    int id = ch - 'A';
    if(done[id]) return;
    for(string p:prod[id]){
        int len = p.size();
        for(int i = 0;i<len;i++){
            char cur = p[i];
            if(isupper(p[i])){
                while(isupper(cur)){
                    find_first(cur);
                    bool epsilon = 0;
                    for(char c:First[cur - 'A']){
                        if(c!='#')
                            First[id].insert(c);
                    }
                    if(Epsilon[cur - 'A']) First[id].insert('#');
                    if(!epsilon) break;
                    cur = p[i++];
                }
            }
            else {
                First[id].insert(cur);
                break;
            }
        }
    }
    done[id] = 1;
}

int main()
{
    //freopen("input4.txt", "r", stdin);
    //printf("How many production: ");
    cin>>rule;
    //printf("Enter the grammar:\n");
    char ch;
    getchar();
    for(int i=0;i<rule;i++){
        string grammer;
        getline(cin, grammer);
        ch = grammer[0];
        int id = ch - 'A';
        lft.insert(ch);
        string g;
        for(int j = 1;j<grammer.size();j++){
            if(grammer[j]==' ' || grammer[j]=='=' || grammer[j]=='-' || grammer[j]=='>') continue;
            if(grammer[j]=='|'){
                prod[ch-'A'].push_back(g);
                if(g=="#") Epsilon[id] = 1;
                g = "";
            }
            else g+=grammer[j];
        }
        if(g.size()>0){
            if(g=="#") Epsilon[id] = 1;
            prod[id].push_back(g);
        }
    }
    for(char ch:lft){
        find_first(ch);
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
    return 0;
}


