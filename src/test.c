
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define test(fn) \
  puts("... " # fn); \
  fn();

void
testListNode_new() {
  char *val = "some value";
  ListNode *node = ListNode_new(val);
  assert(node->val == val);
}

void
testList_push() {
  List *list = List_new();
  ListNode *a = ListNode_new("a");
  ListNode *b = ListNode_new("b");
  ListNode *c = ListNode_new("c");
  List_push(list, a);
  List_push(list, b);
  List_push(list, c);
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

int
main(int argc, const char **argv){
  putchar('\n');
  test(testListNode_new);
  test(testList_push);
  puts("... done\n");
  return 0;
}