#include <stdio.h>
#include <stdlib.h>
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
	
	return ret;
	
}

char *buildKey(char *rec) {
	
	char *key;
	char *token;
	
	key = malloc(sizeof(char)*20);
	token = strtok(rec, "|");
	strcpy(key, token);
	token = strtok(NULL, "|");
	strcat(key, token);
	
	return key;
	
}

char *searchRecords(char *dataRecords, char *toSearch) {
	
	int fd;
	int pos;
	int cmp;
	char *index_cont_str;
	int *index;
	
	int mid;
	int records_left;
	char *key;
	char *token;
	char *ret;
	char tmp[100];
	
	//build index locations
	fd = open("index.txt", O_RDONLY);
	pos = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, 0);
	index_cont_str = malloc(sizeof(char)*pos);
	read(fd, index_cont_str, pos);
	index = loadIndexData(index_cont_str);
	close(fd);
	
	records_left = RECORD_COUNT;
	mid = floor(RECORD_COUNT/2);
	
	do {
		
		pos = index[mid];
		
		ret = malloc(sizeof(char)*RECORD_SIZE);
		fd = open("data.txt", O_RDONLY);
		lseek(fd, HEADER_SIZE + pos, SEEK_SET);
		read(fd, ret, RECORD_SIZE);
		
		key = malloc(sizeof(char)*20);
		key = buildKey(ret);
		
		cmp = strcmp(key, toSearch);
		printf("%s vs %s\n", key, toSearch);
		
		if (cmp == 0) {//found it
			printf("Record found\n");
			return ret;
		} else if (cmp < 0) {//go to the right
			records_left = floor(records_left/2);
			mid = mid + records_left;
			printf("Going right - new mid: %d, records left: %d\n", mid, records_left);
		} else {//go to the left
			records_left = floor(records_left/2);
			mid = mid - records_left;
			printf("Going left - new mid: %d, records left: %d\n", mid, records_left);
		}
		//scanf("%s", tmp);
		
	} while (records_left != 0);
	
	printf("Entry not found\n");
	return NULL;
	
}
