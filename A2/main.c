#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "BTree.h"
#include "parsing.h"

int main() {
	
	char input[20];
	int opt = 0;
	initialSetup();
	
	printf("Please enter the number of what option you would like:\n");
	do {
		
		displayOptions();
		fgets(input, 20, stdin);
		if (isdigit(input[0])) {
			
			opt = atoi(&input[0]);
			
			switch (opt) {
				
				case 1:
					printf("Insert not yet supported\n");
					break;
				case 2:
					printf("Enter the key you want to search for > ");
					fgets(input, 20, stdin);
					input[strlen(input)-1] = '\0';//removes \n
					if (searchRecord(HEAD_PAGE_INDEX, input) == NOT_EXISTS) {
						printf("Record %s not found\n", input);
					}
					break;
				case 3:
					printTree(HEAD_PAGE_INDEX);
					break;
				case 4:
					printHeaders();
					break;
				case 5:
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
