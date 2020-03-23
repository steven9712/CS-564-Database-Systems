//
// File: wl.h
// 
//  Description: code for the wordlocater program which can either load a file contents, locate a word depending on which occurence it was used, newly make a blank data structure, or end program
//  Student Name: Steven Choi
//  UW Campus ID: 9074018194
//  enamil: schoi243@wisc.edu

#define _CRT_SECURE_NO_WARNINGS
#include "wl.h"
std::string delim;

/*! @brief class that implements the links for the nodes*/
class link {

	public:
		int* arr;	/**< store indices */
		size_t mem;		/**< store memory allocated */
		size_t vsize;	/**< store data */


		/* @brief constructor that sets everything to 0 and NULL*/
		link() :arr(NULL), mem(0), vsize(0) {}

		/* @brief returns size of structure*/
		size_t size() {
			return vsize;
		}

		/* @brief function that adds an integer to the end of the structure
		* @param index	index of data structure to add
		* @return doesn't return anything
		*/
		void push(int index)
		{
			if (vsize + 1 > mem)
			{
				if (mem == 0)
				{
					mem = 2;
					arr = (int*)malloc(mem * sizeof(int));
					arr[vsize++] = index;
				}
				else
				{
					mem *= 2;
					arr = (int*)realloc(arr, mem * sizeof(int));
					arr[vsize++] = index;
				}
			}
			else
			{
				arr[vsize++] = index;
			}
		}

		/**
		* @brief allows the data structure to have array like access to calls
		* @param index Index of the data which is to be accessed.
		* @return Data at the input index.
		*/
		int operator[] (int index)
		{
			return arr[index];
		}
};


/*! @brief class for the nodes of the BST*/
class node {

	public:
		node* left;		/**< pointer to the left child of node */
		node* right;	/**< pointer to the right child of node */
		char* word;		/**< word stored in node */
		link* index;	/**< index(s) of word in document */

		//@brief constructor that sets everything to NULL
		node() : left(NULL), right(NULL), word(NULL), index(NULL) {}

		/**
		* @brief constructor that sets word to the word in the input parameters
		* @param word the word to be initalized
		*/
		node(char* word) : left(NULL), right(NULL), word(word), index(new link()) {}

} *rnode;


/**
 * @brief function that inserts word into BST
 * @param	word	word to be inserted
 * @param index index of word in document
 * @return new root of BST
 */
node* insert(node* root, const char* word, int index)
{
	if (root == NULL)
	{
		root = new node(strdup(word));
		root->index->push(index);
		return root;
	}
	int comparison = strcasecmp(word, root->word);

	if (comparison < 0)
	{
		node* returnNode = insert(root->left, word, index);

		if (root->left == NULL)
		{
			root->left = returnNode;
		}
	}
	else if (comparison > 0)
	{
		node* returnNode = insert(root->right, word, index);
		if (root->right == NULL)
		{
			root->right = returnNode;
		}
	}
	else
	{
		root->index->push(index);
	}

	return root;
}

/**
*@brief function that looks up a word from BST
@param root root of BST
@param word the word to look up
@return node that contains the word and its indices, returns NULL if word doesn't exist
*/
node* search(node* root, const char* word)
{
	if (root == NULL)
	{
		return NULL;
	}
	node* returnNode = NULL;
	int comparison = strcasecmp(word, root->word);
	
	if (comparison < 0)
	{
		returnNode = search(root->left, word);
	}
	else if (comparison > 0)
	{
		returnNode = search(root->right, word);
	}
	else
	{
		returnNode = root;
	}

	return returnNode;
}

/**
 * @brief make a deliminator so that the words in the input file does not include bad characters

 * @return doesn't return anything
 */
void makeDelim() {
	for (int i = 1; i < 256; i++) {
		if (i >= 48 && i <= 57) continue;   // [0-9] cannot end word
		if (i >= 65 && i <= 90) continue;   // [A-Z] cannot end word
		if (i >= 97 && i <= 122) continue;  // [a-z] cannot end word
		if (i == 39) continue;              // '(Apostrophe) cannot end word
		delim += (char)i;
	}
}

/**
 * @brief checks if all the characters in the input contains the correct characters

 * @param word	  word to be checked
 * @retval true   when all characters are valid
 * @retval false  when any character is not valid
 */
