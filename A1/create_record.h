#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DATA_FILE "data.txt"
#define RECORD_SIZE 67
#define RECORD_COUNT 4

typedef struct RECORD {
	
	char last_name[10];
	char first_name[10];
	char st_addr[15];
	char city[15];
	char prov[2];
	char post[9];
	
}record;

record *createRecord(char l[10], char f[10], char s[15], char c[15], char pr[2], char po[9]) {
	
	record *r = malloc(sizeof(record));
	strcpy(r->last_name, l);
	strcpy(r->first_name, f);
	strcpy(r->st_addr, s);
	strcpy(r->city, c);
	strcpy(r->prov, pr);
	strcpy(r->post, po);
	return r;
	
}

char *buildHeaderString() {
	
	char *ret;
	
	ret = malloc(sizeof(char)*15);
	sprintf(ret, "index.txt|%d|%d|", RECORD_SIZE, RECORD_COUNT);
	
	return ret;
	
}

char *buildRecordString(record *r) {
	
	char *ret;
	ret = malloc(sizeof(char)*RECORD_SIZE);
	strcpy(ret, r->last_name);
	strcat(ret, "|");
	strcat(ret, r->first_name);
	strcat(ret, "|");
	strcat(ret, r->st_addr);
	strcat(ret, "|");
	strcat(ret, r->city);
	strcat(ret, "|");
	strcat(ret, r->prov);
	strcat(ret, "|");
	strcat(ret, r->post);
	strcat(ret, "|");
	return  ret;
	
}

void addRecordToFile(char *file, record **r) {
	
	int fd;
	int bytes, size;
	char *input;
	FILE *fp;
	
	fp = fopen(file, "w");
	fclose(fp);
	fp = fopen(file, "a");
	fputs(buildHeaderString(), fp);
	for (int i = 0; i < RECORD_COUNT; i++) {
		fputs(buildRecordString(r[i]), fp);
	}
	fclose(fp);
	
}
