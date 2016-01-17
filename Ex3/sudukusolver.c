/**
* @file sudukusolver.c
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 10 Dec 2014
*
* @brief solving suduku
* A short program which is the main running logic to solve a suduku file
*
* @section LICENSE
* This program is a free software
*
* @section DESCRIPTION
*
* The main parts of the program are:
* Input	  : Running the program using the following command:
* 			sudukusolver <sudukuFile>
*
* Process : The program uses a generic DFS file named genericdfs.c in order to find
* and return the best node which represent the table which has been filled
* out the most - and if its value matches a solved suduku returns it as a solution
* no bad solutions could be returned since a node would not be build if it does not
* follow the suduku given logic
*
* Output  : informative error measeges prints out if anything bad happens, in case
* the program went through successfully it will print the suduku solution
*/


// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "genericdfs.h"
#include "sudukutree.h"

//-------------------------- const definitions --------------------------

/**
 * @def FILE_NAME 1
 * @brief A macro that sets the command place
 */
#define FILE_NAME 1

/**
* @def CORRECT_ARGUMENTS_NUM 2
* @brief A macro that sets the correct argument number
*/
#define CORRECT_ARGUMENTS_NUM 2

/**
* @def EXIT_PROGRAM_BAD_RUN 1
* @brief A macro that sets the bad run value to return in main
*/
#define EXIT_PROGRAM_BAD_RUN 1

/**
* @def EXIT_PROGRAM_GOOD_RUN 0
* @brief A macro that sets the good run value to return in main
*/
#define EXIT_PROGRAM_GOOD_RUN 0

//------------------------------ functions ------------------------------


/**
 * @brief Check if a given number is a full square
 * @param numberToCheck - the number to check
 * @return TRUE(1) if it is, FALSE(0) otherwise
 */
int isFullSquareNumber(double numberToCheck)
{
	return ((int)sqrt(numberToCheck) == (double)sqrt(numberToCheck));
}

/**
 * @brief checks if a row is a valid row in suduku
 * @param numberToCheck - the number currently checking
 * @param row - the row it was in
 * @param originialColumn - the column it was in
 * @param grid - the grid the number to check is on - to check on
 * @return TRUE(1) if it is, FALSE(0) otherwise
 */
