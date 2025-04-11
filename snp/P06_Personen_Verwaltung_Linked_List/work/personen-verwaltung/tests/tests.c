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
 * @brief Test suite for the given package.
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/wait.h>
 #include <time.h>
 #include <assert.h>
 #include <CUnit/Basic.h>
 #include "test_utils.h"
 #include "person.h"
 #include "list.h"
 
 #ifndef TARGET // must be given by the make file --> see test target
 #error missing TARGET define
 #endif
 
 /// @brief alias for EXIT_SUCCESS
 #define OK   EXIT_SUCCESS
 /// @brief alias for EXIT_FAILURE
 #define FAIL EXIT_FAILURE
 
 /// @brief The name of the STDOUT text file.
 #define OUTFILE "stdout.txt"
 /// @brief The name of the STDERR text file.
 #define ERRFILE "stderr.txt"
 
 #define TRACE_INDENT "\n                " ///< allow for better stdout formatting in case of error
 
 // setup & cleanup
 static int setup(void)
 {
	 remove_file_if_exists(OUTFILE);
	 remove_file_if_exists(ERRFILE);
	 return 0; // success
 }
 
 static int teardown(void)
 {
	 // Do nothing.
	 // Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
	 return 0; // success
 }
 
 // tests
 static void test_person_compare(void)
 {
	 // arrange
	 person_t p1 = {"Smith", "John", 30};
	 person_t p2 = {"Smith", "John", 30};
	 person_t p3 = {"Smith", "Jane", 30};
	 person_t p4 = {"Johnson", "Bob", 30};
	 person_t p5 = {"Smith", "John", 25};
	 
	 // act & assert
	 // Same person
	 CU_ASSERT_EQUAL(person_compare(&p1, &p2), 0);
	 
	 // Different first name (Smith, John vs Smith, Jane)
	 CU_ASSERT(person_compare(&p1, &p3) > 0);
	 CU_ASSERT(person_compare(&p3, &p1) < 0);
	 
	 // Different last name (Smith vs Johnson)
	 CU_ASSERT(person_compare(&p1, &p4) > 0);
	 CU_ASSERT(person_compare(&p4, &p1) < 0);
	 
	 // Different age (30 vs 25)
	 CU_ASSERT(person_compare(&p1, &p5) > 0);
	 CU_ASSERT(person_compare(&p5, &p1) < 0);
 }
 
 static void test_list_insert(void)
 {
	 // arrange
	 node_t anchor;
	 list_init(&anchor);
	 
	 person_t p1 = {"Smith", "John", 30};
	 person_t p2 = {"Johnson", "Bob", 25};
	 person_t p3 = {"Wilson", "Jane", 35};
	 
	 // act & assert
	 // Insert first person
	 CU_ASSERT_EQUAL(list_insert(&anchor, &p1), 0);
	 CU_ASSERT_EQUAL(list_is_empty(&anchor), 0); // List should not be empty
	 CU_ASSERT_EQUAL(anchor.next->content.age, 30);
	 CU_ASSERT_EQUAL(strncmp(anchor.next->content.name, "Smith", NAME_LEN), 0);
	 
	 // Insert a person before the first (alphabetically)
	 CU_ASSERT_EQUAL(list_insert(&anchor, &p2), 0);
	 CU_ASSERT_EQUAL(anchor.next->content.age, 25);
	 CU_ASSERT_EQUAL(strncmp(anchor.next->content.name, "Johnson", NAME_LEN), 0);
	 
	 // Insert a person after the others (alphabetically)
	 CU_ASSERT_EQUAL(list_insert(&anchor, &p3), 0);
	 
	 // Try to insert a duplicate
	 CU_ASSERT_EQUAL(list_insert(&anchor, &p1), -1);
	 
	 // Clean up
	 list_clear(&anchor);
 }
 
 static void test_list_remove(void)
 {
	 // arrange
	 node_t anchor;
	 list_init(&anchor);
	 
	 person_t p1 = {"Smith", "John", 30};
	 person_t p2 = {"Johnson", "Bob", 25};
	 person_t p3 = {"Wilson", "Jane", 35};
	 person_t p4 = {"Parker", "Peter", 20}; // Not in the list
	 
	 // Insert persons
	 list_insert(&anchor, &p1);
	 list_insert(&anchor, &p2);
	 list_insert(&anchor, &p3);
	 
	 // act & assert
	 // Remove middle person
	 CU_ASSERT_EQUAL(list_remove(&anchor, &p1), 0);
	 
	 // Remove first person
	 CU_ASSERT_EQUAL(list_remove(&anchor, &p2), 0);
	 
	 // Remove last person
	 CU_ASSERT_EQUAL(list_remove(&anchor, &p3), 0);
	 
	 // List should be empty now
	 CU_ASSERT(list_is_empty(&anchor));
	 
	 // Try to remove from an empty list
	 CU_ASSERT_EQUAL(list_remove(&anchor, &p4), -1);
	 
	 // Try to remove a person not in the list
	 list_insert(&anchor, &p1);
	 CU_ASSERT_EQUAL(list_remove(&anchor, &p4), -1);
	 
	 // Clean up
	 list_clear(&anchor);
 }
 
 static void test_list_clear(void)
 {
	 // arrange
	 node_t anchor;
	 list_init(&anchor);
	 
	 person_t p1 = {"Smith", "John", 30};
	 person_t p2 = {"Johnson", "Bob", 25};
	 person_t p3 = {"Wilson", "Jane", 35};
	 
	 // Insert persons
	 list_insert(&anchor, &p1);
	 list_insert(&anchor, &p2);
	 list_insert(&anchor, &p3);
	 
	 // act
	 list_clear(&anchor);
	 
	 // assert
	 CU_ASSERT(list_is_empty(&anchor));
	 
	 // Insert again after clearing
	 CU_ASSERT_EQUAL(list_insert(&anchor, &p1), 0);
	 
	 // Clean up
	 list_clear(&anchor);
 }
 
 /**
  * @brief Registers and runs the tests.
  * @returns success (0) or one of the CU_ErrorCode (>0)
  */
 int main(void)
 {
	 // setup, run, teardown
	 TestMainBasic("lab test", setup, teardown
				   , test_person_compare
				   , test_list_insert
				   , test_list_remove
				   , test_list_clear
				   );
 }