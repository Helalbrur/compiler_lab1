#include<stdio.h>
#include<conio.h>
#include<string.h>

int i=1,j=0,no=0,tmpch=90;
char str[100],left[15],right[15];
void findopr();
void explore();
void fleft(int);
void fright(int);
struct exp{
	int pos;
	char op;
}k[15];
struct quard{
    char op;
    char arg1;
    char arg2;
    char result;
};
void main(){
	printf("Enter the Expression :");
	gets(str);
	findopr();
	explore();
	getch();
}
void findopr(){
	for(i=0;str[i]!='\0';i++)
		if(str[i]=='/'){
            k[j].pos=i;
            k[j++].op='/';
		}
	for(i=0;str[i]!='\0';i++)
		if(str[i]=='*'){
            k[j].pos=i;
            k[j++].op='*';
		}
	for(i=0;str[i]!='\0';i++)
		if(str[i]=='+'){
            k[j].pos=i;
            k[j++].op='+';
		}
	for(i=0;str[i]!='\0';i++)
		if(str[i]=='-'){
            k[j].pos=i;
            k[j++].op='-';
		}
}

void explore(){
	i=0;
	int xx=0;
	printf(" OP\t\arg1\targ2\tresult\n");
	while(k[i].op!='\0'){
		fleft(k[i].pos);
		fright(k[i].pos);
		str[k[i].pos]=tmpch--;
		printf("%c\t%s\t%s\t%c",k[i].op,left,right,str[k[i].pos]);
		printf("\n");
		i++;
	}
	fright(-1);
	if(no==0)
	{
		fleft(strlen(str));
		printf("=\t%s\t\t%s\n",left,right);
		getch();
		exit(0);
	}
	printf("=\t%s\t\t%s\n",left,right);
	getch();
}
void fleft(int x){
	int w=0,flag=0,pp=x;
	x--;
	while(x!= -1 &&str[x]!= '+' &&str[x]!='*'&&str[x]!='='&&str[x]!='\0'&&str[x]!='-'&&str[x]!='/'&&str[x]!=':'){
		if(str[x]!='$'&& flag==0){
            left[w++]=str[x];
            left[w]='\0';
            str[x]='$';
            flag=1;
		}
		x--;
	}
}
void fright(int x){
	int w=0,flag=0;
	x++;
	while(str[x]!= '\0' && str[x]!= '+'&&str[x]!='*'&&str[x]!='\0'&&str[x]!='='&&str[x]!=':'&&str[x]!='-'&&str[x]!='/'){
		if(str[x]!='$'&& flag==0){
		right[w++]=str[x];
		right[w]='\0';
		str[x]='$';
		flag=1;
		}
		x++;
	}
}











