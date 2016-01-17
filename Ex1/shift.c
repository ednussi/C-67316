/**
* @file shift.c
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 4 Nov 2014
*
* @brief The system encrypts or decrypts according to the user's choice
* the entered text.
*
* @section LICENSE
* This program is a free software
*
* @section DESCRIPTION
* The system encrypts (clockwise) or decrypts (counter clockwise) text 
* using a closed scope for numbers, lowercase english characters and
* uppercase english charaters - by their ASCII representation.
* Input	  : shift amount - A number between 0-25
*			'd' - for decrypt | 'e' - for encrypt
*			text to convert - up to 100 chars
* Process : 1. Asks for a the shift number and awaits entery
*			2. Asks for letter 'd' or 'e' for decrypt or encrypt
*			in coralation, and awaits entery.
*			3. Awaits to text to be entered
* 			Repets untill EOF sign or termination by user
* Output  : After enetering the text prints in the next row its
* requested action - encrypted or decrypted.
*/


// ------------------------------ includes ------------------------------
#include <stdio.h>

//-------------------------- const definitions --------------------------

/**
* @def STARTING_ASCII_VALUE_OF_NUMBERS '0'
* @brief A macro that sets the starting ascii value of numbers
*/
#define STARTING_ASCII_VALUE_OF_NUMBERS '0'

/**
* @def ENDING_ASCII_VALUE_OF_NUMBERS '9'
* @brief A macro that sets the ending ascii value of numbers
*/
#define ENDING_ASCII_VALUE_OF_NUMBERS '9'

/**
* @def STARTING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS 'A'
* @brief A macro that sets the starting ascii value of uppercase chars
*/
#define STARTING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS 'A'

/**
* @def ENDING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS 'Z'
* @brief A macro that sets the ending ascii value of uppercase chars
*/
#define ENDING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS 'Z'

/**
* @def STARTING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS 'a'
* @brief A macro that sets the starting ascii value of uppercase chars
*/
#define STARTING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS 'a'

/**
* @def ENDING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS 'z'
* @brief A macro that sets the ending ascii value of uppercase chars
*/
#define ENDING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS 'z'

/**
* @def NUMBERS_RANGE 10
* @brief A macro that sets the range of numbers
*/
#define NUMBERS_RANGE 10

/**
* @def NUMBERS_RANGE 26
* @brief A macro that sets the range of english letters
*/
#define ENGLISH_LETTERS_RANGE 26

/**
* @def DEFAULT_ACTION_CHAR 'a'
* @brief A macro that sets the default asction char
*/
#define DEFAULT_ACTION_CHAR 'a'

/**
* @def DEFAULT_SHIFT -1
* @brief A macro that sets the default shift amount
*/
#define DEFAULT_SHIFT -1

/**
* @def DEFAULT_MAX_SHIFT 25
* @brief A macro that sets the max shift
*/
#define MAX_SHIFT 25

/**
* @def DEFAULT_MIN_SHIFT 0
* @brief A macro that sets the min shift
*/
#define MIN_SHIFT 0 

/**
* @def ENCRYPT 'a'
* @brief A macro that sets the encrypt sign
*/
#define ENCRYPT 'e'

/**
* @def DECRYPT 'a'
* @brief A macro that sets the decrypt sign
*/
#define DECRYPT 'd'

/**
* @def TURE 1
* @brief A macro that sets a true flag
*/
#define TRUE 1

/**
* @def FALSE 0
* @brief A macro that sets a flase flag
*/
#define FALSE 0

/**
* @def DEFAULT_STARTING_ASCII_VALUE 0
* @brief A macro that sets an initial starting ascii value
*/
#define DEFAULT_STARTING_ASCII_VALUE 0

/**
* @def DEFAULT_RANGE 0
* @brief A macro that sets a default range
*/
#define DEFAULT_RANGE 10

/**
* @def DEFAULT_ENDING_ASCII_VALUE 255
* @brief A macro that sets an initial starting ascii value
*/
#define DEFAULT_ENDING_ASCII_VALUE 255

//------------------------------ functions ------------------------------

/**
 * @brief Checks if a given character is a number
 * by its Ascii value.
 * @param c - the Char to check
 * @return True(1) if it is. False (0) if not.
 */
