
#include <stdio.h>
#include <time.h>
#include "src/list.h"

static void
bm(char *label, void (*fn)()) {
  printf(" %18s", label);
  fflush(stdout);
  fn();
}

static int nnodes = 10000000;
static clock_t startTime;

static void
start() {
  startTime = clock();
}

static void
stop() {
  float duration = (float) (clock() - startTime) / CLOCKS_PER_SEC;
  printf(": \x1b[32m%.4f\x1b[0ms\n", duration);
}

static void
bm_push() {
  start();
  int n = nnodes;
  List *list = List_new();
  while (n--) {
    List_push(list, ListNode_new("foo"));
  }
  stop();
}

static void
bm_unshift() {
  start();
  int n = nnodes;
  List *list = List_new();
  while (n--) {
    List_unshift(list, ListNode_new("foo"));
  }
  stop();
}

static void
bm_find() {
  int n = nnodes;
  List *list = List_new();
  while (n--) {
    List_unshift(list, ListNode_new("foo"));
  }
  List_push(list, ListNode_new("bar"));
  start();
  List_find(list, "bar");
  stop();
}

static void
bm_iterate() {
  int n = nnodes;
  List *list = List_new();
  while (n--) {
    List_unshift(list, ListNode_new("foo"));
  }
  ListIterator *it = ListIterator_new(list, LIST_HEAD);
  ListNode *node;
  start();
  while ((node = ListIterator_next(it)))
    ;
  stop();
}

int
main(int argc, const char **argv){
  puts("\n 10,000,000 nodes\n");
  bm("pushed", bm_push);
  bm("unshifted", bm_unshift);  
  bm("find (last node)", bm_find);  
  bm("iterate", bm_iterate);  
  puts("");
  return 0;
}