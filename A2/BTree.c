#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#include "BTree.h"

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

/**writes converted string to the index file**/
void writeDataToIndexFile(int loc, char *s) {
	
	int fd;
	int pos;
	
	fd = open("index.txt", O_WRONLY);
	pos = lseek(fd, INDEX_FILE_HEADER_LENGTH + (loc * PAGE_SIZE) + 1, 0);
	write(fd, s, 512);
	close(fd);
	
}

/**checks to see if current node is a leaf node**/
int isLeafNode(Page r) {
	
	for (int i = 0; i < ORDER; i++) {
		if (r.child[i] != -1) {
			return 0;//found a non-terminal branch. False.
		}
	}
	
	//all branches are terminal. True.
	return 1;
	
}

/**searches for a record**/
SearchResults searchRecord(int RRN, char *key) {
	
	printf("RRN %d\n", RRN);
	Page p = readPageAt(RRN);
	
	if (isLeafNode(p) == 1) {
		//last check. If it's not found here it doesn't exist.
		for (int i = 0; i < ORDER - 1; i++) {
			if (strcmp(key, p.key[i].word) == 0) {
				printRecord(p.key[i]);
				return EXISTS;
			}
		}
		return NOT_EXISTS;
	} else {
		
		//find which branch to go to
		if (strcmp(key, p.key[0].word) < 0) {
			//branch leftmost
			return searchRecord(p.child[0], key);
		} else if (strcmp(key, p.key[0].word) == 0) {
			printRecord(p.key[0]);
			return EXISTS;
		}
		//check other branches
		for (int i = 1; i < p.keyCount; i++) {
			if (strcmp(key, p.key[i].word) < 0) {
				return searchRecord(p.child[i], key);
			} else if (strcmp(key, p.key[i].word) == 0) {
				printRecord(p.key[i]);
				return EXISTS;
			}
		}
		
		//if nothing found in loop, branch rightmost
		return searchRecord(p.child[p.keyCount], key);
		
	}
	
	return NOT_EXISTS;
	
}

/**displays list of available options**/
void displayOptions() {
	
	printf("\n1) Insert a record\n");
	printf("2) Search for a record\n");
	printf("3) Display current B-Tree\n");
	printf("4) Display header information\n");
	printf("5) Exit\n");
	printf("> ");
	
}

/**standard output for printing a record**/
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
