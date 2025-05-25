/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "person.h"
#include "list.h"

void perror_and_exit(const char *context) { perror(context); exit(EXIT_FAILURE); } // das muss noch an einen anderen Ort, scia

// May divide your code in further functions
// BEGIN-STUDENTS-TO-ADD-CODE

// END-STUDENTS-TO-ADD-CODE

void store_person_list(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	FILE *f = fopen("person_list.csv", "w");
	if (!f) perror_and_exit("fopen");
	char buffer[MAX_LEN];
	person_t *p = list_getFirst();
	while (p) {
		person_to_csv_string(p, buffer);
		fprintf(f, "%s\n", buffer);
		p = list_getNext();
	}
	fclose(f);
	// END-STUDENTS-TO-ADD-CODE
}

void load_person_list(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	FILE *f = fopen("person_list.csv", "r");
	if (!f) { // File does not exist
		// As per requirement 1: "sonst wird eine leere Datei kreiert und geöffnet"
		// "geöffnet" implies it's ready for potential future operations,
		// but for load, it means we start with an empty list.
		f = fopen("person_list.csv", "w"); // Create an empty file
		if (!f) perror_and_exit("fopen create empty for load");
		fclose(f); // Close it immediately, list remains empty.
		return; 
	}
	char buffer[MAX_LEN]; // MAX_LEN from person.h
	while (fgets(buffer, MAX_LEN, f)) {
		size_t len = strlen(buffer);
		// Remove newline characters at the end of the buffer
		if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0'; // single-char newline literal and null
            len--; // Adjust length
        }
        if (len > 0 && buffer[len-1] == '\r') { // Handle CR for CRLF or old Mac CR
            buffer[len-1] = '\0'; // single-char carriage-return literal and null
        }

        if (strlen(buffer) == 0) { // Skip empty or effectively empty lines
            continue;
        }
		person_t temp;
		person_from_csv_string(&temp, buffer); // person_from_csv_string is in person.c
		list_insert(&temp); // list_insert is from list.h/list.c
	}
	fclose(f);
	// END-STUDENTS-TO-ADD-CODE
}
