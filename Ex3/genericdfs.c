/**
 * @file genericdfs.c
 * @author ednussi <eran.nussinovitc@mail.huji.ac.il>
 * @version 1.0
 * @date 10 Dec 2014
 * @brief generic dfs contains the main used functions for a generic dfs
 * follows the required logic of the exrecise using the must functions
 */

// ------------------------------ includes ------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "genericdfs.h"

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

static pNode gBestNode = NULL; //global which is the best node
static int gFoundBestNode = FALSE; // global which holds if best node was found

//------------------------------ functions ------------------------------
/**
 * @brief getBest This function returns the node with the highest value in the tree, using
 * DFS algorithm.
 * @param head The head of the tree.
 * @param getChildren A function that gets a node and a pointer to an array of nodes.
 * The function allocates memory for an array of all the children of the node, populate it,
 * and returns it using the second parameter. The returned value is the number of children.
 * @param getVal A function that gets a node and returns its value, as int.
 * @param freeNode A function that frees a node from memory. This function will be called for each
 * node returned by getChildren.
 * @param copy A function that does a deep copy of a node.
 * @param best The highest possible value for a node. When the function encounters a node with that
 * value, it stops looking and returns it. If the best value can't be determined, pass
 * UINT_MAX (defined in limits.h) for that parameter.
 * @return The node with the highest value in the tree. In case of an error, or when all the nodes
 * in the tree have a value of zero, the returned node is NULL. If some nodes share the best value,
 * the function returns the first one it encounters.
 */
pNode getBest(pNode head, getNodeChildrenFunc getChildren,
			  getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{
	// check the value of the head given and compares it to the
	// best so far - update if better
	unsigned int headValue = getVal(head);
	if (gFoundBestNode != TRUE)
	{
		// in case has the value of the best requested pNode
		if (headValue == best)
		{
			freeNode(gBestNode);
			gBestNode = copy(head);
			gFoundBestNode = TRUE;
		}
		else
		{
			// in case its value is bigger than the best found so far
			if (headValue > getVal(gBestNode))
			{
				if (gBestNode != NULL)
				{
					freeNode(gBestNode);
				}
				gBestNode = copy(head);
			}
		}
	}

	// initialize pNode array and find out how many children the pNode has
	// and run thorugh them recursvely
	pNode* headChildren = NULL;
	int numberOfChildren = getChildren(head, &headChildren), child;
	for (child = 0; child < numberOfChildren; child++)
	{
		// run reccursion only in case hasn't found best node yet
		if (!gFoundBestNode)
		{
			getBest(headChildren[child], getChildren, getVal, freeNode, copy, best);

		}
		else
		{
			break;
		}
	}

	// free memory of all the children and the list and finally return the best node
	for (child = (numberOfChildren - 1); child >= 0; child--)
	{
		freeNode(headChildren[child]);
		headChildren[child] = NULL;
	}
	free(headChildren);
	headChildren = NULL;
	return gBestNode;
}
