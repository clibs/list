
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
test_list_node_new() {
  char *val = "some value";
  tlist_node *node = list_node_new(val);
  assert(node->val == val);
  free(node);
}

static void
test_list_rpush() {
  // Setup
  tlist *list = list_new();
  tlist_node *a = list_node_new("a");
  tlist_node *b = list_node_new("b");
  tlist_node *c = list_node_new("c");

  // a b c
  list_rpush(list, a);
  list_rpush(list, b);
  list_rpush(list, c);

  // Assertions
  assert(a == list->head);
  assert(c == list->tail);
  assert(3 == list->len);
  assert(b == a->next);
  assert(NULL == a->prev);
  assert(c == b->next);
  assert(a == b->prev);
  assert(NULL == c->next);
  assert(b == c->prev);

  list_destroy(list);
}

static void
test_list_lpush() {
  // Setup
  tlist *list = list_new();
  tlist_node *a = list_node_new("a");
  tlist_node *b = list_node_new("b");
  tlist_node *c = list_node_new("c");

  // c b a
  list_rpush(list, a);
  list_lpush(list, b);
  list_lpush(list, c);

  // Assertions
  assert(c == list->head);
  assert(a == list->tail);
  assert(3 == list->len);
  assert(NULL == a->next);
  assert(b == a->prev);
  assert(a == b->next);
  assert(c == b->prev);
  assert(b == c->next);
  assert(NULL == c->prev);

  list_destroy(list);
}

static void
test_list_at() {
  // Setup
  tlist *list = list_new();
  tlist_node *a = list_node_new("a");
  tlist_node *b = list_node_new("b");
  tlist_node *c = list_node_new("c");

  // a b c
  list_rpush(list, a);
  list_rpush(list, b);
  list_rpush(list, c);

  // Assertions
  assert(a == list_at(list, 0));
  assert(b == list_at(list, 1));
  assert(c == list_at(list, 2));
  assert(NULL == list_at(list, 3));

  assert(c == list_at(list, -1));
  assert(b == list_at(list, -2));
  assert(a == list_at(list, -3));
  assert(NULL == list_at(list, -4));

  list_destroy(list);
}

static void
test_list_destroy() {
  // Setup
  tlist *a = list_new();
  list_destroy(a);

  // a b c
  tlist *b = list_new();
  list_rpush(b, list_node_new("a"));
  list_rpush(b, list_node_new("b"));
  list_rpush(b, list_node_new("c"));
  list_destroy(b);

  // Assertions
  tlist *c = list_new();
  c->free = freeProxy;
  list_rpush(c, list_node_new(list_node_new("a")));
  list_rpush(c, list_node_new(list_node_new("b")));
  list_rpush(c, list_node_new(list_node_new("c")));
  list_destroy(c);
  assert(3 == freeProxyCalls);
}

static void
test_list_find() {
  // Setup
  tlist *langs = list_new();
  tlist_node *js = list_rpush(langs, list_node_new("js"));
  tlist_node *ruby = list_rpush(langs, list_node_new("ruby"));

  tlist *users = list_new();
  users->match = User_equal;
  User userTJ = { "tj" };
  User userSimon = { "simon" };
  User userTaylor = { "taylor" };
  tlist_node *tj = list_rpush(users, list_node_new(&userTJ));
  tlist_node *simon = list_rpush(users, list_node_new(&userSimon));

  // Assertions
  tlist_node *a = list_find(langs, "js");
  tlist_node *b = list_find(langs, "ruby");
  tlist_node *c = list_find(langs, "foo");
  assert(js == a);
  assert(ruby == b);
  assert(NULL == c);

  list_destroy(langs);

  a = list_find(users, &userTJ);
  b = list_find(users, &userSimon);
  c = list_find(users, &userTaylor);
  assert(tj == a);
  assert(simon == b);
  assert(NULL == c);

  list_destroy(users);
}

static void
test_list_remove() {
  // Setup
  tlist *list = list_new();
  tlist_node *a = list_rpush(list, list_node_new("a"));
  tlist_node *b = list_rpush(list, list_node_new("b"));
  tlist_node *c = list_rpush(list, list_node_new("c"));

  // Assertions
  assert(3 == list->len);

  list_remove(list, b);
  assert(2 == list->len);
  assert(a == list->head);
  assert(c == list->tail);
  assert(c == a->next);
  assert(NULL == a->prev);
  assert(NULL == c->next);
  assert(a == c->prev);

  list_remove(list, a);
  assert(1 == list->len);
  assert(c == list->head);
  assert(c == list->tail);
  assert(NULL == c->next);
  assert(NULL == c->prev);

  list_remove(list, c);
  assert(0 == list->len);
  assert(NULL == list->head);
  assert(NULL == list->tail);

  list_destroy(list);
}

