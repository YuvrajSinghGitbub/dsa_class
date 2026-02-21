#ifndef DSA_DLLIST_H_
#define DSA_DLLIST_H_

#include <stdbool.h>

typedef struct dllist dllist_t;

// create the list and return a pointer to it
dllist_t* dllist_create(void);

// take a pointer to the list and destroy it iteratively
void dllist_destroy(dllist_t* list);

// append a new data at the front
// return: 0 if success, -1 if allocation failure
int dllist_append_front(dllist_t* list, void* new_data);

// remove from the front
// return: 0 if success, -1 if list is empty
// `out_ptr`: the pointer where the removed node's data is stored
int dllist_delete_front(dllist_t* list, void** out_ptr);

// append a new data at the end
// return: 0 if success, -1 if allocation failure
int dllist_append_end(dllist_t* list, void* new_data);

// append a new data after a value
// return: 0 if success, -1 if allocation failure
int dllist_append_after(dllist_t* list, void* after, void* new_data);

// remove from the end
// return: 0 if success, -1 if list is empty
// `out_ptr`: the pointer where the removed node's data is stored
int dllist_delete_end(dllist_t* list, void** out_ptr);

// remove a specific data
// return: 0 if success, -1 if list is empty or if after not present
int dllist_delete_data(dllist_t* list, void* data);

// remove data after a value
// return: 0 if success, -1 if list is empty or if after not present
// `out_ptr`: the pointer where the removed node's data is stored
int dllist_delete_after(dllist_t* list, void* after, void** out_ptr);

// search for a value in the list
bool dllist_search(dllist_t* list, void* data);

// the callback function to use for printing the list
typedef void (*dllist_print_fn)(void* data);

// itereate the entire list, printing the list in the process
void dllist_print(const dllist_t* list, dllist_print_fn print_fn);

#endif  // DSA_DLLIST_H_
