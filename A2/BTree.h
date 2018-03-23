#define EXIT 5
#define ORDER 4

typedef enum {EXISTS, NOT_EXISTS} SearchResults;

//definition of a Record
typedef struct _record {
	
	char *word;
	char *pronounciation;
	char *stress;
	int foreign;
	
}Record;

//definition of a Page
typedef struct _page {
	
	int keyCount;
	Record key[ORDER - 1];
	int keyIndex[ORDER - 1];
	int child[ORDER];
	
}Page;

//global variables
int DATA_FILE_HEADER_LENGTH;
int INDEX_FILE_HEADER_LENGTH;
int PAGE_SIZE;
int HEAD_PAGE_INDEX;
int TOTAL_PAGES;

//main UI
void displayOptions();

//display methods
void printRecord(Record r);
void printPage(Page p);
void printTree(int RRN);

//collection methods
Page initializePage(Record r);
Record collectRecordAtIndex(char *key, int index);
Page readPageAt(int RRN);
void writeDataToIndexFile(int loc, char *s);

//B-Tree methods
int isLeafNode(Page r);
SearchResults searchRecord(int RRN, char *key);
