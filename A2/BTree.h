#include <stdio.h>

#define EXIT 4

typedef struct _btree {
	
	int order;
	char **keys;
	
	
}BTree;

/**Displays list of available options**/
void displayOptions() {
	
	printf("\n1) Insert a record\n");
	printf("2) Search for a record\n");
	printf("3) Display current B-Tree\n");
	printf("4) Exit\n");
	printf(">");
	
}
