/**
 * @file test.c
 * @Brief  test linked list
 * @author wu yangtao , w_y_tao@163.com
 * @version version .10
 * @date 2016-03-24
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/**
 * Cunit headers
 */ 
#include "CUnit.h"
#include "Automated.h"
#include "Basic.h"
#include "Console.h"

/**
 * Test file headers
 */ 
#include "queue/Queue.h"
#include "util/Log.h"


/*************Test Case Begin*******************/

typedef struct Person{
    char *name;
    int age;
}Person;

Queue queue = QUEUE_INIT;

Person *p1, *p2, *p3, *p4;

void destroy_node(void *person)
{
    Person *p = (Person*)person;
    free(p->name);
    p->name = NULL;
    p->age = 0;
    free(p);
}

void display_node(void *person)
{ 
    Person *p = (Person*)person;
    INFO("name:%s age:%d", p->name, p->age);
}

void test_queue_in()
{
    p1 = (Person*)malloc(sizeof(Person));
    char *name1 = (char*)malloc(16);
    strcpy(name1, "tom");
    p1->name = name1;
    p1->age = 22;

    p2 = (Person*)malloc(sizeof(Person));
    char *name2 = (char*)malloc(16);
    strcpy(name2, "jack");
    p2->name = name2;
    p2->age = 23;

    p3 = (Person*)malloc(sizeof(Person));
    char *name3 = (char*)malloc(16);
    strcpy(name3, "jim");
    p3->name = name3;
    p3->age = 24;


    p4 = (Person*)malloc(sizeof(Person));
    char *name4 = (char*)malloc(16);
    strcpy(name4, "fitz");
    p4->name = name4;
    p4->age = 25;

    CU_ASSERT_EQUAL_FATAL(queue_in(&queue, p1), 0);
    CU_ASSERT_EQUAL_FATAL(queue_in(&queue, p2), 0);
    CU_ASSERT_EQUAL_FATAL(queue_in(&queue, p3), 0);
    CU_ASSERT_EQUAL_FATAL(queue_in(&queue, p4), 0);
    CU_ASSERT_EQUAL_FATAL(queue.queue_size, 4);
    CU_ASSERT_EQUAL_FATAL(queue.node_count, 4);
}

void test_queue_out()
{
    CU_ASSERT_PTR_EQUAL_FATAL(queue_out(&queue), p1);
    CU_ASSERT_PTR_EQUAL_FATAL(queue_out(&queue), p2);
    CU_ASSERT_PTR_EQUAL_FATAL(queue_out(&queue), p3);
    CU_ASSERT_PTR_EQUAL_FATAL(queue_out(&queue), p4);
    CU_ASSERT_EQUAL_FATAL(queue.queue_size, 0);
    CU_ASSERT_EQUAL_FATAL(queue.node_count, 4);
}

void test_queue_iterate()
{
    CU_ASSERT_EQUAL_FATAL(queue_iterate(&queue, display_node), 4);
}

void test_queue_clear()
{
    CU_ASSERT_EQUAL_FATAL(queue_clear(&queue, destroy_node), 4);
    CU_ASSERT_EQUAL_FATAL(queue.queue_size, 0);
    CU_ASSERT_EQUAL_FATAL(queue.node_count, 4);
}

void test_queue_delete()
{
    CU_ASSERT_EQUAL_FATAL(queue_delete(&queue, destroy_node), 4);
    CU_ASSERT_EQUAL_FATAL(queue.queue_size, 0);
    CU_ASSERT_EQUAL_FATAL(queue.node_count, 0);
}

/*************Test Case End*********************/



/**
 * add testcase, similar function in the same testcase
 * 
 * typedef struct CU_TestInfo {
 * 	const char  *pName;
 *	CU_TestFunc pTestFunc;
 *	} CU_TestInfo;
 *
 * Example:
 *
 * static CU_TestInfo testcase1[] = {
 * 	{ "test_function_name", test_function},
 * 	{ "test_function_name2", test_function2},
 * 	CU_TEST_INFO_NULL
 * };
 *
 * static CU_TestInfo testcase2[] = {
 * 	...
 * 	CU_TEST_INFO_NULL
 * };
 *
 */ 

static CU_TestInfo testcase1[] = {
    { "test_queue_in", test_queue_in},
    { "test_queue_out", test_queue_out},
    { "test_queue_in1", test_queue_in},
    { "test_queue_iterate", test_queue_iterate},
    { "test_queue_clear", test_queue_clear},
    { "test_queue_in2", test_queue_in},
    { "test_queue_iterate2", test_queue_iterate},
    { "test_queue_delete", test_queue_delete},
    CU_TEST_INFO_NULL
};

/**
 * add testcase to the suites
 * 
 * typedef struct CU_SuiteInfo {
 *     const char       *pName;         
 *     CU_InitializeFunc pInitFunc;     
 *     CU_CleanupFunc    pCleanupFunc;  
 *     CU_SetUpFunc      pSetUpFunc;    
 *     CU_TearDownFunc   pTearDownFunc; 
 *     CU_TestInfo      *pTests;        
 * } CU_SuiteInfo;
 *
 * Example:
 *
 * static CU_SuiteInfo suites[] = {
 * 	{"suite name", suite_success_init, suite_success_clean, NULL, NULL, testcase},
 * 	...
 * 	CU_SUITE_INFO_NULL
 * }
 *
 */

static int suite_success_init(void) 
{
    return 0; 
}
static int suite_success_clean(void) 
{
    return 0; 
}


static CU_SuiteInfo suites[] = {
    {"suite1", suite_success_init, NULL, NULL, NULL, testcase1},
    CU_SUITE_INFO_NULL
};



/**
 * add tests to the test framework
 *
 */ 
void AddTests(void)
{
    assert(NULL != CU_get_registry());
    assert(!CU_is_test_running());

    /* Register suites. */
    if (CU_register_suites(suites) != CUE_SUCCESS) {
	fprintf(stderr, "suite registration failed - %s\n",
		CU_get_error_msg());
	exit(EXIT_FAILURE);
    }

}


int main()
{
    if (CU_initialize_registry()) {
	printf("\nInitialization of Test Registry failed.");
    }else{

	LOG_FILE_OPEN("log.txt");

	AddTests();

	/*******Automated Mode(best)*********************
	 * CU_set_output_filename("TestAutomated");
	 * CU_list_tests_to_file();
	 * CU_automated_run_tests();
	 ******************************************/

	 CU_set_output_filename("TestAutomated");
	 CU_list_tests_to_file();
	 CU_automated_run_tests();
	/*******Basic Mode*********************
	 * mode can choose:
	 * typedef enum {
	 *   CU_BRM_NORMAL = 0, Normal mode - failures and run summary are printed [default].
	 *   CU_BRM_SILENT,     Silent mode - no output is printed except framework error messages.
	 *   CU_BRM_VERBOSE     Verbose mode - maximum output of run details.
	 * } CU_BasicRunMode;
	 ****************************************
	 *
	 * CU_basic_set_mode(CU_BRM_NORMAL);
	 * CU_basic_run_tests();
	 ******************************************/

	/*******Console Mode*********************
	 * CU_console_run_tests();
	 ******************************************/

	/*******Curses Mode*********************
	 * CU_curses_run_tests();
	 ******************************************/ 


	CU_cleanup_registry();
    }

    LOG_FILE_CLOSE();
    return 0;
}

