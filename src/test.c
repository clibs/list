
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// Helpers

#define test(fn) \
  puts("... test " # fn); \
  test_##fn();

static int freeProxyCalls = 0;

void
freeProxy(void *val) {
  ++freeProxyCalls;
  free(val);
}

// Tests

void
test_ListNode_new() {
  char *val = "some value";
  ListNode *node = ListNode_new(val);
  assert(node->val == val);
}

void
test_List_push() {
  // Setup
  List *list = List_new();
  ListNode *a = ListNode_new("a");
  ListNode *b = ListNode_new("b");
  ListNode *c = ListNode_new("c");

  // a b c 
  List_push(list, a);
  List_push(list, b);
  List_push(list, c);

  // Assertions
  assert(list->head == a);
  assert(list->tail == c);
  assert(list->len == 3);
  assert(a->next == b);
  assert(a->prev == NULL);
  assert(b->next == c);
  assert(b->prev == a);
  assert(c->next == NULL);
  assert(c->prev == b);
}

void
test_List_unshift() {
  // Setup
  List *list = List_new();
  ListNode *a = ListNode_new("a");
  ListNode *b = ListNode_new("b");
  ListNode *c = ListNode_new("c");

  // c b a 
  List_push(list, a);
  List_unshift(list, b);
  List_unshift(list, c);

  // Assertions
  assert(list->head == c);
  assert(list->tail == a);
  assert(list->len == 3);
  assert(a->next == NULL);
  assert(a->prev == b);
  assert(b->next == a);
  assert(b->prev == c);
  assert(c->next == b);
  assert(c->prev == NULL);
}

void
test_List_destroy() {
  // Setup
  List *a = List_new();
  List_destroy(a);
  
  // a b c
  List *b = List_new();
  List_push(b, ListNode_new("a"));
  List_push(b, ListNode_new("b"));
  List_push(b, ListNode_new("c"));
  List_destroy(b);

  // Assertions
  List *c = List_new();
  c->free = freeProxy;
  List_push(c, ListNode_new(ListNode_new("a")));
  List_push(c, ListNode_new(ListNode_new("b")));
  List_push(c, ListNode_new(ListNode_new("c")));
  List_destroy(c);
  assert(freeProxyCalls == 3);
}

void
test_ListIterator() {
  // Setup
  List *list = List_new();
  ListNode *tj = ListNode_new("tj");
  ListNode *taylor = ListNode_new("taylor");
  ListNode *simon = ListNode_new("simon");
  
  // tj taylor simon
  List_push(list, tj);
  List_push(list, taylor);
  List_push(list, simon);
  
  // Assertions
  
  // From head
  ListIterator *it = ListIterator_new(list, LIST_HEAD);
  ListNode *a = ListIterator_next(it);
  ListNode *b = ListIterator_next(it);
  ListNode *c = ListIterator_next(it);
  ListNode *d = ListIterator_next(it);
  
  assert(a == tj);
  assert(b == taylor);
  assert(c == simon);
  assert(d == NULL);

  // From tail
  it = ListIterator_new(list, LIST_TAIL);
  ListNode *a2 = ListIterator_next(it);
  ListNode *b2 = ListIterator_next(it);
  ListNode *c2 = ListIterator_next(it);
  ListNode *d2 = ListIterator_next(it);
  
  assert(a2 == simon);
  assert(b2 == taylor);
  assert(c2 == tj);
  assert(d2 == NULL);
  ListIterator_destroy(it);
}

int
main(int argc, const char **argv){
  printf("\nList: %db\n", sizeof(List));
  printf("ListNode: %db\n", sizeof(ListNode));
  printf("ListIterator: %db\n\n", sizeof(ListIterator));
  test(ListNode_new);
  test(List_push);
  test(List_unshift);
  test(List_destroy);
  test(ListIterator);
  puts("... done\n");
  return 0;
}