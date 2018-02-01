#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int RECORD_SIZE;
int RECORD_COUNT;
int HEADER_SIZE;

void loadHeaderData(char *h) {
	
	char *token;
	
	token = strtok(h, "|");
	
	token = strtok(NULL, "|");
	RECORD_SIZE = atoi(token);
	
	token = strtok(NULL, "|");
	RECORD_COUNT = atoi(token);
	
}

int *loadIndexData(char *i) {
	
	int *ret;
	char *token;
	int j;
	
	ret = malloc(sizeof(int)*RECORD_COUNT);
	j = 0;
	token = strtok(i, " ");
	ret[j] = atoi(token);
	j++;
	while (token = strtok(NULL, " ")) {
		ret[j] = atoi(token);
		j++;
	}
	
}
