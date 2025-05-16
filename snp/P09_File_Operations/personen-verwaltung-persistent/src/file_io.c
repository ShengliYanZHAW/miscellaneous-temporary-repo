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
	if (!f) {
		f = fopen("person_list.csv", "w");
		if (!f) perror_and_exit("fopen");
		fclose(f);
		return;
	}
	char buffer[MAX_LEN];
	while (fgets(buffer, MAX_LEN, f)) {
		size_t len = strlen(buffer);
		if (len && (buffer[len-1] == '\n' || buffer[len-1] == '\r'))
			buffer[len-1] = '\0';
		person_t temp;
		person_from_csv_string(&temp, buffer);
		list_insert(&temp);
	}
	fclose(f);
	// END-STUDENTS-TO-ADD-CODE
}
