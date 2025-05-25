#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "test_utils.h"

// Test configuration
#ifndef TARGET
#define TARGET "../bin/person_server"
#endif

// Test setup and teardown
static int setup(void)
{
    // Create any necessary test files or initialize test environment
    remove("test_output.txt");
    return 0; // Success
}

static int teardown(void)
{
    // Clean up any test files
    remove("test_output.txt");
    return 0; // Success
}

// Test cases
static void test_basic_functionality(void)
{
    // Basic sanity test to verify build system works
    CU_ASSERT_EQUAL(1, 1);
    
    // Test the existence of the target binary
    FILE *f = fopen(TARGET, "rb");
    CU_ASSERT_PTR_NOT_NULL(f);
    if (f) {
        fclose(f);
    }
}

/**
 * @brief Registers and runs the tests.
 */
int main(void)
{
    // Initialize the CUnit test registry and add a suite
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }
    
    // Add suite to registry
    CU_pSuite suite = CU_add_suite("P10_IPC Tests", setup, teardown);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    // Add tests to suite
    if (!CU_add_test(suite, "Basic Functionality", test_basic_functionality)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    // Run tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failures = CU_get_number_of_failures();
    CU_cleanup_registry();
    
    return failures;
}
