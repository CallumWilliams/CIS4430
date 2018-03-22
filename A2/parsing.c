#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "BTree.h"
#include "parsing.h"

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
