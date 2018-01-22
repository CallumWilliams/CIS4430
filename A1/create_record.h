#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//search method - assume lastname + firstname concatenated (e.x. MASONALAN)

typedef struct rec {
	
	char last_name[5];
	char first_name[5];
	char street_address[10];
	char city_name[4];
	char province[2];
	char postal_code[6];
	
}Record;

Record *createRecord(char l[5], char f[5], char s[10], char c[4], char p[2], char po[6]) {
	
	Record *r = malloc(sizeof(Record));
	strcpy(r->last_name, l);
	strcpy(r->first_name, f);
	strcpy(r->street_address, s);
	strcpy(r->city_name, c);
	strcpy(r->province, p);
	strcpy(r->postal_code, po);
	
	return r;
	
}

char *buildRecordString(Record *r) {
	
	//temp
	char *ret = "\0";
	return ret;
	
}

int addRecordToData(Record *r) {
	
	int file = 0;
	
	//file = open("data.txt", O_CREAT | O_WRONLY, 0751);
	//char input = 
	
	return 0;
	
}
