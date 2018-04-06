#include "avl/avl.h"
#include "linkedlist/linked-list.h"

//global avl variables
tree *avl_tree;

//file in/out variables
FILE *fp_in;
FILE *fp_dict, *fp_post, *fp_doc;

typedef struct doc_term {
	
	char *term_name;		//string for the term
	struct freq_list *freq;	//list of occurrences in documents
	
}DOC_TERM;

typedef enum {DOC, TITLE, BODY} PARSE_STATE;

void parseDocument(char *f);
