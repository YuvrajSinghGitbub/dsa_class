#include "dsa/dllist.h"

typedef struct dnode {
  void* data;
  struct dnode* prev;
  struct dnode* next;
} dnode_t;

struct dllist {
  dnode_t* head;
  dnode_t* tail;
};

dllist_t* dllist_create(void);

void dllist_destroy(dllist_t* head);

int dllist_append_front(dllist_t* list, void* new_data);

int dllist_delete_front(dllist_t* list, void** out_ptr);

int dllist_append_end(dllist_t* list, void* new_data);

int dllist_append_after(dllist_t* list, void* after, void* new_data);

int dllist_delete_end(dllist_t* list, void** out_ptr);

int dllist_delete_data(dllist_t* list, void* data);

int dllist_delete_after(dllist_t* list, void* after, void** out_ptr);

bool dllist_search(dllist_t* list, void* data);

typedef void (*dllist_print_fn)(void* data);

void dllist_print(const dllist_t* list, dllist_print_fn print_fn);
