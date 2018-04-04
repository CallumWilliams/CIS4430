#include "avl/libtree.h"

FILE *fp_in;
FILE *fp_dict, *fp_post, *fp_doc;

typedef struct doc_term {
	
	char *term_name;			//string for the term
	int term_freq;				//number of documents the term is found in
	struct avltree_node node;	//reference to its avltree_node
	
}DOC_TERM;

typedef enum {DOC, TITLE, BODY} PARSE_STATE;

void parseDocument(char *f);
