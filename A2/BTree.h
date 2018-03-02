#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define EXIT 4
#define ORDER 4
#define PAGE_SIZE 512

typedef struct _record {
	
	char *word;
	char *pronounciation;
	char *stress;
	int foreign;
	
}Record;

typedef struct _page {
	
	int keyCount;
	Record key[ORDER - 1];
	int child[ORDER];
	int childIndex[ORDER];
	
}Page;

int DATA_FILE_HEADER_LENGTH;
int INDEX_FILE_HEADER_LENGTH;
int HEAD_PAGE_INDEX;
int TOTAL_PAGES;

/**setups for global variables**/
void initialSetup() {
	
	//was unable to store header in file successfully (overwrote values)
	//trivial algorithm for getting header lengths
	
	FILE *f1, *f2;
	int c;
	
	//DATA_FILE_HEADER_LENGTH
	f1 = fopen("data.txt", "r");
	
	DATA_FILE_HEADER_LENGTH = 0;
	c = fgetc(f1);
	while (c != 124 && c != -1) {//'|' or EOF, respectively
		DATA_FILE_HEADER_LENGTH++;
		c = fgetc(f1);
	}
	fclose(f1);
	
	//INDEX_FILE_HEADER_LENGTH
	f2 = fopen("index.txt", "r");
	
	INDEX_FILE_HEADER_LENGTH = 0;
	c = fgetc(f2);
	
	while (c != 124 && c != -1) {
		INDEX_FILE_HEADER_LENGTH++;
		c = fgetc(f2);
	}
	fclose(f2);
	
}

/**Initializes a record**/
Record initializeRecord(char *w, char *p, char *s, int f) {
	
	Record r;
	
	strcpy(r.word, w);
	strcpy(r.pronounciation, p);
	strcpy(r.stress, s);
	r.foreign = f;
	
	return r;
	
}

/**Initializes a minimal page with record r**/
Page initializePage(Record r) {
	
	Page p;
	
	p.keyCount = 1;
	p.key[0] = r;
	for (int i = 0; i < ORDER; i++) {
		p.child[i] = -1;
	}
	
	return p;
	
}

/**build record from key and index**/
Record collectRecordAtIndex(char *key, int index) {
	
	int fd, pos, b;
	char recSize[3], *input, *tok;
	int recLen;
	Record r;
	
	memset(recSize, '\0', 3);
	
	fd = open("data.txt", O_RDONLY);
	pos = lseek(fd, DATA_FILE_HEADER_LENGTH + index + 1, 0);
	b = read(fd, recSize, 3);
	
	if (b != 3) {
		printf("error retreiving %s\n", key);
		exit(1);
	}
	
	//quickly remove any '|' characters that may be there
	for (int i = 0; i < 3; i++) {
		if (!isdigit(recSize[i])) {
			recSize[i] = ' ';
		}
	}
	//convert
	recLen = atoi(recSize);
	printf("%d\n", recLen);
	input = malloc(sizeof(char) * recLen);
	
	//fetch input string
	read(fd, input, recLen);
	strcat(input, "\0");
	printf("%s\n", input);
	
	//parse out arguments
	tok = strtok(input, "|");
	r.word = malloc(sizeof(char) * strlen(tok));
	strcpy(r.word, tok);
	tok = strtok(NULL, "|");
	r.pronounciation = malloc(sizeof(char) * strlen(tok));
	strcpy(r.pronounciation, tok);
	tok = strtok(NULL, "|");
	r.stress = malloc(sizeof(char) * strlen(tok));
	strcpy(r.stress, tok);
	tok = strtok(NULL, "|");
	r.foreign = atoi(tok);
	
	return r;
	
}

Page readPageAt(int RRN) {
	
	Page ret;
	char *buff;
	char *tok;
	char *subTok;
	int i = 0;
	int fd, pos;
	fd = open("index.txt", O_RDONLY);
	//collect string
	pos = lseek(fd, INDEX_FILE_HEADER_LENGTH + (PAGE_SIZE * 512), 0);
	read(fd, buff, 512);
	close(fd);
	
	//parse out page
	printf("%s\n", buff);
	tok = strtok(buff, "|");
	ret.keyCount = atoi(tok);
	tok = strtok(NULL, "|");
	subTok = strtok(tok, ",");
	do {
		
		char *t;
		char *key;
		t = strtok(subTok, " ");
		strcpy(key, t);
		t = strtok(NULL, " ");
		ret.key[i] = collectRecordAtIndex(key, atoi(t));
		i++;
		
	} while (subTok = strtok(NULL, ","));
	
	
	return ret;
	
}

/**generates and updates the data file header**/
void buildDataFileHeader(int flag, int recs) {
	
	char ret[30];
	int fd, pos;
	
	//build string
	sprintf(ret, "index.txt %d %d", flag, recs);
	DATA_FILE_HEADER_LENGTH = strlen(ret);
	
	//write to file
	fd = open("data.txt", O_WRONLY);
	pos = lseek(fd, 0, 0);
	write(fd, ret, DATA_FILE_HEADER_LENGTH);
	close(fd);
	
}

/**generates and updates the index file header**/
void buildIndexFileHeader(int headInd, int keyCount) {
	
	char ret[30];
	int fd, pos;
	
	//build string
	sprintf(ret, "%d %d %d", PAGE_SIZE, headInd, keyCount);
	INDEX_FILE_HEADER_LENGTH = strlen(ret);
	
	//write to file
	fd = open("index.txt", O_WRONLY);
	pos = lseek(fd, 0, 0);
	write(fd, ret, INDEX_FILE_HEADER_LENGTH);
	close(fd);
	
}



/**asks user for input and creates and stores record**/
int insertRecord(char *word, char *pron, char *stre, int fore) {
	
	Record r = initializeRecord(word, pron, stre, fore);
	
	//search tree
	
}

/**Displays list of available options**/
void displayOptions() {
	
	printf("\n1) Insert a record\n");
	printf("2) Search for a record\n");
	printf("3) Display current B-Tree\n");
	printf("4) Exit\n");
	printf(">");
	
}

Record buildRecordFromString(char *s) {
	
	Record ret;
	
	return ret;
	
}

Page loadPageFromString(char *s) {
	
	Page ret;
	char *tok;
	char *subParse;
	int i;
	
	tok = strtok(s, "|");
	ret.keyCount = atoi(tok);
	tok = strtok(NULL, "|");
	
	subParse = strtok(tok, ",");
	i = 0;
	do {
		
		
		i++;
		
	} while (subParse = strtok(NULL, ","));
	tok = strtok(NULL, "|");
	printf("%s\n", tok);
	
	return ret;
	
}
