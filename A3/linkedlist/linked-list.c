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
		strcpy(tmp->docid, id);
		tmp->doc_freq = freq;
		tmp->next = NULL;
		
	} else {
		
		//instantiate list
		f = malloc(sizeof(struct freq_list));
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

struct term_list *term_list_add(struct term_list *t, char *te, struct freq_list *occ) {
	
	if (t) {
		
		struct term_list *tmp;
		tmp = t;
		//go to end
		while (tmp) {
			tmp = tmp->next;
		}
		//add
		tmp = malloc(sizeof(struct term_list));
		strcpy(tmp->term, te);
		tmp->occur = occ;
		tmp->next = NULL;
		
	} else {
		
		//instantiate list
		t = malloc(sizeof(struct term_list));
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
