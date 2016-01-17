/**
* @file waredb.c
* @author ednussi <eran.nussinovitc@mail.huji.ac.il>
* @version 1.0
* @date 17 Nov 2014
*
* @brief Managing a data base.
* A short program which enables the user to receive, send and clean
* a database using the exercise logics.
*
* @section LICENSE
* This program is a free software
*
* @section DESCRIPTION
*
* The system has 3 ways of working supporsting all the 3 mentioned
* commands
* Input	  : Running the program using the following command:
* 			waredb <dbfile> <command> <command argsfile>
* Process : For each operation runs through the program - build the
* initial storage house and cleans / adds / sends product out of it
* using bsearch and qsort of the given exrecise logic
* Output  : informative error prints if anything bad happened, in case
* the program went through successfully will change the db file by the
* requested command
*/

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//-------------------------- const definitions --------------------------
/**
* @def DB_FILE 1
* @brief A macro that sets the db file place
*/
#define DB_FILE 1

/**
* @def COMMAND 2
* @brief A macro that sets the command place
*/
#define COMMAND 2

/**
* @def COMMAND_ARGS_FILE 3
* @brief A macro that sets the command args file place
*/
#define COMMAND_ARGS_FILE 3

/**
* @def DATE 3
* @brief A macro that sets the date place
*/
#define DATE 3

/**
* @def RECEIVED_COMMAND "received"
* @brief A macro that sets the received command
*/
#define RECEIVED_COMMAND "received"

/**
* @def CLEAN_COMMAND "clean"
* @brief A macro that sets the clean command
*/
#define CLEAN_COMMAND "clean"

/**
* @def SENT_COMMAND "sent"
* @brief A macro that sets the sent command
*/
#define SENT_COMMAND "sent"

/**
* @def MAX_COMMAND_SIZE 9
* @brief A macro that sets the maximum command size
*/
#define MAX_COMMAND_SIZE 9

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
* @def THE_SAME 0
* @brief A macro that sets TRUE for strcmp
*/
#define THE_SAME 0

/**
* @def CORRECT_ARGUMENTS_NUM 4
* @brief A macro that sets the correct argument number
*/
#define CORRECT_ARGUMENTS_NUM 4

/**
* @def CORRECT_DATE_ARGUMENTS_NUM 2
* @brief A macro that sets the correct argument number
*/
#define CORRECT_DATE_ARGUMENTS_NUM 2

/**
* @def CORRECT_PRODUCT_ARGUMENTS_NUM 5
* @brief A macro that sets the correct argument number
*/
#define CORRECT_PRODUCT_ARGUMENTS_NUM 5

/**
* @def FLOAT_SIZE 16
* @brief A macro that sets the float size
*/
#define FLOAT_SIZE 16

/**
* @def DEFAULT_LINE_SIZE 55
* @brief A macro that sets the default line size
*/
#define DEFAULT_LINE_SIZE 55

/**
* @def WAREHOUSE_CAPACITY 2000
* @brief A macro that sets the warehouse capacity
*/
#define WAREHOUSE_CAPACITY 2000

/**
* @def MAX_NAME_LENGTH 21
* @brief A macro that sets the maximum name length
*/
#define MAX_NAME_LENGTH 21

/**
* @def RUN_OUT_ACCURACY 0.001
* @brief A macro that sets the run out accuracy precision
*/
#define RUN_OUT_ACCURACY 0.001f

/**
* @def RUN_OUT_OF_PRODUCT -1
* @brief A macro that sets the run out of product sign
*/
#define RUN_OUT_OF_PRODUCT -1

/**
* @def MIN_MONTH 1
* @brief A macro that sets the minimum month
*/
#define MIN_MONTH 0

/**
* @def MAX_MONTH 12
* @brief A macro that sets the maximum month
*/
#define MAX_MONTH 12

/**
* @def PRODUCT1_IS_BIGGER 1
* @brief A macro that sets the product1 is bigger sign
*/
#define PRODUCT1_IS_BIGGER 1

/**
* @def PRODUCT1_IS_BIGGER 1
* @brief A macro that sets the product2 is bigger sign
*/
#define PRODUCT2_IS_BIGGER -1

