#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_record.h"

int main(int argc, char *argv[]) {
	
	int fd;
	long pos;
	char query[20];
	
	char *header_size_str;
	char *rec;
	
	if (argc < 2) {
		printf("Please run as \"./find_record <INPUT_FILE>\"\n");
		exit(1);
	}
	
	if (access(argv[1], F_OK) == -1) {
		printf("Error - input file does not exist\n");
		exit(1);
	}
	
	//perform initial header parse
	fd = open(argv[1], O_RDONLY);
	header_size_str = malloc(sizeof(char)*2);
	read(fd, header_size_str, 2);
	HEADER_SIZE = atoi(header_size_str);
	header_size_str = (char*)realloc(header_size_str, sizeof(char)*HEADER_SIZE);
	read(fd, header_size_str, HEADER_SIZE-2);
	loadHeaderData(header_size_str);
	free(header_size_str);
	close(fd);
	
	printf("Search records via \"<LASTNAME><FIRSTNAME>\"\n");
	printf("Type \"exit\" to terminate\n\n");
	rec = malloc(sizeof(char)*RECORD_SIZE);
	do {
		
		printf("Search record > ");
		scanf("%s", query);
		
		if (strcmp(query, "exit") == 0) break;
		rec = searchRecords(argv[1], query);
		
		
	} while(1);
	
	printf("Program terminated.\n");
	return 0;
	
}