bool checkWordChar(const char* word) {

	for (; *word != '\0'; word++)
	{
		int i = *word;
		if (i >= 48 && i <= 57)
		{
			continue;
		}
		else if (i >= 65 && i <= 90)
		{
			continue;
		}
		else if (i >= 97 && i <= 122)
		{
			continue;
		}
		else if (i == 39)
		{
			continue;
		}
		else if (i == 0)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

/* @brief main function*/
int main(int argc, char* argv[])
{
	char input[514];
	char* currCommand = input, * token = input;

	FILE* filein = stdin, * currFile = NULL;
	char* check = NULL;
	command cmd = ERROR;
	makeDelim();

	while (1) 
	{
		cmd = ERROR;
		printf("%s", ">");
		check = fgets(input, sizeof(input), filein);

		if (check == NULL)
		{
			continue;
		}

		char* context;
		char* args[4];
		int i = 0;
		currCommand = input;
		check = strchr(currCommand, '\n');
		if (check != NULL)
		{
			*check = '\0';
		}

		// tokenizes the command line arguments and saves them into the args array
		while (NULL != (token = strtok_r(currCommand, " ", &context)))
		{
			currCommand = NULL;
			args[i++] = token;
			if (i > 3)
			{
				break;
			}
		}

		// if there is only 1 command line argument, there can only be 2 commands: new and end
		if (i == 1)
		{
			if (strcasecmp(args[0], "new") == 0)
			{
				cmd = NEW;
			}
			else if (strcasecmp(args[0], "end") == 0)
			{
				cmd = END;
			}
		}
		// if there are 2 command line arguments
		else if (i == 2)
		{
			if (strcasecmp(args[0], "load") == 0)
			{
				cmd = LOAD;
			}
		}
		// if there are 3
		else if (i == 3)
		{
			if (strcasecmp(args[0], "locate") == 0)
			{
				cmd = LOCATE;
			}
		}
		// anything else is an error
		else
		{
			printf("ERROR: Invalid command\n");
			continue;
		}

		// used switch statements for each of the 4 commands
		switch (cmd) 
		{
			// loads the file and saves the words with valid characters into the BST
			case LOAD: {

				currFile = fopen(args[1], "r");
				if (currFile == NULL) printf("HAHA");

				if (currFile == NULL)
				{
					printf("ERROR: Invalid command\n");
				}
				if (rnode != NULL)
				{
					delete rnode;
					rnode = NULL;
				}

				char line[100];
				int index = 1;

				while (NULL != fgets(line, sizeof(line), currFile))
				{
					currCommand = line;
					while (NULL != (token = strtok_r(currCommand, delim.c_str(), &context)))
					{
						currCommand = NULL;
						std::string temp(token);
						rnode = insert(rnode, temp.c_str(), index);
						index++;
					}
				}
				fclose(currFile);
			}
					   break;

			// locates the word wanted in the BST printing which instance of the document it is from
			case LOCATE: {

				char* err = NULL;
				int occurence = strtol(args[2], &err, 10);
				if (*err != '\0')
				{
					printf("ERROR: Invalid command\n");
					continue;
				}
				if (occurence < 0)
				{
					printf("ERROR: Invalid command\n");
					continue;
				}
				if (checkWordChar(args[1]) == false)
				{
					printf("ERROR: Invalid command\n");
				}

				std::string temp(args[1]);
				node* rc = search(rnode, temp.c_str());
				
				if (rc == NULL)
				{
					printf("No matching entry\n");
				}
				else if (rc->index->size() < (unsigned int)occurence)
				{
					printf("No matching entry\n");
				}
				else
				{
					printf("%d\n", (*(rc->index))[occurence - 1]);
				}
			}
				break;

			// makes a new clean data structure without any contents
			case NEW:
				if (rnode != NULL)
				{
					delete rnode;
					rnode = NULL;
				}
				break;

			// ends the program and deletes any saved data
			case END:
				if (rnode != NULL)
				{
					delete rnode;
					rnode = NULL;
				}
				return 0;
				break;

			default:
				printf("ERROR: Invalid command\n");
				continue;
		}

		

	}
	
	return 0;
}

