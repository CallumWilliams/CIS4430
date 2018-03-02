#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "BTree.h"

int main() {
	
	char input[10];
	int opt = 0;
	initialSetup();
	//readPageAt(0);
	
	printf("Please enter the number of what option you would like:\n");
	do {
		
		displayOptions();
		fgets(input, 10, stdin);
		if (isdigit(input[0])) {
			
			opt = atoi(&input[0]);
			
			switch (opt) {
				
				case 1:
					printf("Insert not yet supported\n");
					break;
				case 2:
					printf("Search not yet supported\n");
					break;
				case 3:
					printTree(HEAD_PAGE_INDEX);
					break;
				case 4:
					printf("Exiting program\n");
					break;
				default:
					printf("Unrecognized command %d\n", opt);
			}
			
		} else {
			printf("Invalid input\n");
		}
		
	} while (opt != EXIT);
	
	return 0;
	
}