static void
test_list_rpop() {
  // Setup
  tlist *list = list_new();
  tlist_node *a = list_rpush(list, list_node_new("a"));
  tlist_node *b = list_rpush(list, list_node_new("b"));
  tlist_node *c = list_rpush(list, list_node_new("c"));

  // Assertions
  assert(3 == list->len);

  assert(c == list_rpop(list));
  assert(2 == list->len);
  assert(a == list->head);
  assert(b == list->tail);
  assert(a == b->prev);
  assert(NULL == list->tail->next && "new tail node next is not NULL");
  assert(NULL == c->prev && "detached node prev is not NULL");
  assert(NULL == c->next && "detached node next is not NULL");

  free(c);

  assert(b == list_rpop(list));
  assert(1 == list->len);
  assert(a == list->head);
  assert(a == list->tail);

  free(b);

  assert(a == list_rpop(list));
  assert(0 == list->len);
  assert(NULL == list->head);
  assert(NULL == list->tail);

  free(a);

  assert(NULL == list_rpop(list));
  assert(0 == list->len);

  list_destroy(list);
}

static void
test_list_lpop() {
  // Setup
  tlist *list = list_new();
  tlist_node *a = list_rpush(list, list_node_new("a"));
  tlist_node *b = list_rpush(list, list_node_new("b"));
  tlist_node *c = list_rpush(list, list_node_new("c"));

  // Assertions
  assert(3 == list->len);

  assert(a == list_lpop(list));
  assert(2 == list->len);
  assert(b == list->head);
  assert(NULL == list->head->prev && "new head node prev is not NULL");
  assert(NULL == a->prev && "detached node prev is not NULL");
  assert(NULL == a->next && "detached node next is not NULL");

  free(a);

  assert(b == list_lpop(list));
  assert(1 == list->len);

  free(b);

  assert(c == list_lpop(list));
  assert(0 == list->len);
  assert(NULL == list->head);
  assert(NULL == list->tail);

  free(c);

  assert(NULL == list_lpop(list));
  assert(0 == list->len);

  list_destroy(list);
}

static void
test_list_iterator() {
  // Setup
  tlist *list = list_new();
  tlist_node *tj = list_node_new("tj");
  tlist_node *taylor = list_node_new("taylor");
  tlist_node *simon = list_node_new("simon");

  // tj taylor simon
  list_rpush(list, tj);
  list_rpush(list, taylor);
  list_rpush(list, simon);

  // Assertions

  // From head
  tlist_iterator *it = list_iterator_new(list, LIST_HEAD);
  tlist_node *a = list_iterator_next(it);
  tlist_node *b = list_iterator_next(it);
  tlist_node *c = list_iterator_next(it);
  tlist_node *d = list_iterator_next(it);

  assert(a == tj);
  assert(b == taylor);
  assert(c == simon);
  assert(NULL == d);

  list_iterator_destroy(it);

  // From tail
  it = list_iterator_new(list, LIST_TAIL);
  tlist_node *a2 = list_iterator_next(it);
  tlist_node *b2 = list_iterator_next(it);
  tlist_node *c2 = list_iterator_next(it);
  tlist_node *d2 = list_iterator_next(it);

  assert(a2 == simon);
  assert(b2 == taylor);
  assert(c2 == tj);
  assert(NULL == d2);
  list_iterator_destroy(it);

  list_destroy(list);
}

int
main(void){
  printf("\ntlist: %zu\n", sizeof(tlist));
  printf("tlist_node: %zu\n", sizeof(tlist_node));
  printf("tlist_iterator: %zu\n\n", sizeof(tlist_iterator));
  test(list_node_new);
  test(list_rpush);
  test(list_lpush);
  test(list_find);
  test(list_at);
  test(list_remove);
  test(list_rpop);
  test(list_lpop);
  test(list_destroy);
  test(list_iterator);
  puts("... \x1b[32m100%\x1b[0m\n");
  return 0;
}
