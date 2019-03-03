#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int z = 0, i = 0, j = 0, c = 0;
char a[100], ac[100], stk[100], act[100];

void check(){
	strcpy(ac,"REDUCE TO F -> ");
	for(z = 0; z < c; z++){
		if(stk[z] == 'a'){
			printf("%sa", ac);
			stk[z] = 'F';
			stk[z + 1] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
		}
	}

	for(z = 0; z < c - 2; z++){
		if(stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'T'){
			printf("%sE+T", ac);
			stk[z] = 'E';
			stk[z + 1] = '\0';
			stk[z + 2] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}

	for(z = 0; z < c - 2; z++){
		if(stk[z] == 'T'){
			printf("%sT", ac);
			stk[z] = 'E';
			stk[z + 1] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}

	for(z = 0; z < c - 2; z++){
		if(stk[z] == 'T' && stk[z + 1] == '*' &&stk[z + 2] == 'F'){
			printf("%sT*F", ac);
			stk[z] = 'T';
			stk[z + 1] = '\0';
			stk[z + 2] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}

	for(z=0; z<c-2; z++){
		if(stk[z] == 'F'){
			printf("%sF",ac);
			stk[z]='T';
			stk[z + 1]='\0';
			stk[z + 1]='\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}

	for(z = 0; z < c - 2; z++){
		if(stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')'){
			printf("%s(E)", ac);
			stk[z] = 'F';
			stk[z + 1] = '\0';
			stk[z + 2] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}
	return ;
}


int main(){
	strcpy(a,"a+a*a");
	c=strlen(a);
	strcpy(act,"SHIFT");
	printf("\nstack \t input \t action");
	printf("\n$\t%s$\t", a);
	for(i = 0; j < c; i++, j++){
		printf("%s", act);
		stk[i] = a[j];
		stk[i + 1] = '\0';
		a[j]=' ';
		printf("\n$%s\t%s$\t", stk, a);
		check();
	}
	check();
	if(stk[0] == 'E' && stk[1] == '\0')
		printf("Accepted\n");
	else
		printf("Rejected\n");
}
