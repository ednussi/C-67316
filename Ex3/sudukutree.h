/**
* @file sudukutree.h
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 10 Dec 2014
* @brief a header file used by sudukutree.c & sudukusolver.c
* contains main functions both files require
*/

#ifndef SUDUKUTREE_H_
#define SUDUKUTREE_H_

//-------------------------- const definitions --------------------------

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
* @def EMPTY_SIGN 0
* @brief A macro that sets empty sign in a suduku
*/
#define EMPTY_SIGN 0

int gSudukuDimension; //global - what is the suduku size NxN

/**
 * @brief typdef of a new struc named sudukuNode
 * unsigned int - sudukuGridValue: the grid which represents the suduku
 * int - **sudukuGrid: the value of that grid
 * the grid's value is logically Defined as the sum of all the filled cells in the grid
 * Parameters arranged in a matter that no memory loss would happen
 * due to bad order of initialized inner variables in the structure
 */
typedef struct sudukuNode
{
	unsigned int sudukuGridValue;
	int **sudukuGrid;
} sudukuNode;

//------------------------------ functions ------------------------------

/**
 * @brief creates the children of a given node and populates them directly into
 * the given array. the fucntion allocates memory for the array and fill it up
 * with the kids - and returns how many they are.
 * @param node - the node we want his children
 * @param children - a pointer to a pointer to an array of sudukunodes to fill with the children
 * @return the number of children
 */
int getNodeChildren(sudukuNode* node, sudukuNode*** pNode);

/**
 * @brief This function allocated memory for a grid used by suduku
 * @param grid suduku grid to be allocated
 * @return the pointer to the grid with the allocated memory
 */
int** allocateGridMemory(int** grid);

/**
 * @brief This function creates a new suduku Node
 * @param gridValue the suduku's value
 * @param sudukuGrid the suduku's grid
 * @return the pointer to the new suduku Node
 */
sudukuNode* newSudukuNode(int gridSummary, int** sudukuTable);

/**
 * @brief gets the node's value
 * @param node - the node we want his value
 * @return the nod's value
 */
unsigned int getNodeVal(sudukuNode *node);

/**
 * @brief free a suduku node from memory which was allocated to
 * @param node - the node we want free
 */
void freeNode(sudukuNode *node);

/**
 * @brief copies a suduku node
 * @param nodeToCopy - a pointer to the node we want to copy
 * @return a pointer to the new copied node
 */
sudukuNode* copyNode(sudukuNode* node);

/**
 * @brief This function finds the starting of a sub matrix in a grid
 * @param index the index to find it's starting submatrix
 * @return the starting of the index's sub matrix in the grid
 */
int findStartingSubMatrix(int index);

#endif /* SUDUKUTREE_H_ */

