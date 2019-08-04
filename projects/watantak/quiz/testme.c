/*********************************************************************************************************************************
** Program name: CS362 Summer 2019 Random Testing Quiz (testme)
** Author: Takahiro Watanabe
** Date: 07/23/19
** Description: This program implements the random testing for the testme() function in testme.c file. 
**              It generates inputs randomly then prints an error message and exits once meeting the error condition.
** Source: <Title> How to generate random number from a given set of values?
**         <Author> progrenhard 
**         <Date of Retrieval> 07/23/19
**         <Availability> https://stackoverflow.com/questions/24809443/how-to-generate-random-number-from-a-given-set-of-values
*********************************************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


// inputChar() function returns a character and accepts no parameter
char inputChar()
{
	// randomly generate a character to input
	// the input pool includes every printing character in the ASCII code.
    return (rand() % (126 - 32 + 1)) + 32;
}

// I modified the setting of inputString() function.
// Now it accepts the C-string as a parameter and returns nothing (void function)
void inputString(char testStr[])
{
	// the input pool includes only the letters used the target statement
	int target[4] = {101, 114, 115, 116};
	int targetIndx;

	// randomly generates the string of 5 characters (fixed length)
	for (int i = 0; i < 5; i++)
	{
		targetIndx = rand() % 4;
		testStr[i] = target[targetIndx];
	}

	// insert the null terminator at the end of the string
	testStr[5] = 0;
}

void testme()
{
  int tcCount = 0;
  char s[6];	// declared the C-string as an array of character instead of a pointer to char
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    inputString(s);		// the function is modified and called with the C-string as an argument
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("\nError! Exiting the program...\n\n");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
