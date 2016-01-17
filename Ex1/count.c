/**
* @file count.c
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 4 Nov 2014
*
* @brief System to count the number of characters, words, and lines
* in an entered text.
*
* @section LICENSE
* This program is a free software
*
* @section DESCRIPTION
* The system counts the number of characters, words, and lines
* in an entered text.
* Input	  : Text to be examined.
* Process : Starting with the first line, counts any increasement of line
* word or entered character.
* Output  : 3 numbers seperated by space referring to the number
* of characters, words and lines in corlation.
*/


// ------------------------------ includes ------------------------------
#include <stdio.h>

//-------------------------- const definitions --------------------------

/**
* @def STARTING_CHARS_NUM 0
* @brief A macro that sets the starting number of characters to count from
*/
#define STARTING_CHARS_NUM 0

/**
* @def STARTING_WORDS_NUM 0
* @brief A macro that sets the starting number of words to count from
*/
#define STARTING_WORDS_NUM 0

/**
* @def STARTING_LINES_NUM 0
* @brief A macro that sets the starting number of lines to count from
*/
#define STARTING_LINES_NUM 1

/**
* @def END_OF_LINE '\n'
* @brief A macro that sets the end of line corresponding integer
*/
#define END_OF_LINE '\n'

/**
* @def SPACE ' '
* @brief A macro that sets the space corresponding integer
*/
#define SPACE ' '

/**
* @def DEFAULT_LAST_CHARACTER ' '
* @brief A macro that sets the defaulted last character
*/
#define DEFAULT_LAST_CHAR SPACE

//------------------------------ functions ------------------------------

/**
 * @brief The main function. Runs the enternal loop which runs over
 * the entered text and counts the characters, words and lines.
 * return 0, tells the system execution ended without errors.
 */
int main()
{

	// Local variables:
	int numOfChars = STARTING_CHARS_NUM;
	int numOfWords = STARTING_WORDS_NUM;
	int numOfLines = STARTING_LINES_NUM;
	int lastCharacter = DEFAULT_LAST_CHAR;
	char currentCharacter;

	while ((currentCharacter = getchar()) != EOF)
	{
		numOfChars++;

		if (currentCharacter == END_OF_LINE)
		{
			numOfLines++;
		}
		else if (currentCharacter != SPACE)
		{
			if ((lastCharacter == SPACE) || (lastCharacter == END_OF_LINE))
			{
				numOfWords++;
			}
		}

		lastCharacter = currentCharacter;
	}
	printf("%d %d %d", numOfChars, numOfWords, numOfLines);
	return 0;
}

