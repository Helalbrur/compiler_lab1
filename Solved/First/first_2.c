#include<stdio.h>
#include<ctype.h>
void FIRST(char*,char );
void addToResultSet(char*,char);
int numOfProductions;
char productionSet[10][10];
char NonTerminal[100];

int main(){
    int i;
    char result[20];
    freopen("input2.txt","r+",stdin);
    printf("Number of productions:");
    scanf("%d",&numOfProductions);
    //getchar();
    int num=0;
    for(i=0;i<numOfProductions;i++){
        gets(productionSet[i]);
        int flag=0;
        for(int j=0;j<num;j++){
            if(NonTerminal[j]==productionSet[i][0]){
                flag=1;
                break;
            }
        }
        if(flag==0){
            NonTerminal[num++]=productionSet[i][0];
        }
    }
    int nn=0;
    do{
        FIRST(result,NonTerminal[nn]);
        printf("\n FIRST(%c)= { ",NonTerminal[nn]);
        for(i=0;result[i]!='\0';i++)
        printf(" %c ",result[i]);
        printf("}\n");
        nn++;
    }
    while(nn<num);
}


void FIRST(char* Result,char ch){
    int i,j,k,foundEpsilon;
    char subResult[20];
    subResult[0]='\0';
    Result[0]='\0';

    //If X is terminal, FIRST(X) = {X}.
    if(!(isupper(ch))){
        addToResultSet(Result,ch);
               return ;
    }
    //If X is non terminal Read each production
    for(i=0;i<numOfProductions;i++){
        //Find production with X as LHS
        if(productionSet[i][0]==ch){
        //If X → ε is a production, then add ε to FIRST(X).
            if(productionSet[i][2]=='$')
                addToResultSet(Result,'$');
            //If X is a non-terminal, and X → Y1 Y2 … Yk
            //is a production, then add a to FIRST(X)
            //if for some i, a is in FIRST(Yi),
            //and ε is in all of FIRST(Y1), …, FIRST(Yi-1).
      else
            {
                j=2;
                while(productionSet[i][j]!='\0'){
                foundEpsilon=0;
                FIRST(subResult,productionSet[i][j]);
                for(k=0;subResult[k]!='\0';k++)
                    addToResultSet(Result,subResult[k]);
                 for(k=0;subResult[k]!='\0';k++)
                     if(subResult[k]=='$'){
                         foundEpsilon=1;
                         break;
                     }
                 //No ε found, no need to check next element
                 if(!foundEpsilon)
                     break;
                 j++;
                }
            }
    }
}
    return ;
}

void addToResultSet(char* Result,char val){
    int k;
    for(k=0 ;Result[k]!='\0';k++)
        if(Result[k]==val)
            return;
    Result[k]=val;
    Result[k+1]='\0';
}

