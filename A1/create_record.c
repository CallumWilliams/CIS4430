#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_record.h"

int main() {
	
	record **r;
	
	r = malloc(sizeof(record*)*RECORD_COUNT);
	
	r[0] = createRecord("Mason", "Alan", "90 Eastgate", "Ada", "ON", "N2L3G1");
	r[1] = createRecord("Ames", "John", "123 Maple", "Stillwater", "OK", "74075");
	r[2] = createRecord("Rogers", "Bob", "321 Fake", "Toronto", "ON", "1A2B3C");
	r[3] = createRecord("Francis", "Amelia", "55 Plain", "New York", "NY", "987123");
	
	addRecordToFile(DATA_FILE, r);
	
	return 0;
	
}
