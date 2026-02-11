#ifndef DSA_SLIST_H
#define DSA_SLIST_H

#include <stdbool.h>
#include <stddef.h>

// the structure that holds the list's head pointer
typedef struct slist slist_t;

// create a new list
slist_t* slist_create(void);

// destroy the list, freeing each node one by one
void slist_destroy(slist_t* list);

// append a new data at the front
// return: 0 if success, -1 if allocation failure
int slist_append_front(slist_t* list, void* new_data);

// remove from the front
// return: 0 if success, -1 if list is empty
// `out_ptr`: the pointer where the removed node's data is stored
int slist_delete_front(slist_t* list, void** out_ptr);

// append a new data at the end
// return: 0 if success, -1 if allocation failure
int slist_append_end(slist_t* list, void* new_data);

// append a new data after a value
// return: 0 if success, -1 if allocation failure
int slist_append_after(slist_t* list, void* after, void* new_data);

// remove from the end
// return: 0 if success, -1 if list is empty
// `out_ptr`: the pointer where the removed node's data is stored
int slist_delete_end(slist_t* list, void** out_ptr);

// remove a specific data
// return: 0 if success, -1 if list is empty or if after not present
int slist_delete_data(slist_t* list, void* data);

// remove data after a value
// return: 0 if success, -1 if list is empty or if after not present
// `out_ptr`: the pointer where the removed node's data is stored
int slist_delete_after(slist_t* list, void* after, void** out_ptr);

// search for a value in the list
bool slist_search(slist_t* list, void* data);

// the callback function to use for printing the list
typedef void (*slist_print_fn)(void* data);

// itereate the entire list, printing the list in the process
void slist_print(const slist_t* list, slist_print_fn print_fn);

#endif  // DSA_SLIST_H
