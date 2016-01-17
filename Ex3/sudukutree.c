/**
* @file sudukutree.c
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 10 Dec 2014
* @brief sudku tree contains the main used function for a tree based suduku
*/

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sudukutree.h"
#include "genericdfs.h"

//------------------------------ functions ------------------------------

/**
 * @brief This function allocated memory for a grid used by suduku
 * @param grid suduku grid to be allocated
 * @return the pointer to the grid with the allocated memory
 */
int** allocateGridMemory(int** grid)
{
	grid = (int**)malloc(gSudukuDimension * sizeof(int*));
	int cell;
	for (cell = 0; cell < gSudukuDimension; cell++)
	{
		grid[cell] = (int*) malloc(gSudukuDimension * sizeof(int));
	}
	return grid;
}

/**
 * @brief This function creates a new suduku Node
 * @param gridValue the suduku's value
 * @param sudukuGrid the suduku's grid
 * @return the pointer to the new suduku Node
 */
sudukuNode* newSudukuNode(int gridValue, int** sudukuGrid)
{
	sudukuNode* suduku = (sudukuNode*) malloc(sizeof(sudukuNode));
	if (suduku != NULL)
	{
		suduku->sudukuGridValue = gridValue;
		suduku->sudukuGrid = allocateGridMemory(suduku->sudukuGrid);

		if (suduku->sudukuGrid != NULL)
		{
			int row, column;
			for (row = 0; row < gSudukuDimension; row++)
			{
				for (column = 0; column < gSudukuDimension; column++)
				{
					suduku->sudukuGrid[row][column] = sudukuGrid[row][column];
				}
			}
		}
	}
	return suduku;
}

/**
 * @brief This function finds the starting of a sub matrix in a grid
 * @param index the index to find it's starting submatrix
 * @return the starting of the index's sub matrix in the grid
 */
int findStartingSubMatrix(int index)
{
	return floor((index) / sqrt(gSudukuDimension))*sqrt(gSudukuDimension);
}

/**
 * @brief This function finds the possible values to assign to an empty cell in a suduku grid
 * doesn't returns anything but changes the array sent by switching off the values which
 * can't be used
 * @param possibleValues possibleValues - a binary array set to TRUE
 * @param possibleValues row - the row the empty cell is in
 * @param possibleValues column - the column the empty cell is in
 * @param possibleValues suduku - the suduku node itself
 */
void findPossibleValues(int **possibleValues, int row, int column, sudukuNode suduku)
{
	// row logic
	int runnerIndex, runnerIndex2;
	for (runnerIndex = 0; runnerIndex < gSudukuDimension; runnerIndex++)
	{
		if (suduku.sudukuGrid[row][runnerIndex] != EMPTY_SIGN)
		{
			(*possibleValues)[suduku.sudukuGrid[row][runnerIndex] - 1] = FALSE;
		}
	}

	// column logic
	for (runnerIndex = 0; runnerIndex < gSudukuDimension; runnerIndex++)
	{
		if (suduku.sudukuGrid[runnerIndex][column] != EMPTY_SIGN)
		{
			(*possibleValues)[suduku.sudukuGrid[runnerIndex][column] - 1] = FALSE;
		}
	}

	// submatrix logic
	int startingRowSubMatrix = findStartingSubMatrix(row), startingColumnSubMatrix =
							   findStartingSubMatrix(column);
	for (runnerIndex = 0; runnerIndex < sqrt(gSudukuDimension); runnerIndex++)
	{
		for (runnerIndex2 = 0; runnerIndex2 < sqrt(gSudukuDimension); runnerIndex2++)
		{
			if (suduku.sudukuGrid[startingRowSubMatrix + runnerIndex]
			    [startingColumnSubMatrix + runnerIndex2] != EMPTY_SIGN)
			{
				(*possibleValues)[suduku.sudukuGrid[startingRowSubMatrix + runnerIndex]
						                           [startingColumnSubMatrix + runnerIndex2] - 1]
						                           = FALSE;
			}
		}
	}
}

/**
 * @brief creates the children of a given node and populates them directly into
 * the given array. the fucntion allocates memory for the array and fill it up
 * with the kids - and returns how many they are.
 * @param node - the node we want his children
 * @param children - a pointer to a pointer to an array of sudukunodes to fill with the children
 * @return the number of children
 */
int getNodeChildren(sudukuNode* node, sudukuNode*** children)
{
	int numOfChildren = 0, row, column, value, initializingIndex;
	for (row = 0; row < gSudukuDimension; ++row)
	{
		for (column = 0; column < gSudukuDimension; ++column)
		{
			if (node->sudukuGrid[row][column] == EMPTY_SIGN)
			{
				// initialize a binary array of values
				int *possibleVals =  (int*) malloc(sizeof(int) * gSudukuDimension);
				for (initializingIndex = 0; initializingIndex < gSudukuDimension; initializingIndex++)
				{
					possibleVals[initializingIndex] = TRUE;
				}
				findPossibleValues(&possibleVals, row, column, (*node));

				// find how many children that node has - and allocate memory of proper size
				int sumOfChilds = 0;
				for (initializingIndex = 0; initializingIndex < gSudukuDimension; initializingIndex++)
				{
					if (possibleVals[initializingIndex] == TRUE)
					{
						sumOfChilds++;
					}
				}
				(*children) = (sudukuNode**)malloc(sumOfChilds * sizeof(sudukuNode*));

				// create the children of the node by copying the node and chainging the proper value
				for (value = 1; value <= gSudukuDimension; value++)
				{
					if (possibleVals[value -1] != FALSE)
					{
						// increase size of array and put the new child with the replacement of zero
						numOfChildren++;
						(*children)[numOfChildren - 1] = copyNode(node);
						(*children)[numOfChildren - 1]->sudukuGrid[row][column] = value;
						(*children)[numOfChildren - 1]->sudukuGridValue += value;
					}
				}
				free(possibleVals);
				possibleVals = NULL;
				return numOfChildren;
			}
		}
	}
	return numOfChildren;
}

/**
 * @brief gets the node's value
 * @param node - the node we want his value
 * @return the nod's value
 */
unsigned int getNodeVal(sudukuNode *node)
{
	if (node != NULL)
	{
		return node->sudukuGridValue;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief free a suduku node from memory which was allocated to
 * @param nodeToFree - the node we want free
 */
void freeNode(sudukuNode *nodeToFree)
{
	// frees each section within the grid
	int cell;
	for (cell = gSudukuDimension - 1; cell >= 0; cell--)
	{
		free((nodeToFree->sudukuGrid)[cell]);
	}

	// frees the grid iteslf
	free(nodeToFree->sudukuGrid);
	nodeToFree->sudukuGrid = NULL;

	//frees the node himself
	free(nodeToFree);
	nodeToFree = NULL;
}

/**
 * @brief copies a suduku node
 * @param nodeToCopy - a pointer to the node we want to copy
 * @return a pointer to the new copied node
 */
sudukuNode* copyNode(sudukuNode *nodeToCopy)
{
	return newSudukuNode(nodeToCopy->sudukuGridValue, nodeToCopy->sudukuGrid);
}