int isRowValid(int numberToCheck, int row, int originialColumn, int** grid)
{
	int column;
	for (column = 0; column < gSudukuDimension; column++)
	{
		if (column != originialColumn)
		{
			if (numberToCheck == grid[row][column])
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

/**
 * @brief checks if a column is a valid column in suduku
 * @param numberToCheck - the number currently checking
 * @param originalRow - the row it was in
 * @param column - the column it was in
 * @param grid - the grid the number to check is on - to check on
 * @return TRUE(1) if it is, FALSE(0) otherwise
 */
int isColumnValid(int numberToCheck, int originalRow, int column, int** grid)
{
	int row;
	for (row = 0; row < gSudukuDimension; ++row)
	{
		if (row != originalRow)
		{
			if (numberToCheck == grid[row][column])
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

/**
 * @brief checks if a subgrid is a valid subgrid in suduku
 * @param numberToCheck - the number currently checking
 * @param originalRow - the row it was in
 * @param originalColumn - the column it was in
 * @param grid - the grid the number to check is on - to check on
 * @return TRUE(1) if it is, FALSE(0) otherwise
 */
int isSubGridValid(int numberToCheck, int originalRow, int originalColumn, int** grid)
{
	int subGridStartRow, subGridStartColumn;
	subGridStartRow = findStartingSubMatrix(originalRow);
	subGridStartColumn = findStartingSubMatrix(originalColumn);

	int row, column;
	for (row = 0; row < sqrt(gSudukuDimension); ++row)
	{
		for (column = 0; column < sqrt(gSudukuDimension); ++column)
		{
			if (((row + subGridStartRow) != originalRow) &&
				((column + subGridStartColumn) != originalColumn))
			{
				if (numberToCheck == grid[subGridStartRow + row][subGridStartColumn + column])
				{
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

/**
 * @brief checks if a given suduku grid is a valid for a single cell
 * @param numberToCheck - the number currently checking
 * @param row - the row it was in
 * @param column - the column it was in
 * @param grid - the grid the number to check is on - to check on
 * @return TRUE(1) if it is, FALSE(0) otherwise
 */
int isSudukuGridValid(int numberToCheck, int row, int column, int** grid)
{
	return (isRowValid(numberToCheck, row, column, grid)
			&& isColumnValid(numberToCheck, row, column, grid)
			&& isSubGridValid(numberToCheck, row, column, grid));
}

/**
 * @brief checks if a given suduku grid is a valid
 * @param sudukuGrid - the grid to check
 * @return TRUE(1) if it is, FALSE(0) otherwise
 */
int checkGridValidity(int** sudukuGrid)
{
	int row, column;
	for (row = 0; row < gSudukuDimension; row++)
	{
		for (column = 0; column < gSudukuDimension; column++)
		{
			// in case has nothing in it
			if (sudukuGrid[row][column] == EMPTY_SIGN)
			{
				continue;
			}
			// in case has a number in -
			// check if rest of grid is valid for that number in that place
			else if (!isSudukuGridValid(sudukuGrid[row][column], row, column, sudukuGrid))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

/**
 * @brief Check if a given file is null
 * @param file - a pointer to the file to check if null
 * @return True(1) if it is matching. False (0) if not.
 */
int isFileNull(FILE *file)
{
	if (file != NULL)
	{
		return FALSE;
	}
	return TRUE;
}

/**
 * @brief calc what is the value of a colved suduku grid for that size
 * @return the correct value for a solved suduku of that size
 */
int calcSolvedSudukuVal()
{
	return gSudukuDimension * gSudukuDimension * (gSudukuDimension + 1) / 2;
}

/**
 * @brief Check if a given digit is fitting for the suduku
 * @param digit - the number to check
 * @return True(1) if it is. False (0) if not.
 */
int checkDigit(int digit)
{
	if (digit < 0 || digit > gSudukuDimension)
	{
		return FALSE;
	}
	return TRUE;
}

/**
 * @brief free the memory of a given suduku grid
 * @param sudukuGrid - the grid to free
 */
void freeGridMemory(int** sudukuGrid)
{
	// frees from end to start all the grid's allocated memory
	int eraseIndex;
	for (eraseIndex = gSudukuDimension - 1; eraseIndex >= 0; eraseIndex--)
	{
		free(sudukuGrid[eraseIndex]);
		sudukuGrid[eraseIndex] = NULL;
	}
	free(sudukuGrid);
	sudukuGrid = NULL;
}

/**
 * @brief free the memory of a given suduku grid
 * @param sudukuGrid - the grid to free
 * @return
 */
int notValidSudukuFile(FILE *sudukuFile, int **sudukuGrid)
{
	fclose(sudukuFile);
	freeGridMemory(sudukuGrid);
	printf("<filename>: not a valid suduku file");
	return EXIT_PROGRAM_BAD_RUN;
}

/**
 * @brief This function prints out a suduku
 * @param sudukugrid - the grid of that suduku
 */
void printSudukuGrid(int** sudukugrid)
{
	// prints its size - than the representation of the grid
	printf("%d\n", gSudukuDimension);
	int row, column;
	for (row = 0; row < gSudukuDimension; row++)
	{
		for (column = 0; column < gSudukuDimension; column++)
		{
			// in case is in the end of a row
			if (column == gSudukuDimension - 1)
			{
				printf("%d", (sudukugrid)[row][column]);
			}
			else
			{
				printf("%d ", (sudukugrid)[row][column]);
			}
		}
		printf("\n");
	}
}

/**
 * @brief The main function which runs the project - calls the needed functions
 * in order to run the process solving the suduku
 * @param argc - given automatically when entering parameters when starting the program
 * @param argv - pointer to an array of chars - hold automatically the
 * params entered seperated by space
 * @return EXIT_PROGRAM_GOOD_RUN(0), tells the system execution ended without errors
 * Or EXIT_PROGRAM_BAD_RUN(1) otherwise.
 */
int main(int argc, char *argv[])
{
	// in case wrong amount of parameters entered
	if (argc != CORRECT_ARGUMENTS_NUM)
	{
		printf("please supply a file!\n");
		printf("usage: sudukusolver <filename>");
		return EXIT_PROGRAM_BAD_RUN;
	}

	// open file and check if is null
	FILE* sudukuFile = fopen(argv[FILE_NAME], "r");
	if (isFileNull(sudukuFile))
	{
		printf("<%s> no such file\n", argv[FILE_NAME]);
		return EXIT_PROGRAM_BAD_RUN;
	}

	// initializing parameters
	int** sudukuGrid = NULL;
	int gridSum = 0;

	// Check if the first paramter is correct and represents a correct
	// size for a suduku
	if ((fscanf(sudukuFile, "%d\n", &gSudukuDimension) != 1) || (gSudukuDimension <= 0) ||
		(!isFullSquareNumber((gSudukuDimension))))
	{
		printf("<filename>: not a valid suduku file");
		fclose(sudukuFile);
		sudukuFile = NULL;
		return EXIT_PROGRAM_BAD_RUN;
	}

	// allocating memory for a grid and fill it according to the file given
	sudukuGrid = allocateGridMemory(sudukuGrid);
	int row, column, currentNum;
	for (row = 0; row < gSudukuDimension; row++)
	{
		for (column = 0; column < gSudukuDimension; column++)
		{
			if (fscanf(sudukuFile, "%d ", &currentNum) == 1
				&& (checkDigit(currentNum)))
			{
				// insert the current num into the grid and add to the grid's sum
				sudukuGrid[row][column] = currentNum;
				gridSum += currentNum;

				// in case didn't end with '\n'
				if (column == (gSudukuDimension - 1) && fscanf(sudukuFile, "\n") != 0)
				{
					return notValidSudukuFile(sudukuFile, sudukuGrid);
				}
			}
			// in case wasn't an int
			else
			{
				return notValidSudukuFile(sudukuFile, sudukuGrid);
			}
		}
	}

	// finished working with file - check validity of the grid given
	if (!checkGridValidity(sudukuGrid))
	{
		return notValidSudukuFile(sudukuFile, sudukuGrid);
	}


	// calculate what is the value of a solved suduku and search for it using the
	// getBest of the generic dfs
	unsigned int solvedSudukuValue = calcSolvedSudukuVal();
	sudukuNode* head = newSudukuNode(gridSum, sudukuGrid);
	sudukuNode* best = (((sudukuNode*) getBest(head, (void*) getNodeChildren,
						(void*) getNodeVal, (void*) freeNode,
						(void*) copyNode, solvedSudukuValue)));

	// frees and closes the head grid and file we finished working with
	freeNode(head);
	head = NULL;
	freeGridMemory(sudukuGrid);
	sudukuGrid = NULL;
	fclose(sudukuFile);
	sudukuFile = NULL;
	// checks if the best node represents a solved suduku and return the proper answer
	if (best->sudukuGridValue != solvedSudukuValue)
	{

		freeNode(best);
		best = NULL;
		printf("no solution\n");
		return EXIT_PROGRAM_BAD_RUN;
	}
	else
	{
		printSudukuGrid(best->sudukuGrid);
		freeNode(best);
		best = NULL;
		return EXIT_PROGRAM_GOOD_RUN;
	}
}
