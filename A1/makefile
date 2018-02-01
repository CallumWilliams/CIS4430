all: create_record find_record
	
create_record: create_record.c create_record.h
	gcc create_record.c -o create_record

find_record: find_record.c find_record.h
	gcc find_record.c -o find_record

clean:
	rm create_record
	rm find_record
