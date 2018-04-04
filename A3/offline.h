FILE *fp_in;
FILE *fp_dict, *fp_post, *fp_doc;

typedef enum {DOC, TITLE, BODY} PARSE_STATE;

void parseDocument(char *f);
