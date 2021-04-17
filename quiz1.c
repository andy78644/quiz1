#include "quiz1.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static void list_free(node_t *list) {
  while (list) {
    // printf("%d\n", (list)->value);
    node_t *tmp = (list)->next;
    free(list);
    list = tmp;
  }
}

static node_t *list_make_node_t(node_t *list, int value) {
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  newNode->value = value;
  newNode->next = list;
  if (!list)
    newNode->previous = newNode;
  else {
    newNode->previous = list->previous;
    list->previous = newNode;
  }
  return newNode;
}

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char **argv) {
  size_t count = 1;
  srand(time(NULL));
  printf("%ld\n", time(NULL));
  node_t *list = NULL;
  while (count--)
    list = list_make_node_t(list, random() % 1024);
  list_display(list);
  // quicksort(&list);
  non_recursive_quicksort(list, list->previous);
  list_display(list);

  if (!list_is_ordered(list))
    return EXIT_FAILURE;

  list_free(list);
  return EXIT_SUCCESS;
}        
