#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TREE STRUCTURE*/
typedef struct NodeTree 
{
int elem;  
struct NodeTree *parent;
struct NodeTree *left;
struct NodeTree *right;
} Node; 

/*Adding a ROOT*/
Node* addRoot(int x)
{

    Node *root = malloc(sizeof(Node));
    root->elem = x;
    root->left = root->right = NULL;
	return root;
}


/*Adding a NODE by PARENT*/
void addNodeByParent(int x, Node *parent,int *level)
{
    
    Node *root = malloc(sizeof(Node));
    root->elem = x;
	root->parent = parent;
	root->left = root->right = NULL;
	if (!parent->left) {
		parent->left = root;
		*level = *level + 1;
	}
	else if (!parent->right)
		parent->right = root;
	else
		printf("You can't add more that 2 nodes in a BINtree!\n");
    
}

/*Adding NODE by SIBLING*/
void addNodeBySibling(int x,Node *sibling)
{
   
    Node *root = malloc(sizeof(Node));
	Node *parent = sibling->parent;
    root->elem = x;
	root->parent = parent;
	root->left = root->right = NULL;
	if (!parent->left)
		parent->left = root;
	else
		parent->right = root;
    
}



/*search for node by value*/
void searchNode(Node *root,Node **foundNode, int x) {
	if(root->elem == x)
		*foundNode = root;
	if(root->left) 
		searchNode(root->left,foundNode,x);
	if (root->right)
		searchNode(root->right,foundNode,x);
}

char** parser(char* string);
char** trinput(char* command, char** args);

void printTree (Node *root) 
{ 
	if(root)
		printf("%d ",root->elem);
	if(root->left) 
		printTree(root->left);
	if (root->right)
		printTree(root->right);
	
}

/*>>START OF MAIN METHOD<<*/
int main() {
	Node *root = NULL;
	Node *foundNode = NULL;
	int level = 0;
	int nodesCounter = 0;
	int innerNodes = 0;
	char command[100];
	char** args = NULL;
	printf("Hello. Create a bintree by next format:\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\nadd root 2\nadd node 10 parent root\nadd node 3 parent/sibling 10\nend (finish creating)\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	args = trinput(command,args);
	while(strcmp(args[0],"end"))
	{
		nodesCounter++;
		if(!strcmp(args[1],"root")) {
			root = addRoot(atoi(args[2]));
		}
		else if (!strcmp(args[1],"node")) 
		{
			int key = atoi(args[2]);
			int family = (!strcmp(args[4],"root"))? root->elem : atoi(args[4]);
			searchNode(root,&foundNode,family);
			if(!strcmp(args[3],"parent")) {
			if(!foundNode) {
				printf("Such a node doesn't exist.");
				break;
			}
				if(!foundNode->left)
					innerNodes++;
				addNodeByParent(key,foundNode,&level);
			}
			else {
				addNodeBySibling(key,foundNode);
			}
				
		}
		args = trinput(command,args);
	}
	
	printf("\n_______________________________\n");
	printf("The number of all nodes: %d\n",nodesCounter);
	printf("The number of internal nodes: %d\n",innerNodes);
	printf("The Number of leaves: %d\n\n",nodesCounter - innerNodes);
	printf("What would you like to do now?:\n>exit\n>show (bintree)\n");
	scanf("%s",command);
	while(strcmp(command,"exit")) {
		if(!strcmp(command,"show"))
			printTree(root);
		printf("\n");
		scanf("%s",command);
	}

	return 0;
}
/*>>END OF MAIN METHOD<<*/


char** parser(char* string)
{
	int argsBuff = 100;
	char** args = (char**)malloc(argsBuff*sizeof(char*));
	char* token;
	int i = 0;
	token = strtok(string," ");
	
	if(token != NULL) 
	{
		while(token != NULL) 
		{
			args[i++] = token;
			token = strtok(NULL," ");
			if( i >= argsBuff) 
			{
				argsBuff *= argsBuff;
				args = realloc(args,argsBuff);
			}
		}
	}
	else if ((token = strtok(string,"\0")) != NULL) 
	{
		args[i++] = token;
	}
	
	args[i] = NULL;
	
	return args;
	
}

char** trinput(char* command, char** args) 
{
	if(args)
		free(args);
	gets(command);
	args = parser(command);
	
	return args;
}
 