/**
 * @file Common.h
 * @Brief  data struct common interface
 * @author wu yangtao , w_y_tao@163.com
 * @version version 1.0
 * @date 2016-03-21
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef int (*handle_element)(void *arg, void *element);
typedef int (*destroy_element)(void *element);
typedef int (*iterate_handle)(void *element);

typedef struct DataCommon{
    //the data's linked method that user chooses 
    void *linked_type;

    //match function
    handle_element remove_match;
    handle_element search_match;
    handle_element alter_match;
    destroy_element destroy_node;
    iterate_handle handle_iteration;

    //public handle list begin
    int (*insert)(struct DataCommon *common, void *element);
    int (*remove)(struct DataCommon *common, void *element);
    (void*) (*search)(struct DataCommon *common, void *element);
    int (*alter)(struct DataCommon *common, void *element);

    (void*) (*prior)(struct DataCommon *common, void *element);
    (void*) (*next)(struct DataCommon *common, void *element);

    int (*iterate)(struct DataCommon *common);
    int (*size)(struct DataCommon *common);
    int (*clear)(struct DataCommon *common);
    //public handle list end

}DataCommon;

#define DATA_COMMON_NULL {\
    .linked_type = NULL,\
    .remove_match = NULL,\
    .search_match = NULL,\
    .alter_match = NULL,\
    .destroy_node = NULL,\
    .insert = NULL,\
    .remove = NULL,\
    .search = NULL,\
    .alter = NULL,\
    .prior = NULL,\
    .next = NULL,\
    .iterate = NULL,\
    .size = NULL,\
    .clear = NULL\
}

#endif
