#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl/avl.h"
#include "offline.h"

/**Begin parsing input document**/
void parseDocument(char *f) {
	
	char out_name[50];
	char in_line[1000];
	PARSE_STATE s = DOC;
	
	//stores all elements before adding to tree
	struct term_list *terms = NULL;
	
	//setup input/output files
	fp_in = fopen(f, "r");
	
	strcpy(out_name, "dict_");
	strcat(out_name, f);
	fp_dict = fopen(out_name, "w");
	
	strcpy(out_name, "post_");
	strcat(out_name, f);
	fp_post = fopen(out_name, "w");
	
	strcpy(out_name, "doc_");
	strcat(out_name, f);
	fp_doc = fopen(out_name, "w");
	
	while(fgets(in_line, 1000, fp_in)) {
		
		char tmp[1000];//used for strtok buffer
		strcpy(tmp, in_line);
		
		if (strcmp(strtok(tmp, " "), "$DOC") == 0) {
			
			s = DOC;
			
		} else if (strcmp(in_line, "$TITLE\n") == 0) {
			
			s = TITLE;
			printf("TITLE vs %s\n", in_line);
			fgets(in_line, 1000, fp_in);
			
		} else if (strcmp(in_line, "$BODY\n") == 0) {
			
			s = BODY;
			fgets(in_line, 1000, fp_in);
			
		}
		
		if (s == DOC) {
			
			//read out <docid>
			char *id = strtok(NULL, " ");
			id[strlen(id)-1] = '\0';
			printf("DOC = |%s|\n", id);
			
			//swap states
			getchar();
			
		} else if (s == TITLE) {
			
			printf("\tTITLE = %s\n", in_line);
			//iterate through all the terms and add them to the tree
			char *t = malloc(sizeof(char)*50);
			t = strtok(in_line, " ");
			do {
				
				if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
				//find if term is already in list
				
				
			} while (t = strtok(NULL, " "));
			
		} else if (s == BODY) {
			
			printf("\tBODY = %s\n", in_line);
			//iterate through all the terms and add them to the tree
			char *t = malloc(sizeof(char)*50);
			t = strtok(in_line, " ");
			do {
				
				if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
				printf("BODY|%s|\n", t);
				
			} while (t = strtok(NULL, " "));
			
		}
		
	}
	
}
