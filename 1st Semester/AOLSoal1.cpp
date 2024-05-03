#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse(char *str) {
	int i,j = 0;
	j = strlen(str) - 1;

	
	while (i < j) {
	 int temp = str[i];
	 str[i] = str[j];
	 str[j] = temp;
	 i++;
	 j--;
	}
}

void inverse(char *str) {

	int l = strlen(str);
	
	for (int i = 0; i < l; i++) {	
	  if (islower(str[i])) {
		str[i] = toupper(str[i]);
	}
	  else if (isupper(str[i])) {
		str[i] = tolower(str[i]);
	}
}

}


int main () {
	
	char s[200];
	
	printf ("Input string: ");
	scanf("%[^\n]", s);
	getchar();

	
	reverse(s);
	printf ("Reversed string: %s\n", s);
	
	
	inverse(s);
	printf ("Inverted string: %s\n", s);

	return 0;
}

//Fay 
