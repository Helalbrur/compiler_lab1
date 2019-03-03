#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

char oper[500], ident[500][50], integer[500][50], real[500][50], keyword[500][50], invalid[500][50];
int oplen, idenlen, intlen, reallen, keylen, invlen;
bool isDelimiter(char ch){
	if (ch == '+' || ch == '-' || ch == '*' ||ch == '/' ||
        ch == ' ' ||ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' ||ch=='&' ||ch=='|')
		return (true);
	return (false);
}

bool isOperator(char ch){
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=' || ch=='|' || ch=='&')
		return (true);
	return (false);
}

bool validIdentifier(char* str){
	if ((str[0] >= '0' && str[0]<='9') ||  str[0] == '#' || str[0]=='"' || str[0]=='%' || str[0]=='&' || isDelimiter(str[0]) == true)
		return (false);
    int len = strlen(str), i;
    for(i=1;i<len;i++){
        if(str[i]=='_' || str[i]=='$' || isalnum(str[i])) continue;
        return 0;
    }
	return (true);
}

bool isKeyword(char* str){
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") ||
		!strcmp(str, "break") ||
		!strcmp(str, "continue") || !strcmp(str, "int")
		|| !strcmp(str, "double") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char")
		|| !strcmp(str, "case") || !strcmp(str, "char")
		|| !strcmp(str, "sizeof") || !strcmp(str, "long")
		|| !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "switch") || !strcmp(str, "unsigned")
		|| !strcmp(str, "void") || !strcmp(str, "static")
		|| !strcmp(str, "struct") || !strcmp(str, "goto"))
		return (true);
	return (false);
}

bool isInteger(char* str){
	int i, len = strlen(str);
	if (len == 0)
		return (false);
	for (i = 0; i < len; i++){
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

bool isRealNumber(char* str){
	int i, len = strlen(str);
	bool hasDecimal = false;
	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

char* subString(char* str, int left, int right){
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));
    //char subStr[right-left+2];
	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
        subStr[right - left + 1] = '\0';
	return (subStr);
}

void parse(char str[]){
	int left = 0, right = 0;
	int len = strlen(str);
	while (right <= len && left <= right) {
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right) {
			if (isOperator(str[right]) == true){
                oper[oplen++] = str[right];
				/*printf("%c is an operator.\n", str[right]);*/
			}

			right++;
			left = right;
		} else if (isDelimiter(str[right]) == true && left != right
				|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);

			if (isKeyword(subStr) == true){
				/*printf("%s is a keyword.\n", subStr);*/

				strcpy(keyword[keylen++], subStr);
			}

			else if (isInteger(subStr) == true){
				/*printf("%s is an integer.\n", subStr);*/
                strcpy(integer[intlen++], subStr);
			}

			else if (isRealNumber(subStr) == true){
				/*printf("%s is a real number.\n", subStr);*/
				strcpy(real[reallen++], subStr);
			}
			else if (validIdentifier(subStr) == true
					&& isDelimiter(str[right - 1]) == false){
				/*printf("%s is a valid identifier.\n", subStr);*/
				strcpy(ident[idenlen++], subStr);
            }

			else if (validIdentifier(subStr) == false
					&& isDelimiter(str[right - 1]) == false){
				/*printf("%s is not a valid identifier.\n", subStr);*/
                strcpy(invalid[invlen++], subStr);
            }
			left = right;
		}
	}
	return;
}

int main(){
   FILE *file =freopen("file.txt","r+",stdin);
   if (file != NULL ){
      char str[200];
      while(fgets(str,sizeof str, file )!= NULL ){ /* read a line */
            if(strlen(str)==0) continue;
            int i = 0, ch = 0;
            while(str[i]!='\n'){
                if(str[i]!=' ') ch++;
                    i++;
            }
            if(ch==0) continue;
            str[i] = '\0';
            parse(str);
      }
      int i;
      printf("List of identifiers in the program:\n");
      for(i=0;i<idenlen;i++)
          printf("%s ", ident[i]);
      printf("\n\n");

      printf("List of keywords in the program:\n");
      for(i=0;i<keylen;i++)
          printf("%s ", keyword[i]);
      printf("\n\n");

      printf("List of integer number in the program:\n");
      for(i=0;i<intlen;i++)
          printf("%s ", integer[i]);
      printf("\n\n");


      printf("List of real numbers in the program:\n");
      for(i=0;i<reallen;i++)
          printf("%s ", real[i]);
      printf("\n\n");

      printf("List of real operators in the program:\n");
      for(i=0;i<oplen;i++)
          printf("%c ", oper[i]);
      printf("\n\n");

      fclose (file);
   }

}
