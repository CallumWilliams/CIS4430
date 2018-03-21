#define EXIT 5
#define ORDER 4

typedef enum {EXISTS, NOT_EXISTS} SearchResults;

typedef struct _record {
	
	char *word;
	char *pronounciation;
	char *stress;
	int foreign;
	
}Record;

typedef struct _page {
	
	int keyCount;
	Record key[ORDER - 1];
	int keyIndex[ORDER - 1];
	int child[ORDER];
	
}Page;

int DATA_FILE_HEADER_LENGTH;
int INDEX_FILE_HEADER_LENGTH;
int PAGE_SIZE;
int HEAD_PAGE_INDEX;
int TOTAL_PAGES;

//functions
void initialSetup();
void displayOptions();

void printHeaders();
void printRecord(Record r);
void printPage(Page p);
void printTree(int RRN);

Page initializePage(Record r);
Record collectRecordAtIndex(char *key, int index);
Page readPageAt(int RRN);
void writeDataToIndexFile(int loc, char *s);

void buildDataFileHeader(int flag, int recs);
void buildIndexFileHeader(int headInd, int keyCount);
char *buildDataRecordString(Page p);

SearchResults searchRecord(int RRN, char *key);
