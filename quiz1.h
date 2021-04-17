#include <stddef.h>
#include <stdio.h>
typedef struct __node {                   
    int value;
    struct __node *next;
    struct __node *previous;
} node_t;
static inline void list_add_node_t(node_t **list, node_t *node_t) {
  if (!*list)
    node_t->previous = node_t;
  node_t->previous = (*list)->previous;
  node_t->next = *list;
  *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
    while (*left)
      left = &((*left)->next);
    *left = right;
}
#define MAX_LEVELS 100
void non_recursive_quicksort(node_t *list, node_t *tail) {
  if (!list || list->previous == list)
    return;
  int i = 0;
  node_t *l, *r;
  node_t *beg[MAX_LEVELS], *end[MAX_LEVELS];
  beg[0] = list;
  end[0] = tail;
  int pivot = list->value;
  while (i >= 0) {
    l = beg[i];
    r = end[i];
    if (l != r && l && r) {
      pivot = l->value;
      while (l != r && l && r) {
        while (r->value > pivot && l != r) {
          r = r->previous;
        }
        if (l != r) {
          l->value = r->value;
          l = l->next;
        }
        while (l->value < pivot && l != r)
          l = l->next;
        if (l != r) {
          r->value = l->value;
          r = r->previous;
        }
      }
      l->value = pivot;
      beg[i + 1] = l->next;
      end[i + 1] = end[i];
      end[i] = l;
      i = i + 1;
    } else
      i--;
  }
}
void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}
