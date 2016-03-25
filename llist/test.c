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
#include "Common.h"
#include "llist/Linkedlist.h"
#include "util/Log.h"


/*************Test Case Begin*******************/

typedef struct Person{
    char *name;
    int age;
}Person;

DataCommon persons = DATA_COMMON_NULL;

Person *p1, *p2, *p3;

int match(void *person, void *name)
{
    if (strcmp(((Person*)person)->name, (char*)name) == 0)
	return 0;
    else
	return -1;
}

int alter_match(void *element, void *arg)
{
    Person *person = (Person*)element;
    Person *temp = (Person*)arg;

    if (strcmp(person->name, temp->name) == 0){
	person->age = temp->age;
	return 0;
    }else{
	return -1;
    }
}

int destroy_node(void *person)
{
    Person *p = (Person*)person;
    free(p->name);
    p->name = NULL;
    p->age = 0;
    free(p);

    return 0;
}

int handle_iteration(void *person)
{
    Person  *p = (Person*)person;
    INFO("name:%s age:%d", p->name, p->age);

    return 0;
}


void test_insert()
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

    CU_ASSERT_EQUAL_FATAL(persons.insert(&persons, p1), 0);
    CU_ASSERT_EQUAL_FATAL(persons.insert(&persons, p2), 0);
    CU_ASSERT_EQUAL_FATAL(persons.insert(&persons, p3), 0);
}

void test_iterate()
{
    CU_ASSERT_EQUAL_FATAL(persons.iterate(&persons), 0);
}

void test_alter()
{
    Person temp1 = {"tom", 32};
    Person temp2 = {"jack", 33};
    Person temp3 = {"jim", 34};
    CU_ASSERT_EQUAL_FATAL(persons.alter(&persons, &temp1), 0);
    CU_ASSERT_EQUAL_FATAL(persons.alter(&persons, &temp2), 0);
    CU_ASSERT_EQUAL_FATAL(persons.alter(&persons, &temp3), 0);
}

void test_size()
{
    CU_ASSERT_EQUAL_FATAL(persons.size(&persons), 3);
}

void test_prior()
{
    CU_ASSERT_PTR_EQUAL_FATAL(persons.prior(&persons, "tom"), NULL);
    CU_ASSERT_PTR_EQUAL_FATAL(persons.prior(&persons, "jack"), p1);
    CU_ASSERT_PTR_EQUAL_FATAL(persons.prior(&persons, "jim"), p2);
}


void test_next()
{
    CU_ASSERT_PTR_EQUAL_FATAL(persons.next(&persons, "tom"), p2);
    CU_ASSERT_PTR_EQUAL_FATAL(persons.next(&persons, "jack"), p3);
    CU_ASSERT_PTR_EQUAL_FATAL(persons.next(&persons, "jim"), NULL);
}

void test_search()
{
    CU_ASSERT_PTR_EQUAL_FATAL(persons.search(&persons, "tom"), p1);
    CU_ASSERT_PTR_EQUAL_FATAL(persons.search(&persons, "jack"), p2);
    CU_ASSERT_PTR_EQUAL_FATAL(persons.search(&persons, "jim"), p3);
}


void test_remove()
{
    CU_ASSERT_EQUAL_FATAL(persons.remove(&persons, "jack"), 0);
    CU_ASSERT_EQUAL_FATAL(persons.remove(&persons, "jim"), 0);
    CU_ASSERT_EQUAL_FATAL(persons.remove(&persons, "tom"), 0);
}

void test_clear()
{
    CU_ASSERT_EQUAL_FATAL(persons.clear(&persons), 3);
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
    { "test_insert", test_insert},
    { "test_iterate", test_iterate},
    { "test_search", test_search},
    CU_TEST_INFO_NULL
};

static CU_TestInfo testcase2[] = {
    { "test_alter", test_alter},
    { "test_iterate2", test_iterate},
    { "test_prior", test_prior},
    { "test_iterate5", test_iterate},
    { "test_next", test_next},
    { "test_iterate4", test_iterate},
    CU_TEST_INFO_NULL
};

static CU_TestInfo testcase3[] = {
    { "test_remove", test_remove},
    { "test_insert", test_insert},
    { "test_iterate3", test_iterate},
    { "test_clear", test_clear},
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
    persons.remove_match = match;
    persons.search_match = match;
    persons.alter_match = alter_match;
    persons.destroy_node = destroy_node;
    persons.handle_iteration = handle_iteration;

    llist_new(&persons);

    return 0; 
}
static int suite_success_clean(void) 
{
    llist_delete(&persons); 
    return 0; 
}


static CU_SuiteInfo suites[] = {
    {"suite1", suite_success_init, NULL, NULL, NULL, testcase1},
    {"suite2", NULL, NULL, NULL, NULL, testcase2},
    {"suite3", NULL, suite_success_clean, NULL, NULL, testcase3},
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

