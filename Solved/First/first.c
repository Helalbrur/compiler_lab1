#include<stdio.h>
#include<ctype.h>
#include<string.h>

void findfirst(char,int,int);
char calc_first[20][20],production[20][20],f[20],first[20],ck;
int count,n=0,k,e,ii;

int main(){
    int jm=0,km=0,i;
    char c;
    freopen("input2.txt","r+",stdin);
    scanf("%d",&count);
    getchar();
    for(ii=0;ii<count;ii++){
        gets(production[ii]);
     }
    char done[count];
    int key,ptr=-1;
    int point1=0,point2,xxx;
    for(k=0;k<count; k++){
        c=production[k][0];
        point2=0;
        xxx=0;
        // Checking if First of c has already been calculated
        for(key=0;key<=ptr;key++)
            if(c==done[key])
                xxx=1;

        if (xxx==1)
            continue;

        findfirst(c,0,0);
        ptr+=1;
        // Adding c to the calculated list
        done[ptr]=c;
        printf("\nFirst(%c) = { ",c);
        calc_first[point1][point2++]=c;
        // Printing the First Sets of the grammar
        for(i=0+jm; i<n; i++){
            int lark=0, chk=0;
            for(lark=0; lark<point2; lark++){
                if (first[i]==calc_first[point1][lark]){
                    chk=1;
                    break;
                }
            }
            if(chk==0){
                printf("%c ", first[i]);
                calc_first[point1][point2++] = first[i];
            }
        }
        printf("}\n");
        jm = n;
        point1++;
    }
}

void findfirst(char c,int q1,int q2){
    int j;
    if(!(isupper(c))){
        first[n++]=c;
    }
    for(j=0; j<count; j++){
        if(production[j][0]==c){
            if(production[j][2]=='#'){
                if(production[q1][q2]=='\0')
                    first[n++]='#';
                else if(production[q1][q2]!='\0'
                        && (q1!=0||q2!=0)){
                    findfirst(production[q1][q2],q1,(q2+1));
                }
                else
                    first[n++]='#';
            }
            else if(!isupper(production[j][2])){
                first[n++]=production[j][2];
            }
            else{
                findfirst(production[j][2],j,3);
            }
        }
    }
}