/**
* @def IGNORE_MONTHS_IN_CHECK 0
* @brief A macro that sets the ignore months in check sign
*/
#define IGNORE_MONTHS_IN_CHECK 0

/**
* @def AVOID_CHECKING_EXPIRED_PRODUCTS 0
* @brief A macro that sets the avoid checking expired products sign
*/
#define AVOID_CHECKING_EXPIRED_PRODUCTS 0

/**
* @def MINIMUM_AMOUNT_OF_PRODUCT 0.0f
* @brief A macro that sets the minimum amount of product
*/
#define MINIMUM_AMOUNT_OF_PRODUCT 0.0f

/**
* @def INITIAIZED_REMAINNING_DIFFERENCE 0.0f
* @brief A macro that sets the initialized remainning differenece
*/
#define INITIAIZED_REMAINNING_DIFFERENCE 0.0f

/**
* @def BARCODE_LENGTH 4
* @brief A macro that sets the barcode length
*/
#define BARCODE_LENGTH 4

/**
* @def SEPERATION_TAB 4
* @brief A macro that sets the seperation tab place
*/
#define SEPERATION_TAB 4

/**
* @def TAB_SIGN '\t'
* @brief A macro that sets the tab sign
*/
#define TAB_SIGN '\t'

/**
* @def DECIMEL_POINT '.'
* @brief A macro that sets the decimel point sign
*/
#define DECIMEL_POINT '.'

/**
* @def NO_DECIMEL_POINTS 0
* @brief A macro that sets the no decimel points num
*/
#define NO_DECIMEL_POINTS 0

/**
* @def WANTED_AMOUNT 5
* @brief A macro that sets the wanted amount place
*/
#define WANTED_AMOUNT 5

/**
* @def ONE_ARGUMENT 1
* @brief A macro that sets the one argument sign
*/
#define ONE_ARGUMENT 1

/**
* @def NEGATIVE_SIGN_PLACE 0
* @brief A macro that sets the negative sign place
*/
#define NEGATIVE_SIGN_PLACE 0

/**
* @def EMPTY_WAREHOUSE 0
* @brief A macro that sets the empty warehouse initial amount
*/
#define EMPTY_WAREHOUSE 0

//------------------------------ functions ------------------------------

/**
 * @brief The defination of a new struct ExpirationDate
 * year - an int for exipration year
 * month - an int for exipration month
 */
typedef struct
{
	int year;
	int month;
} ExpirationDate;

/**
 * @brief The defination of a new struct Product
 * inInventory - a float for quantity of the product in stock
 * expiration - an ExpirationDate for the expiration date of the product
 * barcode - a 4 digits int for the product's barcode
 * name - a char array for the product's name
 *
 * Parameters arranges in a matter that no memory loss would happen
 * due to bad order of initalized inner variables in the strutcture
 */
typedef struct
{
	float inInventory;
	ExpirationDate expiration;
	int barcode;
	char name[MAX_NAME_LENGTH];
} Product;

/**
 * @brief typdef to be used as a casting for the
 * comparator function.
 */
typedef int (*compfn)(const void*, const void*);

// Craeting Of the Global Variables
static int gNumOfProducts = EMPTY_WAREHOUSE;
static Product gWarehouse[WAREHOUSE_CAPACITY];

/**
 * @brief Check if a given file is empty
 * @param file - a pointer to the file to check if empty
 * @return True(1) if it is matching. False (0) if not.
 */
int isFileEmpty(FILE *file)
{
	long savedOffset = ftell(file);
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0)
	{
		return TRUE;
	}
	fseek(file, savedOffset, SEEK_SET);
	return FALSE;
}

/**
 * @brief Check if a given command is valid
 * @param command - a char array holding the command
 * @return True(1) if it is matching. False (0) if not.
 */
