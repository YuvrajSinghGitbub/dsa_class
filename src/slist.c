#include "dsa/slist.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void* data;
  struct node* next;
} node_t;

struct slist {
  node_t* head;
  node_t* tail;
};

slist_t* slist_create(void) {
  slist_t* list = malloc(sizeof(struct slist));

  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;

  return list;
}

void slist_destroy(slist_t* list) {
  if (!list) {
    fprintf(stderr, "List is already empty\n");
    return;
  }

  node_t* curr_node = list->head;

  while (curr_node != NULL) {
    node_t* next_node = curr_node->next;
    free(curr_node);
    curr_node = next_node;
  }

  free(list);
}

int slist_append_front(slist_t* list, void* new_data) {
  if (!list) {
    fprintf(stderr, "ERROR: No list present\n");
    return -1;
  }

  node_t* new_node = malloc(sizeof(node_t));
  if (!new_node) {
    return -1;
  }

  new_node->data = new_data;
  new_node->next = list->head;

  list->head = new_node;

  // add tail too if list was empty
  if (list->tail == NULL) {
    list->tail = list->head;
  }

  return 0;
}

int slist_delete_front(slist_t* list, void** out_ptr) {
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: No list present\n");
    return -1;
  }

  node_t* old_head = list->head;

  if (out_ptr) {
    *out_ptr = old_head->data;
  }

  // the new list head can become null
  list->head = old_head->next;

  // so if it becomes null, set tail to null too!
  if (list->head == NULL) {
    list->tail = NULL;
  }

  free(old_head);

  return 0;
}

int slist_append_end(slist_t* list, void* new_data) {
  if (!list) {
    fprintf(stderr, "ERROR: No list present\n");
    return -1;
  }

  node_t* new_node = malloc(sizeof(node_t));
  if (!new_node) {
    return -1;
  }

  new_node->data = new_data;
  new_node->next = NULL;

  // if there was no head
  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
    return 0;
  }

  list->tail->next = new_node;
  list->tail = new_node;

  return 0;
}

int slist_delete_end(slist_t* list, void** out_ptr) {
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: No list present\n");
    return -1;
  }

  // save the data to `out_ptr`
  if (out_ptr) {
    *out_ptr = list->tail->data;
  }

  // if there is only one node
  if (list->head == list->tail) {
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    return 0;
  }

  // else just go one node before the tail
  node_t* curr_node = list->head;

  while (curr_node->next != list->tail) {
    curr_node = curr_node->next;
  }

  node_t* target_node = curr_node->next;

  free(target_node);
  list->tail = curr_node;

  return 0;
}

int slist_append_after(slist_t* list, void* after, void* new_data) {
  if (!list) {
    fprintf(stderr, "ERROR: No list provided\n");
    return -1;
  }

  node_t* curr_node = list->head;

  while (curr_node != NULL && curr_node->data != after) {
    curr_node = curr_node->next;
  }

  if (!curr_node) {
    fprintf(stderr, "ERROR: after not found\n");
    return -1;
  }

  node_t* new_node = malloc(sizeof(node_t));
  if (!new_node) {
    return -1;
  }

  new_node->data = new_data;
  new_node->next = NULL;

  new_node->next = curr_node->next;
  curr_node->next = new_node;

  // if the insertion happened after the tail
  if (curr_node == list->tail) {
    list->tail = new_node;
  }

  return 0;
}

int slist_delete_after(slist_t* list, void* after, void** out_ptr) {
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: No list provided\n");
    return -1;
  }

  node_t* curr_node = list->head;
  while (curr_node != NULL && curr_node->data != after) {
    curr_node = curr_node->next;
  }

  if (!curr_node) {
    fprintf(stderr, "ERROR: after not found\n");
    return -1;
  }

  node_t* node_to_delete = curr_node->next;

  // say [a] -> [b] -> [c] -> 0
  // and say delete after [c] then what?
  // does it makes sense to delete ...
  if (node_to_delete == NULL) {
    return -1;
  }

  // write to the `out_ptr`
  if (out_ptr) {
    *out_ptr = curr_node->data;
  }

  curr_node->next = node_to_delete->next;

  if (node_to_delete == list->tail) {
    list->tail = curr_node;
  }

  free(node_to_delete);

  return 0;
}

int slist_delete_data(slist_t* list, void* data) {
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: No list provided\n");
    return -1;
  }

  node_t* curr_node = list->head;

  if (curr_node->data == data) {
    return slist_delete_front(list, NULL);
  }

  // walk just before we find the data which to delete
  while (curr_node->next != NULL && curr_node->next->data != data) {
    curr_node = curr_node->next;
  }

  if (curr_node->next == NULL) {
    return -1;
  }

  node_t* node_to_delete = curr_node->next;
  curr_node->next = node_to_delete->next;

  if (node_to_delete == list->tail) {
    list->tail = curr_node;
  }

  free(node_to_delete);

  return 0;
}

bool slist_search(struct slist* list, void* data) {
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: List is empty\n");
    return false;
  }

  node_t* curr_ptr = list->head;
  while (curr_ptr->next != NULL) {
    if (curr_ptr->data == data) {
      return true;
    }

    curr_ptr = curr_ptr->next;
  }

  return false;
}

void slist_print(const struct slist* list, slist_print_fn print_fn) {
  if (!list || list->head == NULL) {
    fprintf(stderr, "ERROR: List is empty\n");
    return;
  }

  node_t* curr_node = list->head;
  while (curr_node != NULL) {
    print_fn(curr_node->data);
    curr_node = curr_node->next;
  }
}