int isNumber(char c)
{
	if ((c >= STARTING_ASCII_VALUE_OF_NUMBERS) && (c <= ENDING_ASCII_VALUE_OF_NUMBERS))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

/**
 * @brief Checks if a given character is an uppercase english char
 * by its Ascii value.
 * @param c - the Char to check
 * @return True(1) if it is. False (0) if not.
 */
int isUppercase(char c)
{
	if ((c >= STARTING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS) && 
		(c <= ENDING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

/**
 * @brief Checks if a given character is an lowercase english char
 * by its Ascii value.
 * @param c - the Char to check
 * @return True(1) if it is. False (0) if not.
 */
int isLowercase(char c)
{
	if ((c >= STARTING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS) && 
		(c <= ENDING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

/**
 * @brief Checks if a given character is an english char
 * by its Ascii value.
 * @param c - the Char to check
 * @return True(1) if it is. False (0) if not.
 */
int isEnglishLetter(char c)
{
	if (isLowercase(c) || isUppercase(c))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

/**
 * @brief Encrypts a given character by a given shift
 * for its Ascii value. Keeps the scope range for each time
 * in a loop.
 * e.g. encrypt(2, 'a') = 'c'
 *		encrypt(12, 4) = 6
 * @param shift - the shift amount
 * @param c - the char to encrypt
 * @return The encrypted char
 */
char encrypt(int shift, char c)
{
	// Local variables:
	int startingAsciiValue = DEFAULT_STARTING_ASCII_VALUE;
	int rangeOfAsciiGroup = DEFAULT_RANGE;

	if (isNumber(c))
	{
		startingAsciiValue = STARTING_ASCII_VALUE_OF_NUMBERS;
		rangeOfAsciiGroup = NUMBERS_RANGE;
	}
	else if (isEnglishLetter(c))
	{
		if (isUppercase(c))
		{
			startingAsciiValue = STARTING_ASCII_VALUE_OF_UPPERCASE_CHARACTERS;
		}
		else
		{
			startingAsciiValue = STARTING_ASCII_VALUE_OF_LOWERCASE_CHARACTERS;
		}
		rangeOfAsciiGroup = ENGLISH_LETTERS_RANGE;
	}
	else
	{
		return c;
	}
	// in case was one of the corresponding group
	// calculate the differnce to the charater - within the parenthesis
	// and add to the starting Ascii value of the proper group
	return startingAsciiValue + ((c + shift - startingAsciiValue) % rangeOfAsciiGroup);
}

/**
 * @brief Decrypts a given character by a given shift
 * for its Ascii value. Keeps the scope range for each time
 * in a loop.
 * e.g. decrypt(1, 'A') = 'Z'
 *		decrypt(12, 2) = 0
 * @param shift - the shift amount
 * @param c - the char to decrypt
 * @return The decrypted char
 */
char decrypt(int shift, char c)
{
	// In order to avoid code repetation uses encrypt calculation
	// to return the proper decrypted correponding character
	if (isNumber(c))
	{
		return encrypt(NUMBERS_RANGE -(shift) % NUMBERS_RANGE, c);
	}
	else if (isEnglishLetter(c))
	{
		return encrypt(ENGLISH_LETTERS_RANGE - shift, c);
	}
	else
	{
		return c;
	}
}

/**
 * @brief The main function. Runs the enternal loops which asks
 * the user for the proper inputs and accordingly uses encrypt or decrypt
 * to do as asked on the entered text.
 * return 0, tells the system execution ended without errors.
 */
int main()
{
	// Local variables:
	int shift = DEFAULT_SHIFT;
	char requestedAction = DEFAULT_ACTION_CHAR;
	char (*cryptFunction)(int, char); 
	char currentChar;

	while ((shift > MAX_SHIFT) || (shift < MIN_SHIFT))
	{
		printf("please enter the shift:\n");
		scanf(" %d", &shift);
	}

	while ((requestedAction != ENCRYPT) && (requestedAction != DECRYPT))
	{
		printf("would you like to encrypt (e) or decrypt (d)?\n");
		scanf(" %c%*1[\n]", &requestedAction);
	}

	// change the function pointer to the appropriate function
	switch (requestedAction)
	{
		case ENCRYPT:
			cryptFunction = &encrypt;
			break;
		case DECRYPT:
			cryptFunction = &decrypt;
			break;
	}

	while ((currentChar = getchar()) != EOF)
	{
		putchar(cryptFunction(shift, currentChar));

	}

	printf("\n");
	return 0;
}