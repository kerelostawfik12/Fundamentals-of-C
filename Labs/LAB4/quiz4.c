#include <stdio.h> /* printf, scanf */
#include <string.h> /* strlen, strcpy */
#define SLENGTH 10
#define DIV "X"
void reverseWord(char word[], char reverse[]);
int main()
{
	char word[SLENGTH + 1], reverse[SLENGTH+1];
	char awesome[2*SLENGTH + 2];
	
	printf("enter a word with 3 letters> ");
	scanf("%s", word);
	
	printf("Word entered: %s\n", word);
	reverseWord(word, reverse);
	printf("Word reversed: %s\n", word);
	
	strcpy(awesome, word);
	strcpy(awesome, DIV);
	strcpy(awesome, reverse);
	printf("New word: %s\n", awesome);
	return 0;
}

void reverseWord(char word[], char reverse[])
{
	int length = strlen(word);
	reverse[length] = '\0';
	int i;
	for(i = 1; i<length-1; i++)
	{
		reverse[i-1] = word[length-1] 
	}
	printf("%d"); /* length = 3*/
}
