#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "offline.h"

/**Begin parsing input document**/
void parseDocument(char *f) {
	
	char out_name[50];
	char in_line[1000];
	PARSE_STATE s = DOC;
	
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
			
		} else if (s == BODY) {
			
			printf("\tBODY = %s\n", in_line);
			
		}
		
	}
	
}

/**Prototype of comparison function**/
int my_cmp(const struct avltree_node *a, const struct avltree_node *b) {
	
	DOC_TERM *p = avltree_container_of(a, DOC_TERM, node);
	DOC_TERM *q = avltree_container_of(b, DOC_TERM, node);
	
	return strcmp(p->term_name, q->term_name);
	
}

int main(int argv, char *argc[]) {
	
	struct avltree tree;
	int cmp_fn;
	
	avltree_init(&tree, cmp_fn, 0);
	
	if (argv != 2) {
		printf("Run as ./offline <file-nam>\n");
		return 1;
	}
	parseDocument(argc[1]);
	
}
