#define EXIT 5
#define ORDER 4

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
void printHeaders();
void printRecord(Record r);
Page initializePage(Record r);
Record collectRecordAtIndex(char *key, int index);
Page readPageAt(int RRN);
void buildDataFileHeader(int flag, int recs);
void buildIndexFileHeader(int headInd, int keyCount);
int searchRecord(int RRN, char *key);
void displayOptions();
void printPage(Page p);
void printTree(int RRN);
