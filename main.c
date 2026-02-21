#include <stdio.h>
#include <stdlib.h>

#include "dsa/dllist.h"
#include "dsa/slist.h"

void print_int(void* data) {
  int value = *(int*)data;
  printf("%d -> ", value);
}

void dlist_print_int(void* data) {
  int value = *(int*)data;
  printf("%d - ", value);
}

void test_single_list(void) {
  slist_t* list = slist_create();

  for (int i = 0; i <= 5; i++) {
    int* data = malloc(sizeof(int));
    *data = i * 10;
    slist_append_front(list, data);
  }

  slist_print(list, print_int);
  slist_destroy(list);
}

void test_dlist(void) {
  dllist_t* list = dllist_create();

  for (int i = 5; i > 0; i--) {
    int* data = malloc(sizeof(int));
    *data = i;
    dllist_append_front(list, data);
  }

  dllist_print(list, dlist_print_int);

  dllist_delete_front(list, NULL);  // 1
  dllist_delete_front(list, NULL);  // 2
  dllist_delete_front(list, NULL);  // 3
  dllist_delete_front(list, NULL);  // 4
  dllist_delete_front(list, NULL);  // 5

  dllist_print(list, dlist_print_int);

  for (int i = 5; i > 0; i--) {
    int* data = malloc(sizeof(int));
    *data = i;
    dllist_append_end(list, data);
  }
  dllist_print(list, dlist_print_int);

  dllist_destroy(list);
}

int main(void) {
  test_dlist();
  return 0;
}
