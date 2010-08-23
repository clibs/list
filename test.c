
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "src/list.h"

// Helpers

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

static int freeProxyCalls = 0;

void
freeProxy(void *val) {
  ++freeProxyCalls;
  free(val);
}

typedef struct {
  char *name;
} User;

static int
User_equal(User *a, User *b) {
  return 0 == strcmp(a->name, b->name); 
}

// Tests

static void
test_ListNode_new() {
  char *val = "some value";
  ListNode *node = ListNode_new(val);
  assert(node->val == val);
}

static void
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

static void
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

static void
test_List_at() {
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
  assert(a == List_at(list, 0));
  assert(b == List_at(list, 1));
  assert(c == List_at(list, 2));
  assert(NULL == List_at(list, 3));

  assert(c == List_at(list, -1));
  assert(b == List_at(list, -2));
  assert(a == List_at(list, -3));
  assert(NULL == List_at(list, -4));
}

static void
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

static void
test_List_find() {
  // Setup
  List *langs = List_new();
  ListNode *js = List_push(langs, ListNode_new("js"));
  ListNode *ruby = List_push(langs, ListNode_new("ruby"));

  List *users = List_new();
  users->match = User_equal;
  User userTJ = { "tj" };
  User userSimon = { "simon" };
  User userTaylor = { "taylor" };
  ListNode *tj = List_push(users, ListNode_new(&userTJ));
  ListNode *simon = List_push(users, ListNode_new(&userSimon));

  // Assertions
  ListNode *a = List_find(langs, "js");
  ListNode *b = List_find(langs, "ruby");
  ListNode *c = List_find(langs, "foo");
  assert(a == js);
  assert(b == ruby);
  assert(c == NULL);

  a = List_find(users, &userTJ);
  b = List_find(users, &userSimon);
  c = List_find(users, &userTaylor);
  assert(a == tj);
  assert(b == simon);
  assert(c == NULL);
}

static void
test_List_remove() {
  // Setup
  List *list = List_new();
  ListNode *a = List_push(list, ListNode_new("a"));
  ListNode *b = List_push(list, ListNode_new("b"));
  ListNode *c = List_push(list, ListNode_new("c"));

  // Assertions
  assert(list->len == 3);

  List_remove(list, b);
  assert(list->len == 2);
  assert(list->head == a);
  assert(list->tail == c);
  assert(a->next == c);
  assert(a->prev == NULL);
  assert(c->next == NULL);
  assert(c->prev == a);

  List_remove(list, a);
  assert(list->len == 1);
  assert(list->head == c);
  assert(list->tail == c);
  assert(c->next == NULL);
  assert(c->prev == NULL);

  List_remove(list, c);
  assert(list->len == 0);
  assert(list->head == NULL);
  assert(list->tail == NULL);
}

static void
test_List_pop() {
  // Setup
  List *list = List_new();
  ListNode *a = List_push(list, ListNode_new("a"));
  ListNode *b = List_push(list, ListNode_new("b"));
  ListNode *c = List_push(list, ListNode_new("c"));

  // Assertions
  assert(3 == list->len);
  
  assert(c == List_pop(list));
  assert(2 == list->len);
  assert(a == list->head);
  assert(b == list->tail);
  assert(a == b->prev);
  assert(NULL == list->tail->next && "new tail node next is not NULL");
  assert(NULL == c->prev && "detached node prev is not NULL");
  assert(NULL == c->next && "detached node next is not NULL");
  
  assert(b == List_pop(list));
  assert(1 == list->len);
  assert(a == list->head);
  assert(a == list->tail);
  
  assert(a == List_pop(list));
  assert(0 == list->len);
  assert(NULL == list->head);
  assert(NULL == list->tail);
  
  assert(NULL == List_pop(list));
  assert(0 == list->len);
}

static void
test_List_shift() {
  // Setup
  List *list = List_new();
  ListNode *a = List_push(list, ListNode_new("a"));
  ListNode *b = List_push(list, ListNode_new("b"));
  ListNode *c = List_push(list, ListNode_new("c"));

  // Assertions
  assert(3 == list->len);

  assert(a == List_shift(list));
  assert(2 == list->len);
  assert(b == list->head);
  assert(NULL == list->head->prev && "new head node prev is not NULL");
  assert(NULL == a->prev && "detached node prev is not NULL");
  assert(NULL == a->next && "detached node next is not NULL");
  
  assert(b == List_shift(list));
  assert(1 == list->len);
  
  assert(c == List_shift(list));
  assert(0 == list->len);
  assert(NULL == list->head);
  assert(NULL == list->tail);
  
  assert(NULL == List_shift(list));
  assert(0 == list->len);
}

static void
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
  test(List_find);
  test(List_at);
  test(List_remove);
  test(List_pop);
  test(List_shift);
  test(List_destroy);
  test(ListIterator);
  puts("... \x1b[32m100%\x1b[0m\n");
  return 0;
}