#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"

/**Makes use of two different linked list types**/
/**First, a list of terms that are in all the documents**/
/**Second, a list of certain term frequencies across all docs**/

struct freq_list *freq_list_add(struct freq_list *f, char *id, int freq) {
	
	if (f) {
		
		struct freq_list *tmp;
		tmp = f;
		//go to end
		while (tmp) {
			tmp = tmp->next;
		}
		//add
		tmp = malloc(sizeof(struct freq_list));
		tmp->docid = malloc(sizeof(strlen(id)));
		strcpy(tmp->docid, id);
		tmp->doc_freq = freq;
		tmp->next = NULL;
		
	} else {
		
		//instantiate list
		f = malloc(sizeof(struct freq_list));
		f->docid = malloc(sizeof(strlen(id)));
		strcpy(f->docid, id);
		f->doc_freq = freq;
		f->next = NULL;
		
	}
	
	return f;
	
}

struct freq_list *freq_list_contains(struct freq_list *f, char *id) {
	
	struct freq_list *tmp = f;
	while (tmp) {
		
		if (strcmp(tmp->docid, id) == 0) {
			return tmp;
		}
		tmp = tmp->next;
		
	}
	
	return NULL;
	
}

void incrementFrequency(struct freq_list *f, char *id) {
	
	struct freq_list *tmp;
	tmp = freq_list_contains(f, id);
	
	tmp->doc_freq++;
	
}

void printFrequencies(struct freq_list *f) {
	
	struct freq_list *tmp = f;
	while (tmp) {
		
		printf("\t%s occurs %d times\n", tmp->docid, tmp->doc_freq);
		tmp = tmp->next;
		
	}
	
}

struct term_list *term_list_add(struct term_list *t, char *te, struct freq_list *occ) {
	
	if (t) {
		
		struct term_list *tmp;
		tmp = t;
		//go to end
		while (tmp->next) {
			tmp = tmp->next;
		}
		//add
		tmp->next = malloc(sizeof(struct term_list));
		tmp->next->term = malloc(sizeof(strlen(te)));
		strcpy(tmp->next->term, te);
		tmp->next->occur = occ;
		tmp->next->next = NULL;
		
	} else {
		
		//instantiate list
		t = malloc(sizeof(struct term_list));
		t->term = malloc(sizeof(strlen(te)));
		strcpy(t->term, te);
		t->occur = occ;
		t->next = NULL;
		
	}
	
	return t;
	
}

struct term_list *term_list_contains(struct term_list *t, char *id) {
	
	struct term_list *tmp = t;
	while (tmp) {
		
		if (strcmp(tmp->term, id) == 0) {
			return tmp;
		}
		tmp = tmp->next;
		
	}
	
	return NULL;
	
}

int listSize(struct term_list *t) {
	
	struct term_list *tmp = t;
	int i = 0;
	while (tmp) {
		i++;
		tmp = tmp->next;
	}
	printf("Size %d\n", i);
	return i;
	
}

void printTerms(struct term_list *t) {
	
	struct term_list *tmp = t;
	while (tmp) {
		
		printf("Term: %s\n", tmp->term);
		printFrequencies(tmp->occur);
		tmp = tmp->next;
		
	}
	
}