int validCommandCheck(const char command[])
{
	if (strcmp(command, RECEIVED_COMMAND) == THE_SAME ||
		strcmp(command, CLEAN_COMMAND) == THE_SAME  ||
		strcmp(command, SENT_COMMAND) == THE_SAME)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
 * @brief Check if a given month is iwthin months range
 * @param month - an int - the month to check
 * @return True(1) if it is matching. False (0) if not.
 */
int monthCheck(const int month)
{
	if (month < MIN_MONTH || month > MAX_MONTH)
	{
		return FALSE;
	}
	return TRUE;
}

/**
 * @brief Check some initial validation of the command entered:
 * Checks for correct arguments amount, for correct usage and readability
 * of provided files.
 * @param argc - amount of parameters entered
 * @param argv - pointer to char array which holds the command parts
 */
void initialValidation(int argc, char* argv[])
{
	//In case incorrent number of parametrs or unknown command
	if (argc != CORRECT_ARGUMENTS_NUM || validCommandCheck(argv[COMMAND]) == FALSE)
	{
		printf("USAGE: waredb <db file> <command> <command arg file>\n");
		exit(1);
	}

	//Clean command date checks
	if (strcmp(CLEAN_COMMAND, argv[COMMAND]) == THE_SAME)
	{
		int expirationYear, expirationMonth;
	    if (sscanf(argv[DATE], " %d-%d", &expirationYear, &expirationMonth) ==
	    	CORRECT_DATE_ARGUMENTS_NUM)
	    {
	    	//In case received a negative year in clean (supporting school solution) or bad month
	    	if (monthCheck(expirationMonth) == FALSE || !isdigit(argv[DATE][NEGATIVE_SIGN_PLACE]))
	    	{
				printf("USAGE: waredb <db file> <command> <command arg file>\n");
				exit(1);
	    	}
	    }
	    else
	    {
	    	printf("USAGE: waredb <db file> <command> <command arg file>\n");
	    	exit(1);
	    }
	}

	//Checking file is there and readable
	FILE *dbFile = fopen(argv[DB_FILE], "r");
	if (dbFile == NULL)
	{
		printf("%s: no such file\n", argv[DB_FILE]);
		exit(1);
	}
	fclose(dbFile);
	dbFile = NULL;
}

/**
 * @brief Creates a new ExiprationDate typed item with given year and month
 * @param year - year to be entered into the new ExiprationDate
 * @param month - month to be entered into the new ExiprationDate
 * @return An ExiprationDate with initialized paramters as given
 */
ExpirationDate newExpirationDate(const int year, const int month)
{
	ExpirationDate expirationDate;
	expirationDate.year = year;
	expirationDate.month = month;
	return expirationDate;
}

/**
 * @brief Given 2 pointers of product uses the given logic to determint which
 * is bigger
 * @param product1 - pointer to a Product
 * @param product2 - pointer to a Product
 * @return 1 if product1 is bigger, -1 if product2 is bigger, 0 if are equal
 */
int productComparator(const Product *product1, const Product *product2)

{

	if (product1->barcode > product2->barcode)
	{
		return PRODUCT1_IS_BIGGER;
	}
	else if (product1->barcode < product2->barcode)
	{
		return PRODUCT2_IS_BIGGER;
	}
	else
	{
		if (product1->expiration.year > product2->expiration.year)
		{
			return PRODUCT1_IS_BIGGER;
		}
		else if (product1->expiration.year < product2->expiration.year)
		{
			return PRODUCT2_IS_BIGGER;
		}
		else
		{
			if (product1->expiration.month > product2->expiration.month)
			{
				return PRODUCT1_IS_BIGGER;
			}
			else if (product1->expiration.month < product2->expiration.month)
			{
				return PRODUCT2_IS_BIGGER;
			}
			else
			{
				return strcmp(product1->name, product2->name);
			}
		}
	}
}

/**
 * @brief Checks if a given product is within the warehouse
 * If it exists add to inventory its amount
 * @param productToFind - a Product pointer of the product to look for
 * @return True(1) if it is matching. False (0) if not.
 */
int doesExistInWarehouse(const Product *productToFind)
{
	Product *matchingProduct = bsearch(productToFind, gWarehouse, gNumOfProducts,
									   sizeof(Product), (compfn) productComparator);
	if (matchingProduct != NULL)
	{
		matchingProduct->inInventory += productToFind->inInventory;
		return TRUE;
	}
	return FALSE;
}

/**
 * @brief Adds a single product to the warehouse
 * @param productData - a char array containning the string with
 * the product data.
 */
void addProductToWarehouse(const char productData[])
{
	//initializing inner Vars
	char name[MAX_NAME_LENGTH];
	int barcode, expirationYear, expirationMonth;
	float inInventory;

	//Basic Tests for input leagality
	if (sscanf(productData, "%[^\t]\t%4d\t%f\t%d-%d\n", name, &barcode,
		&inInventory, &expirationYear, &expirationMonth) != CORRECT_PRODUCT_ARGUMENTS_NUM ||
		monthCheck(expirationMonth) == FALSE || expirationMonth == 0 ||
		(int) strlen(name) >= MAX_NAME_LENGTH)
	{
		printf("unknown file format\n");
		exit(1);
	}

	Product newItem;
	strcpy(newItem.name, name);
	newItem.barcode = barcode;
	newItem.inInventory = inInventory;
	newItem.expiration = newExpirationDate(expirationYear, expirationMonth);

	//After creating new item - searches for it
	// if exists - add to amount otherwise add to warehouse
	if (doesExistInWarehouse(&newItem) == FALSE)
	{
		gWarehouse[gNumOfProducts] = newItem;
		gNumOfProducts++;
	}
}

/**
 * @brief Sorts the warehouse
 */
void sortDataBase()
{
	qsort(gWarehouse, gNumOfProducts, sizeof(Product), (compfn) productComparator);
}

/**
 * @brief given a data base file with correct structure will build
 * the warehouse - the database of products
 * @param dbFile - a pointer to a File
 */
void buildDB(FILE *dbFile)
{
	//In case got an empty file
	if (isFileEmpty(dbFile) == TRUE)
	{
		printf("unknown file format\n");
		exit(1);
	}
	 char productData[DEFAULT_LINE_SIZE];
	 //For each line - which represents a product - add and sort warehouse
	 while (fgets(productData, DEFAULT_LINE_SIZE, dbFile) != NULL)
	 {
		 //In case is empty line
		 if (strcmp(productData, "\n") == THE_SAME)
		 {
			 continue;
		 }
		 addProductToWarehouse(productData);
		 sortDataBase();
	 }
}

/**
 * @brief Receives a file and adds its invenotory into our
 * already exisitng warehouse
 * @param commandArgsFile - a char array containning the name of the file
 */
void received(const char commandArgsFile[])
{
	FILE *commandFile = fopen(commandArgsFile, "r");
	buildDB(commandFile);
	fclose(commandFile);
	commandFile = NULL;
}

/**
 * @brief Cleans all the soldout products in the warehouse
 */
void cleanSoldoutProducts()
{
	int i = 0;
	while (i < gNumOfProducts)
	{
		if (gWarehouse[i].inInventory <= RUN_OUT_ACCURACY)
		{
			gWarehouse[i].inInventory = RUN_OUT_OF_PRODUCT;
		}
		i++;
	}
}

/**
 * @brief Cleans all the expired products in the warehouse
 * @param year - an int of the expired year
 * @param month - an int of the expired month
 */
void cleanExpiredProducts(const int year, const int month)
{
	int i = 0;
	while (i < gNumOfProducts)
	{
		if (gWarehouse[i].expiration.year <= year)
		{
			if (month != IGNORE_MONTHS_IN_CHECK)
			{
				if (gWarehouse[i].expiration.year < year || gWarehouse[i].expiration.month < month)
				{
					gWarehouse[i].inInventory = RUN_OUT_OF_PRODUCT;
				}
			}
			else
			{
				if (gWarehouse[i].expiration.year < year)
				{
					gWarehouse[i].inInventory = RUN_OUT_OF_PRODUCT;
				}
			}
		}
		i++;
	}
}

/**
 * @brief Cleans all the expired products in the warehouse
 * @param date - a char array containning the date for the expirtaion date
 * 0 in month - disregard month, o in year - only clean soldouts
 */
void clean(const char date[])
{
	int expirationYear, expirationMonth;
	if (sscanf(date, " %d-%d", &expirationYear, &expirationMonth) == CORRECT_DATE_ARGUMENTS_NUM)
	{
		if (expirationYear != AVOID_CHECKING_EXPIRED_PRODUCTS)
		{
			cleanExpiredProducts(expirationYear, expirationMonth);
		}
		cleanSoldoutProducts();
	}
	else
	{
		printf("USAGE: waredb <db file> <command> <command arg file>\n");
		exit(1);
	}
}

/**
 * @brief updates the correct amount of each product untill all wanted amount is filled
 * @param wantedAmount - a float of how much of the product is requested
 * @param firstMatchIndex - an int where the first product is in the warehouse
 * @param remainingDifference - the remaining differne to check if still needs to send
 */
void updateAmounts(const float wantedAmount, int firstMatchIndex, float remainingDifference)
{
	//In case has enough to send
	if (remainingDifference >= -RUN_OUT_ACCURACY)
	{
		//Update to zero all the products with the proper barcode
		//Untill the product which the sum of quantites reached the requested goal
		remainingDifference = wantedAmount;
		while (remainingDifference > RUN_OUT_ACCURACY)
		{
			if (remainingDifference - gWarehouse[firstMatchIndex].inInventory >
				RUN_OUT_ACCURACY)
			{
				remainingDifference -= gWarehouse[firstMatchIndex].inInventory;
				gWarehouse[firstMatchIndex].inInventory = MINIMUM_AMOUNT_OF_PRODUCT;
				firstMatchIndex++;
			}
			else
			{
				gWarehouse[firstMatchIndex].inInventory -= remainingDifference;
				remainingDifference = 0.0f;
			}
		}
	}
	else
	{
		printf("not enough items in warehouse\n");
		exit(1);
	}
}

/**
 * @brief checks is given char[] represents a float
 * @param floater - an array of char representing a float to check
 * @return True(1) if it is float. False (0) if not.
 */
int checkFloat(char floater[])
{
	int i = 0;
	int numOfDots = NO_DECIMEL_POINTS;
	//Check each individual char if fits Float logic
	while (i < (int)strlen(floater))
	{
		if (!isdigit(floater[i]))
		{
			if (numOfDots == NO_DECIMEL_POINTS)
			{
				if (floater[i] != DECIMEL_POINT)
				{
					return FALSE;
				}
				numOfDots++;
			}
			else
			{
				return FALSE;
			}
		}
		i++;
	}
	return TRUE;
}

/**
 * @brief checks is given char[] represents a float
 * @param floater - an array of char representing a float to check
 * @return True(1) if it is float. False (0) if not.
 */
void checkSentCommand(char command[])
{
	//initialize inner vars
	char barcode[BARCODE_LENGTH];
	char wantedAmount[FLOAT_SIZE];
	strncpy(barcode, &command[0], BARCODE_LENGTH);
	strncpy(wantedAmount, &command[WANTED_AMOUNT], (int)strlen(command) - (WANTED_AMOUNT + 1));
	int barcodeInt;

	// if barcode is not int or wanted amount if not float - return error
	if (sscanf(barcode, "%d", &barcodeInt) != ONE_ARGUMENT || checkFloat(wantedAmount) != TRUE)
	{
		printf("unknown file format\n");
		exit(1);
	}
}

/**
 * @brief gets a file of products to send - and send them out
 * of the warehouse if there are enough of what is wanted
 * @param commandArgsFile - a char array containning the name of the file
 */
void sent(const char commandArgsFile[])
{
	//initialize inner vars
	int barcode, i, firstMatchIndex;
	float wantedAmount, remainingDifference = INITIAIZED_REMAINNING_DIFFERENCE;
	char command[DEFAULT_LINE_SIZE];
	FILE *commandFile = fopen(commandArgsFile, "r");

	//In case file is empty
	if (isFileEmpty(commandFile) == TRUE)
	{
		printf("unknown file format\n");
		exit(1);
	}

	//Runs on all lines of file
	while (fgets(command, DEFAULT_LINE_SIZE, commandFile) != NULL)
	{
		//ignores empty lines
		 if (strcmp(command, "\n") == THE_SAME)
		 {
			 continue;
		 }

		 //checks if command is proper
		 checkSentCommand(command);
		 i = 0;
		 if (command[SEPERATION_TAB] != TAB_SIGN)
		 {
			 printf("unknown file format\n");
			 exit(1);
		 }
		 if (sscanf(command, "%4d\t%f", &barcode, &wantedAmount) == CORRECT_DATE_ARGUMENTS_NUM)
		 {
			 //looks for the requested barcode
			 while (gWarehouse[i].barcode != barcode && i < gNumOfProducts)
			 {
				 i++;
			 }

			 //In case found barcode start checking if has enough of
			 if (i < gNumOfProducts)
			 {
				 firstMatchIndex = i;
				 remainingDifference = gWarehouse[i].inInventory - wantedAmount;
				 while (remainingDifference <= RUN_OUT_ACCURACY &&
						gWarehouse[i + 1].barcode == barcode)
				 {
					 remainingDifference += gWarehouse[i + 1].inInventory;
					 i++;
				 }

				 //In case found out that warehouse has enough - Now update the amounts
				 updateAmounts(wantedAmount, firstMatchIndex, remainingDifference);
			 }
			 else
			 {
				 printf("not enough items in warehouse\n");
				 exit(1);
			 }
		 }
		 else
		 {
			 printf("unknown file format\n");
			 exit(1);
		 }
	}
	fclose(commandFile);
}

/**
 * @brief writes the warehouse into a file
 * @param commandArgsFile - a char array containning the name of the file
 */
void writeWarhouseToFile(const char fileName[])
{
	FILE *dbFile = fopen(fileName, "w+");

	//In case is not writable
	if (dbFile == NULL)
	{
		printf("%s: Permission denied\n", fileName);
		exit(1);
	}

	int i = 0;

	// Runs on warehouse and print to file the not marked as earased products
	while (i < gNumOfProducts)
	{
		if (gWarehouse[i].inInventory != RUN_OUT_OF_PRODUCT &&
			gWarehouse[i].inInventory > RUN_OUT_ACCURACY)
		{
			fprintf(dbFile, "%s\t%d\t%.3f\t%d-%d\n", gWarehouse[i].name, gWarehouse[i].barcode,
			gWarehouse[i].inInventory, gWarehouse[i].expiration.year,
			gWarehouse[i].expiration.month);
		}
		i++;
	}
	fclose(dbFile);
	dbFile = NULL;
}

/**
 * @brief checks if the args file has readability permissions and is openable
 * @param argsFile - a char array containning the name of the file
 */
void checkArgsFile(const char argsFile[])
{
	FILE *commandFile = fopen(argsFile, "r");
	if (commandFile == NULL)
	{
		printf("%s: no such file\n", argsFile);
		exit(1);
	}
	fclose(commandFile);
	commandFile = NULL;
}

/**
 * @brief The main function which runs the project - calls the needed functions
 * in order to run the process of building sorting cleaning or sending items from the warehouse
 * @param argc - given automatically when entering parameters when starting the program
 * @param argv - pointer to an array of chars - hold automatically the
 * params entered seperated by space
 * @return 0, tells the system execution ended without errors
 * Or 1 otherwise.
 */
int main(const int argc, char* argv[])
{
	//Run First Checks
	initialValidation(argc, argv);
	char command[MAX_COMMAND_SIZE];
	strcpy(command, argv[COMMAND]);
	FILE *dbFile = fopen(argv[DB_FILE], "r");

	//Creates the warehouse out of the given db file
	buildDB(dbFile);
	fclose(dbFile);

	//Do as user input requested from knoon commands
	if (!strcmp(command, CLEAN_COMMAND))
	{
		clean(argv[DATE]);
	}
	else
	{
		checkArgsFile(argv[COMMAND_ARGS_FILE]);
		if(!strcmp(command, RECEIVED_COMMAND))
		{
			received(argv[COMMAND_ARGS_FILE]);
		}
		else
		{
			sent(argv[COMMAND_ARGS_FILE]);
		}
	}

	//After action finished write back to file the warehouse after changes
	writeWarhouseToFile(argv[DB_FILE]);
	return 0;
}
