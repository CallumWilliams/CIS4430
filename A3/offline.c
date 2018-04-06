#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl/avl.h"
#include "offline.h"

/**Begin parsing input document**/
void parseDocument(char *f) {
	
	char out_name[50];
	char in_line[1000];
	char id_tmp[100];
	PARSE_STATE s = DOC;
	
	int term_count = 0;
	
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
			fgets(in_line, 1000, fp_in);
			
		} else if (strcmp(in_line, "$BODY\n") == 0) {
			
			s = BODY;
			fgets(in_line, 1000, fp_in);
			
		}
		
		if (s == DOC) {
			
			//read out <docid>
			char *id = strtok(NULL, " ");
			id[strlen(id)-1] = '\0';
			strcpy(id_tmp, id);
			
		} else if (s == TITLE) {
			
			//iterate through all the terms and add them to the tree
			char *t = malloc(sizeof(char)*50);
			t = strtok(in_line, " ");
			
			do {
				
				if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
				
				struct term_list *curr_term;
				
				//check if term already exists in list
				if (curr_term = term_list_contains(terms, t)) {
					
					if (freq_list_contains(curr_term->occur, id_tmp)) {
						
						//increment the frequency
						incrementFrequency(curr_term->occur, id_tmp);
						
					} else {
						
						//add new frequency under current id
						curr_term->occur = freq_list_add(curr_term->occur, id_tmp, 1);
						
					}
					
				} else {
					
					//create fully new term
					struct freq_list *newFreq = NULL;
					newFreq = freq_list_add(newFreq, id_tmp, 1);
					terms = term_list_add(terms, t, newFreq);
					term_count++;
					
				}
				
				
			} while (t = strtok(NULL, " "));
			free(t);
			
		} else if (s == BODY) {
			
			//iterate through all the terms and add them to the tree
			char *t = malloc(sizeof(char)*50);
			t = strtok(in_line, " ");
			
			do {
				
				if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
				
				struct term_list *curr_term;
				
				//check if term already exists in list
				if (curr_term = term_list_contains(terms, t)) {
					
					if (freq_list_contains(curr_term->occur, id_tmp)) {
						
						//increment the frequency
						incrementFrequency(curr_term->occur, id_tmp);
						
					} else {
						
						//add new frequency under current id
						curr_term->occur = freq_list_add(curr_term->occur, id_tmp, 1);
						
					}
					
				} else {
					
					//create fully new term
					struct freq_list *newFreq = NULL;
					newFreq = freq_list_add(newFreq, id_tmp, 1);
					terms = term_list_add(terms, t, newFreq);
					
				}
				
			} while (t = strtok(NULL, " "));
			free(t);
		}
		
	}
	
	//write to dictionary
	fprintf(fp_dict, "%d\n", term_count);
	while(terms) {
		
		//add to tree + file
		fprintf(fp_dict, "%s %d\n", terms->term, terms->occur->doc_freq);
		terms = terms->next;
		
	}
	
}
