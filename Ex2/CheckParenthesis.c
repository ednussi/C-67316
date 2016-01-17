/**
* @file CheckParenthesis.c
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 17 Nov 2014
*
* @brief The system runs a simple check for the correct
* usage of parenthesis within a text file.
*
* @section LICENSE
* This program is a free software
*
* @section DESCRIPTION
*
* The system runs a simple check for the correct
* usage of parenthesis within a text file.
* Input	  : A file name - of the file to check.
* 			Running the program using the command:
* 			CheckParenthesis <filename>
* Process : Using a Stack and the logic of:
* 			1. parenthesis can hold within other parenthesis
* 			2. If a close bracket apper he's opener must be the last
* 			   one that was used
* 			3. you may not leave an open barcket of any kind
* 			Check with the stack the parenthesis of the file.
* Output  : Prints ok if the file holds through the test -
* 			or bad structure otherwise
*/

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//-------------------------- const definitions --------------------------
/**
* @def SORUCE_FILE 1
* @brief A macro that sets the place of the source file
*/
#define SORUCE_FILE 1

/**
* @def ROUND_OPEN_BRACKET '('
* @brief A macro that sets round open bracket
*/
#define ROUND_OPEN_BRACKET '('

/**
* @def ROUND_CLOSE_BRACKET ')'
* @brief A macro that sets round close bracket
*/
#define ROUND_CLOSE_BRACKET ')'

/**
* @def CURLED_OPEN_BRACKET '{'
* @brief A macro that sets curled open bracket
*/
#define CURLED_OPEN_BRACKET '{'

/**
* @def CURLED_CLOSE_BRACKET '}'
* @brief A macro that sets curled closed bracket
*/
#define CURLED_CLOSE_BRACKET '}'

/**
* @def SQUARE_OPEN_BRACKET '['
* @brief A macro that sets square open bracket
*/
#define SQUARE_OPEN_BRACKET '['

/**
* @def SQUARE_CLOSE_BRACKET ']'
* @brief A macro that sets square close bracket
*/
#define SQUARE_CLOSE_BRACKET ']'

/**
* @def SIGN_OPEN_BRACKET '<'
* @brief A macro that sets sign open bracket
*/
#define SIGN_OPEN_BRACKET '<'

/**
* @def SIGN_CLOSE_BRACKET '>'
* @brief A macro that sets sign close bracket
*/
#define SIGN_CLOSE_BRACKET '>'

/**
* @def TRUE 1
* @brief A macro that sets the true value
*/
#define TRUE 1

/**
* @def FALSE 0
* @brief A macro that sets the false value
*/
#define FALSE 0

/**
* @def MAX_STACK_SIZE 5000
* @brief A macro that sets the max stack size
*/
#define MAX_STACK_SIZE 5000

/**
* @def EMPTY_STACK 0
* @brief A macro that sets the empty stack amount
*/
#define EMPTY_STACK 0

/**
* @def CORRECT_ARGUMENTS_NUM 2
* @brief A macro that sets the correct argument number
*/
#define CORRECT_ARGUMENTS_NUM 2

//------------------------------ functions ------------------------------

/**
 * @brief The defination of a new struct Stack
 * brackets - a char array which contains all of the entered brackets by LIFO
 * totalNumOfBrackets - an int summing all of the brackets within the array
 */
typedef struct
{
	char barckets[MAX_STACK_SIZE];
	int totalNumOfBrackets;
} Stack;

// Craeting Of the Global Variables
static Stack gBracketsStack;

/**
 * @brief Pushes the given bracket into the stack
 * @param bracket - the bracket char to push
 */
void push(char bracket)
{
	//in case Stack is full
	if (gBracketsStack.totalNumOfBrackets == MAX_STACK_SIZE)
	{
		exit(1);
	}
	gBracketsStack.barckets[gBracketsStack.totalNumOfBrackets] = bracket;
	gBracketsStack.totalNumOfBrackets++;
}

/**
 * @brief Check if the stack is empty
 * @return True(1) if it is. False (0) if not.
 */
int isEmpty()
{
	if (gBracketsStack.totalNumOfBrackets != EMPTY_STACK)
	{
		return FALSE;
	}
	return TRUE;
}

/**
 * @brief Pops the last entered item into the stack
 * @return The last entered bracket into the stack
 */
char pop()
{
	if (isEmpty())
	{
		printf("Bad structure\n");
		exit(1);

	}
	char popedBracket;
	gBracketsStack.totalNumOfBrackets--;
	popedBracket = gBracketsStack.barckets[gBracketsStack.totalNumOfBrackets];
	return popedBracket;
}

/**
 * @brief Check if a given char is an open bracket
 * @param bracket - the bracket to check
 * @return True(1) if it is matching. False (0) if not.
 */
int isOpenBarcket(char barcket)
{
	if (barcket == ROUND_OPEN_BRACKET || barcket == CURLED_OPEN_BRACKET ||
		barcket == SQUARE_OPEN_BRACKET || barcket == SIGN_OPEN_BRACKET)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
 * @brief Runs through a file and counts the amount of total brackets and
 * that witholds a correct structure
 * @param sourceFile - A file pointer to the file which contains the text to be checked
 * @return True(1) if it holds. False (0) if not.
 */
int countBrackets(FILE *sourceFile)
{
	char currentChar;

	while ((currentChar = fgetc(sourceFile)) != EOF)
	{
		if (isOpenBarcket(currentChar))
		{
			push(currentChar);
		}
		else
		{
			// If matches one the closed brackets signs - checks if the last
			// one to be entered to the stack was his matching open counterpart.
			switch (currentChar)
			{
				case ROUND_CLOSE_BRACKET:
					if (pop() != ROUND_OPEN_BRACKET)
					{
						return FALSE;
					}
					break;
				case CURLED_CLOSE_BRACKET:
					if (pop() != CURLED_OPEN_BRACKET)
					{
						return FALSE;
					}
					break;
				case SQUARE_CLOSE_BRACKET:
					if (pop() != SQUARE_OPEN_BRACKET)
					{
						return FALSE;
					}
					break;
				case SIGN_CLOSE_BRACKET:
					if (pop() != SIGN_OPEN_BRACKET)
					{
						return FALSE;
					}
					break;
			}

		}
	}

	//Checks Stack is empty and all brackets were matched
	if (isEmpty())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
 * @brief Runs initial validation of the entered command
 * @param argc - an int - amount of args inserted in
 */
void initialValidation(int argc)
{
	if (argc != CORRECT_ARGUMENTS_NUM)
	{
		printf("please supply a file!\nusage:CheckParenthesis <filename>\n");
		exit(1);
	}
}

/**
 * @brief The main function which runs the project - calls the needed functions
 * in order to check a utalize the process of checking the file for the right
 * parenthesis structure.
 * @param argc - given automatically when entering parameters when starting the program
 * @param argv - pointer to an array of chars - hold automatically the
 * params entered seperated by space
 * @return 0, tells the system execution ended without errors
 * Or 1 otherwise.
 */
int main(int argc, char *argv[])
{
	initialValidation(argc);
	FILE *sourceFile = fopen(argv[SORUCE_FILE], "r");
	if (sourceFile == NULL)
	{
		printf("file \"%s\" not found\n", argv[SORUCE_FILE]); //matching school solution
		return 1;
	}
	gBracketsStack.totalNumOfBrackets = EMPTY_STACK;
	if (countBrackets(sourceFile) == TRUE)
	{
		printf("Ok\n");
	}
	else
	{
		printf("Bad structure\n");
		return 1;
	}
	fclose(sourceFile);
	sourceFile = NULL;
	return 0;
}
