#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#include "BTree.h"

/**setups for global variables**/
void initialSetup() {
	
	//was unable to store header in file successfully (overwrote values)
	//trivial algorithm for getting header lengths
	
	FILE *f1, *f2;
	int c, i;
	char tmp[10];
	
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
	//get PAGE_SIZE, HEAD_PAGE_INDEX and TOTAL_PAGES
	f2 = fopen("index.txt", "r");
	//get PAGE_SIZE
	c = fgetc(f2);
	memset(tmp, '\0', 10);
	i = 0;
	while (c != 32 && c != -1) {
		tmp[i] = c;
		i++;
		c = fgetc(f2);
	}
	PAGE_SIZE = atoi(tmp);
	
	//get HEAD_PAGE_INDEX
	c = fgetc(f2);
	memset(tmp, '\0', 10);
	i = 0;
	while (c != 32 && c != -1) {
		tmp[i] = c;
		i++;
		c = fgetc(f2);
	}
	HEAD_PAGE_INDEX = atoi(tmp);
	
	//get TOTAL_PAGES
	c = fgetc(f2);
	memset(tmp, '\0', 10);
	i = 0;
	while (c != 124 && c != -1) {
		tmp[i] = c;
		i++;
		c = fgetc(f2);
	}
	TOTAL_PAGES = atoi(tmp);
	
	fclose(f2);
	
}

/**prints header information**/
void printHeaders() {
	
	int fd, pos;
	char tok[30];
	
	fd = open("data.txt", O_RDONLY);
	lseek(fd, 0, 0);
	read(fd, tok, DATA_FILE_HEADER_LENGTH);
	printf("Data file: %s\n", tok);
	close(fd);
	
	memset(tok, '\0', 30);
	
	fd = open("index.txt", O_RDONLY);
	lseek(fd, 0, 0);
	read(fd, tok, INDEX_FILE_HEADER_LENGTH);
	printf("Index file: %s\n", tok);
	close(fd);
	
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
	input = malloc(sizeof(char) * recLen);
	
	//fetch input string
	read(fd, input, recLen);
	strcat(input, "\0");
	
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

/**goes to RRN on index.txt and reads page**/
Page readPageAt(int RRN) {
	
	Page ret;
	char buff[512];
	char *tok;
	char *keys, *children;
	int i = 0;
	int fd, pos, b;
	
	memset(buff, '\0', 512);
	fd = open("index.txt", O_RDONLY);
	
	//collect string
	pos = lseek(fd, INDEX_FILE_HEADER_LENGTH + (RRN * PAGE_SIZE) + 1, 0);
	b = read(fd, buff, 512);
	printf("%s\n", buff);
	close(fd);
	
	//parse out page
	tok = strtok(buff, "|");
	ret.keyCount = atoi(tok);
	
	//read keys
	tok = strtok(NULL, "|");
	keys = malloc(sizeof(char) * strlen(tok));
	strcpy(keys, tok);
	
	//read children
	tok = strtok(NULL, "|");
	children = malloc(sizeof(char) * strlen(tok));
	strcpy(children, tok);
	
	//read out keys
	int indexTrack = 0;
	for (int i = 0; i < ret.keyCount; i++) {
		
		//replacement strtok (need to keep track of place)
		int j, k;
		char arg[50];
		char ind[50];
		char key[50];
		
		memset(arg, '\0', 50);
		
		k = 0;
		//parse out full key
		for (indexTrack; keys[indexTrack] != ','; indexTrack++) {
			arg[k] = keys[indexTrack];
			k++;
		}
		
		memset(ind, '\0', 50);
		memset(key, '\0', 50);
		
		//parse out key
		for (j = 0; arg[j] != ' '; j++) {
			key[j] = arg[j];
		}
		
		k = 0;
		//parse out index
		for (j = j + 1; j < strlen(arg) + 1; j++) {
			ind[k] = arg[j];
			k++;
		}
		
		//fetch record from data file
		ret.key[i] = collectRecordAtIndex(key, atoi(ind));
		ret.keyIndex[i] = atoi(ind);
		indexTrack++;
		
	}
	
	//fetch children
	tok = strtok(children, ",");
	for (int i = 0; i < ORDER; i++) {
		
		ret.child[i] = atoi(tok);
		tok = strtok(NULL, ",");
		
	}
	
	return ret;
	
}

/**converts a page into a 512 byte string for the index file**/
char *buildDataRecordString(Page p) {
	
	char *ret = malloc(sizeof(ret)*512);
	int remaining;
	
	memset(ret, '\0', 512);
	
	//copy keyCount
	sprintf(ret, "%d|", p.keyCount);
	
	//copy keys and indices
	for (int i = 0; i < p.keyCount; i++) {
		
		sprintf(ret + strlen(ret), "%s %d", p.key[i].word, p.keyIndex[i]);
		if (i + 1 != p.keyCount) strcat(ret, ",");
		
	}
	strcat(ret, "|");
	
	//copy children
	for (int i = 0; i < ORDER; i++) {
		
		sprintf(ret + strlen(ret), "%d", p.child[i]);
		if (i + 1 != ORDER) strcat(ret, ", ");
		
	}
	
	//add remaining 512 bytes
	remaining = PAGE_SIZE - strlen(ret);
	for (int i = 0; i < remaining - 1; i++) {
		sprintf(ret + strlen(ret), " ");
	}
	ret[PAGE_SIZE-1] = '|';
	
	return ret;
	
}

/**writes converted string to the index file**/
void writeDataToIndexFile(int loc, char *s) {
	
	int fd;
	int pos;
	
	fd = open("index.txt", O_WRONLY);
	pos = lseek(fd, INDEX_FILE_HEADER_LENGTH + (loc * PAGE_SIZE) + 1, 0);
	write(fd, s, 512);
	close(fd);
	
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

/**searches for a record**/
SearchResults searchRecord(int RRN, char *key) {
	
	Page p = readPageAt(RRN);
	
	//find where the key should occur
	
	return NOT_EXISTS;
	
}

/**Displays list of available options**/
void displayOptions() {
	
	printf("\n1) Insert a record\n");
	printf("2) Search for a record\n");
	printf("3) Display current B-Tree\n");
	printf("4) Display header information\n");
	printf("5) Exit\n");
	printf("> ");
	
}

/**Standard output for printing a record**/
void printRecord(Record r) {
	
	printf("\tWord: %s\n", r.word);
	printf("\tPronounciation: %s\n", r.pronounciation);
	printf("\tStress: %s\n", r.stress);
	printf("\tForeign Index: %d\n", r.foreign);
	
}

/**Standard output for printing a page**/
void printPage(Page p) {
	
	printf("-------------------------------\n");
	//print records
	for (int i = 0; i < p.keyCount; i++) {
		
		printRecord(p.key[i]);
		
	}
	
	//print children (if there)
	for (int i = 0; i < p.keyCount + 1; i++) {
		
		if (p.child[i] != -1) {
			//printf("Child: %d\n", p.child[i]);
		}
		
	}
	printf("-------------------------------\n");
	
}

/**Parses through tree to print elements**/
void printTree(int RRN) {
	
	printf("Page Index: %d\n" , RRN);
	Page p = readPageAt(RRN);
	
	printPage(p);
	
	for (int i = 0; i < p.keyCount + 1; i++) {
		
		if (p.child[i] != -1) {//if node exists, print it.
			printTree(p.child[i]);
		}
		
	}
	
}
