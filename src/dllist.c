#include "dsa/dllist.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dnode {
  void* data;
  struct dnode* prev;
  struct dnode* next;
} dnode_t;

struct dllist {
  dnode_t* head;
  dnode_t* tail;
};

dllist_t* dllist_create(void) {
  dllist_t* list = malloc(sizeof(struct dllist));

  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;

  return list;
}

void dllist_destroy(dllist_t* list) {
  if (list == NULL) {
    fprintf(stderr, "ERROR: List is not initialized\n");
    return;
  }

  dnode_t* current = list->head;
  while (current != NULL) {
    dnode_t* next = current->next;
    free(current->data);
    free(current);
    current = next;
  }

  free(list);
}

int dllist_append_front(dllist_t* list, void* new_data) {
  if (list == NULL) {
    fprintf(stderr, "ERROR: List is not initialized\n");
    return -1;
  }

  dnode_t* new_node = malloc(sizeof(dnode_t));
  if (new_node == NULL) {
    fprintf(stderr, "ERROR: Failed to allocated data for new node\n");
    return -1;
  }

  new_node->data = new_data;
  new_node->prev = NULL;

  // if list is empty
  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
    return 0;
  }

  dnode_t* curr_head = list->head;
  new_node->next = curr_head;
  curr_head->prev = new_node;
  list->head = new_node;

  return 0;
}

int dllist_delete_front(dllist_t* list, void** out_ptr) {
  // the base case
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: List is not initialized\n");
    return -1;
  }

  dnode_t* curr_head = list->head;

  if (out_ptr) {
    *(out_ptr) = curr_head->data;
  }

  list->head = curr_head->next;
  // now if the list becomes empty...
  if (list->head == NULL) {
    // set the tail to NULL too!
    list->tail = NULL;
    return 0;
  }

  // adjust the new head node's previous node
  list->head->next = NULL;
  free(curr_head);

  return 0;
}

int dllist_append_end(dllist_t* list, void* new_data);

int dllist_append_after(dllist_t* list, void* after, void* new_data);

int dllist_delete_end(dllist_t* list, void** out_ptr);

int dllist_delete_data(dllist_t* list, void* data);

int dllist_delete_after(dllist_t* list, void* after, void** out_ptr);

bool dllist_search(dllist_t* list, void* data);

typedef void (*dllist_print_fn)(void* data);

void dllist_print(const dllist_t* list, dllist_print_fn print_fn) {
  if (list == NULL || list->head == NULL) {
    fprintf(stderr, "ERROR: List is empty\n");
    return;
  }

  dnode_t* curr_node = list->head;
  while (curr_node != NULL) {
    print_fn(curr_node->data);
    curr_node = curr_node->next;
  }

  printf("NULL\n");
}
