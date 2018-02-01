#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_record.h"

int main() {
	
	record **r;
	
	r = malloc(sizeof(record*)*RECORD_COUNT);
	
	r[0] = createRecord("Ames", "John", "123 Maple", "Stillwater", "OK", "74075");
	r[1] = createRecord("Andrew", "Andrews", "66 Jones", "Stillwater", "OK", "74075");
	r[2] = createRecord("Francis", "Amelia", "55 Plain", "New York", "NY", "987123");
	r[3] = createRecord("Khan", "Zack", "16 Fredrick", "Toronto", "ON", "NNNNNN");
	r[4] = createRecord("Mason", "Alan", "90 Eastgate", "Ada", "ON", "N2L3G1");
	r[5] = createRecord("Rogers", "Bob", "321 Fake", "Toronto", "ON", "1A2B3C");
	r[6] = createRecord("Sebastian", "Simon", "444 Elm", "Waterloo", "ON", "L4A1W2");
	
	addRecordToFile(r);
	
	return 0;
	
}
