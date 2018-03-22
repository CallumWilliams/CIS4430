//initialize function
void initialSetup();

//print header data functions
void printHeaders();

//build data headers
void buildDataFileHeader(int flag, int recs);
void buildIndexFileHeader(int headInd, int keyCount);
char *buildDataRecordString(Page p);
