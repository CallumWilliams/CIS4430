#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DATA_FILE "data.txt"
#define RECORD_SIZE 50
#define RECORD_COUNT 4

typedef struct RECORD {
	
	char last_name[8];
	char first_name[8];
	char st_addr[10];
	char city[10];
	char prov[2];
	char post[6];
	
}record;

record *createRecord(char l[8], char f[8], char s[10], char c[10], char pr[2], char po[6]) {
	
	record *r = malloc(sizeof(record));
	strcpy(r->last_name, l);
	strcpy(r->first_name, f);
	strcpy(r->st_addr, s);
	strcpy(r->city, c);
	strcpy(r->prov, pr);
	strcpy(r->post, po);
	return r;
	
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
	for (int i = 0; i < RECORD_COUNT; i++) {
		fputs(buildRecordString(r[i]), fp);
	}
	fclose(fp);
	//fd = open(DATA_FILE, O_WRONLY | O_CREAT, 0751);
	//input = buildRecordString(r);
	//size = strlen(input)+1;
	//bytes = write(fd, input, size);
	//if (bytes != size) {
		//printf("Write error\n");
		//exit(1);
	//}
	
}
