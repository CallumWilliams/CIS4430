#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "offline.h"
#include "avl/avl.h"

/**Prototype of comparison function**/
int data_cmp(void *a, void *b) {
	
	DOC_TERM *a_conv = (DOC_TERM *) a;
	DOC_TERM *b_conv = (DOC_TERM *) b;
	
	//null pointer protection
	if (a_conv && b_conv) {
		return strcmp(a_conv->term_name, b_conv->term_name);
	}
	return 0;
	
}

/**Prototype of printing function**/
void data_print(void *prnt) {
	
	DOC_TERM *p = (DOC_TERM *) prnt;
	
	if (p) {
		printf("%s\n", p->term_name);
	}
	
}

/**Prototype of deletion function**/
void data_del(void *rem) {
	
	DOC_TERM *r = (DOC_TERM *) rem;
	
	if (r) {
		free(r);
	}
	
}

/**Prototype of copying function**/
void data_copy(void *src, void *dest, size_t t) {
	
	DOC_TERM *s = (DOC_TERM *) s;
	DOC_TERM *d = (DOC_TERM *) d;
	
	if (s && d) {
		strcpy(d->term_name, s->term_name);
	}
	
}

int main(int argv, char *argc[]) {
	
	avl_tree = init_dictionnary(data_cmp, data_print, data_del, data_copy);
	
	if (argv != 2) {
		printf("Run as ./offline <file-name>\n");
		return 1;
	}
	parseDocument(argc[1]);
	
}
