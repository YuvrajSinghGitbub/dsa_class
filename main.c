#include <stdio.h>
#include <stdlib.h>

#include "dsa/slist.h"

void print_int(void* data) {
  int value = *(int*)data;
  printf("%d -> ", value);
}

int main(void) {
  slist_t* list = slist_create();

  for (int i = 0; i <= 5; i++) {
    int* data = malloc(sizeof(int));
    *data = i * 10;
    slist_append_front(list, data);
  }
  // 50 -> 40 -> 30 -> 20 -> 10 -> 0 -> NULL;

  slist_print(list, print_int);

  return 0;
}
