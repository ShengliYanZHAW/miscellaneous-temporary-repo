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

#include "file_io.h"
#include "person.h"
#include "list.h"


/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */
int main(int argc, char* argv[])
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	load_person_list(); // Requirement 1: Load data on start

	// Placeholder for application logic that would mutate the list.
	// For example, if you had a function to add a person:
	// add_new_person_interactive(); // This function would call list_insert()
	// store_person_list(); // Requirement 2: Store data after mutation

	// No explicit action needed for requirement 3 (close on exit) if
	// store_person_list() is the last operation that writes to the file,
	// as it handles closing the file. If the program could exit
	// without a final store_person_list() after a mutation,
	// then an explicit store_person_list() might be needed here or via atexit().
	// However, the tests will likely cover the mutation and storage.

	// END-STUDENTS-TO-ADD-CODE
    return EXIT_SUCCESS;
}
