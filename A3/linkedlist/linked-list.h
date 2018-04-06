struct freq_list {
	
	char *docid;			//id for current frequency
	int doc_freq;			//frequency
	struct freq_list *next;	//pointer to next
	
};

struct term_list {
	
	char *term;				//list of terms
	struct freq_list *occur;//occurrences across all docs
	struct term_list *next;	//pointer to next
	
};

struct freq_list *freq_list_add(struct freq_list *f, char *id, int freq);
struct freq_list *freq_list_contains(struct freq_list *f, char *id);
void incrementFrequency(struct freq_list *f, char *id);
void printFrequencies(struct freq_list *f);
int listSize(struct term_list *t);

struct term_list *term_list_add(struct term_list *t, char *te, struct freq_list *occ);
struct term_list *term_list_contains(struct term_list *t, char *id);
void printTerms(struct term_list *t);
