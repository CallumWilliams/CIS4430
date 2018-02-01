#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DATA_FILE "data.txt"
#define INDEX_FILE "index.txt"
#define RECORD_SIZE 67
#define RECORD_COUNT 7
int HEADER_SIZE;

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
	sprintf(ret, "%s|%d|%d|", INDEX_FILE, RECORD_SIZE, RECORD_COUNT);
	HEADER_SIZE = strlen(ret)+1;
	sprintf(ret, "%d|%s|%d|%d|", HEADER_SIZE+2, INDEX_FILE, RECORD_SIZE, RECORD_COUNT);
	
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

char *convertIndexToString(int i) {
	
	char *ret;
	sprintf(ret, "%d ", i);
	
	return ret;
	
}

void addRecordToFile(record **r) {
	
	FILE *fp1;
	FILE *fp2;
	int index;
	
	fp1 = fopen(DATA_FILE, "w");
	fclose(fp1);
	fp2 = fopen(INDEX_FILE, "w");
	fclose(fp2);
	
	index = 0;
	fp1 = fopen(DATA_FILE, "a");
	fp2 = fopen(INDEX_FILE, "a");
	fputs(buildHeaderString(), fp1);
	for (int i = 0; i < RECORD_COUNT; i++) {
		fputs(buildRecordString(r[i]), fp1);
		fputs(convertIndexToString(index), fp2);
		index += RECORD_SIZE;
	}
	fclose(fp1);
	fclose(fp2);
	
}
